"""Bidirectional morse signal interpreter and translator."""


import Queue
import abc
import collections
import copy
import functools
import itertools
import threading

import six
from scipy.cluster.vq import kmeans, vq, whiten

from libmorse import converter, exceptions, settings
from libmorse.utils import Logger


# Different states into which the translator may run across.
class STATE:
    LONG_PAUSE = "<long pause>"


@six.add_metaclass(abc.ABCMeta)
class BaseTranslator(Logger):

    """Base class for any kind of translator"""

    CLOSE_SENTINEL = None
    SIG_MINLEN, SIG_MAXLEN = settings.SIG_RANGE
    SIL_MINLEN, SIL_MAXLEN = settings.SIL_RANGE
    FACTORS = settings.RATIO_HANDICAP

    handicapify = (lambda vec, handi_factor=None:
                   [item * handi_factor for item in vec])
    sig_handicap, sil_handicap = map(
        lambda factor, func=handicapify: functools.partial(
            func,
            handi_factor=factor
        ),
        [FACTORS.SIGNALS, FACTORS.SILENCES]
    )
    CONFIG = {
        "signals": {
            "type": "signals",
            "means": 2,
            "mean_min_diff": settings.MEAN_MIN_DIFF,
            "mean_max_diff": settings.MEAN_MAX_DIFF,
            "min_length": SIG_MINLEN,
            # Tuples of (sum_of_ratios, ratios_count).
            "ratios": {
                converter.DOT: sig_handicap([1.0, 1]),
                converter.DASH: sig_handicap([3.0, 1]),
            },
            "offset": 0,
        },
        "silences": {
            "type": "silences",
            "means": 3,
            "mean_min_diff": settings.MEAN_MIN_DIFF,
            "mean_max_diff": settings.MEAN_MAX_DIFF,
            "min_length": SIL_MINLEN,
            # Tuples of (sum_of_ratios, ratios_count).
            "ratios": {
                converter.INTRA_GAP: sil_handicap([1.0, 1]),
                converter.SHORT_GAP: sil_handicap([3.0, 1]),
                converter.MEDIUM_GAP: sil_handicap([7.0, 1]),
            },
            "offset": 0,
        },
    }

    def __init__(self, *args, **kwargs):
        super(BaseTranslator, self).__init__(__name__, *args, **kwargs)

        self._input_queue = Queue.Queue()
        self._output_queue = Queue.Queue()
        self._queue_processor = None    # parallel thread handling processing
        self._closed = threading.Event()

        self.config = copy.deepcopy(self.CONFIG)
        self._unit = None    # should be initialized as deque (below)
        self.unit = settings.UNIT    # average used unit length

        # Last set state of the last analysed signals/silences.
        self.last_state = None  # used to notify the outsides (changeable)

        self._start()    # start the item processor

    @property
    def unit(self):
        """Returns the length in ms of the most basic morse unit."""
        if not self._unit:
            return None
        return sum(self._unit) / len(self._unit)

    @unit.setter
    def unit(self, unit):
        del self.unit
        maxlen = max(self.SIG_MAXLEN, self.SIL_MAXLEN)
        self._unit = collections.deque(maxlen=maxlen)
        if unit:
            self._unit.append(unit)

    @unit.deleter
    def unit(self):
        if self._unit:
            self._unit.clear()

    @staticmethod
    def _calc_ratios(ratios):
        normed_ratios = {}
        for symbol, ratio_data in ratios.items():
            ratio = ratio_data[0] / ratio_data[1]
            normed_ratios[symbol] = ratio
        return normed_ratios

    def _free(self):
        del self._input_queue
        del self._output_queue
        del self.unit

    @abc.abstractmethod
    def _process(self, item):
        """Returns a list of processed items as results."""

    def _run(self):
        while True:
            item = self._input_queue.get()
            if item == self.CLOSE_SENTINEL:
                self._input_queue.task_done()
                self._free()
                break

            if not self.closed:
                try:
                    results = self._process(item)
                except exceptions.TranslatorMorseError as exc:
                    self.log.error(exc)
                else:
                    if not isinstance(results, (tuple, list, set)):
                        results = [results]
                    for result in results:
                        if result != self.CLOSE_SENTINEL:
                            # Add rightful results only.
                            self._output_queue.put(result)

            self._input_queue.task_done()

    def _start(self):
        self._queue_processor = threading.Thread(target=self._run)
        self._queue_processor.setDaemon(True)
        self._queue_processor.start()

    def put(self, item, **kwargs):
        """Add a new item to the processing queue.

        This can be a simple alphabet letter or timed signal.
        """
        if self.closed:
            if item == self.CLOSE_SENTINEL:
                raise exceptions.TranslatorMorseError(
                    "translator already closed"
                )
            raise exceptions.TranslatorMorseError(
                "put operation on closed translator"
            )
        try:
            self._input_queue.put(item, **kwargs)
        except Queue.Full:
            raise exceptions.TranslatorMorseError("full queue")

    def get(self, **kwargs):
        """Retrieve and return from the processed items a new item."""
        if self.closed:
            raise exceptions.TranslatorMorseError(
                "get operation on closed translator"
            )
        try:
            result = self._output_queue.get(**kwargs)
        except Queue.Empty:
            raise exceptions.TranslatorMorseError("empty queue")
        self._output_queue.task_done()
        return result

    @property
    def closed(self):
        """Returns True if the translator is closed."""
        return self._closed.is_set()

    def close(self):
        """Close and wait the translator to finish and free resources."""
        self.put(self.CLOSE_SENTINEL)
        self._closed.set()
        self._queue_processor.join()

    def wait(self):
        """Block until all the items in the queue are processed."""
        self._input_queue.join()


class AlphabetTranslator(BaseTranslator):

    """Alphabet to morse translator."""

    def __init__(self, *args, **kwargs):
        super(AlphabetTranslator, self).__init__(*args, **kwargs)

        self._converter = converter.AlphabetConverter(*args, **kwargs)
        # Use predefined ratios when creating timings.
        self._ratios = {}
        self.update_ratios(self.config)

    def update_ratios(self, config):
        """Update the standard ratios with custom learned ones within a
        custom configuration.
        """
        for ent in ("signals", "silences"):
            ratios = config[ent]["ratios"]
            normed_ratios = self._calc_ratios(ratios)
            self._ratios.update(normed_ratios)

    def _process(self, item):
        # Convert every new character into a morse letter.
        letters = self._converter.add([item])
        # Translate the obtained morse code into timed signals.
        signals = []
        unit = self.unit

        for letter in letters:
            if letter in (converter.SHORT_GAP, converter.MEDIUM_GAP):
                # Create the silence for the gap between characters or words.
                silence = (False, self._ratios[letter] * unit)
                signals.append(silence)
                continue

            # We have a letter; properly add all the successive signals and
            # silences.
            silence = (False, self._ratios[converter.INTRA_GAP] * unit)
            extend = [((True, self._ratios[symbol] * unit), silence)
                      for symbol in letter]
            extend = [signal for pair in extend for signal in pair]
            # There is no intra-gap at the end of the letter; short gap
            # follows explicitly.
            extend.pop(-1)
            signals.extend(extend)

        return signals

    def _free(self):
        self._converter.free()

        super(AlphabetTranslator, self)._free()


class MorseTranslator(BaseTranslator):

    """Morse to alphabet translator."""

    def __init__(self, *args, **kwargs):
        super(MorseTranslator, self).__init__(*args, **kwargs)

        # Actively analysed signals.
        self._signals = collections.deque(maxlen=self.SIG_MAXLEN)
        # Actively analysed silences; the same range may work.
        self._silences = collections.deque(maxlen=self.SIL_MAXLEN)
        # First and last provided items.
        self._begin = None
        self.last_item = None
        # Actual morse code, divided and combined.
        self._morse_signals = []
        self._morse_silences = []
        self._morse_pick = itertools.cycle([
            self._morse_signals, self._morse_silences
        ])
        self._morse_selected = None
        self._morse_code = []
        # Code converter.
        self._converter = converter.MorseConverter(*args, **kwargs)
        # Items saturation.
        self._skip_type = None

        # Custom learned units allowed only.
        self.unit = None

    def _free(self):
        self._signals.clear()
        self._silences.clear()
        self._morse_signals = []
        self._morse_silences = []
        del self._morse_pick
        self._morse_selected = None
        self._morse_code = []
        self._converter.free()

        super(MorseTranslator, self)._free()

    def _get_signal_classes(self, means, ratios):
        """Classify the means into signal types."""
        classes = []
        unit = min(means)    # good unit for reference
        ratios_items = ratios.items()

        for mean in means:
            ratio = mean / unit
            # Find closest defined ratio.
            best_class = None
            min_delta = abs(ratios_items[0][1] - ratio) + 1
            for entity, entity_ratio in ratios_items:
                delta = abs(ratio - entity_ratio)
                if delta < min_delta:
                    min_delta = delta
                    best_class = entity
            classes.append(best_class)

        return classes

    def _stable_kmeans(self, container, clusters):
        # Normalize the elements to be clustered.
        factor = container[-1]
        container = whiten(container)
        factor /= container[-1]
        # Get the stable means.
        count = settings.CLUSTER_ITER

        while True:
            means = kmeans(container, clusters)[0]
            # Obtain and return the labels along with the means.
            labels = vq(container, means)[0]
            # Check for empty clusters.
            labels_set = set(labels)
            clusters_set = set(range(clusters))
            if labels_set == clusters_set:
                break

            self.log.warning("Empty clusters (%d/%d).",
                             *map(len, [labels_set, clusters_set]))
            if count is not None:
                if count <= 0:
                    raise exceptions.TranslatorMorseError(
                        "k-means maximum number of iterations reached")
                else:
                    count -= 1

        # Return the original means along the labels distribution.
        return means * factor, labels

    def _update_ratios(self, conf_ratios, means):
        def sort_ratios(symbol):
            metric = conf_ratios[symbol]
            return metric[0] / metric[1]

        symbols = sorted(conf_ratios, key=sort_ratios)
        unit = self.unit
        new_ratios = [mean / unit for mean in sorted(means)]

        for idx, symbol in enumerate(symbols):
            symbol_ratio = conf_ratios[symbol]
            symbol_ratio[0] += new_ratios[idx]
            symbol_ratio[1] += 1

    def _analyse(self, container, config):
        """Analyse and translate if possible the current range of
        signals or silences.
        """
        # Get a first classification of the signals.
        means, distribution = self._stable_kmeans(container, config["means"])
        unit = min(means)
        lower_bound = config["mean_min_diff"] * unit
        upper_bound = config["mean_max_diff"] * unit
        for combi in itertools.combinations(means, 2):
            delta = abs(combi[0] - combi[1])
            if not lower_bound < delta < upper_bound:
                # Insufficient or incoherent signals.
                return None

        # If we got here, it means that we have a good approved unit as the
        # minimum centroid.
        self._unit.append(unit)
        # Also converge ratios as well.
        conf_ratios = config["ratios"]
        self._update_ratios(conf_ratios, means)

        # We've got a correct distribution. Take each remaining unprocessed
        # signal and normalize its classification.
        normed_ratios = self._calc_ratios(conf_ratios)
        signal_classes = self._get_signal_classes(means, normed_ratios)
        signals = []
        for signal_index in distribution[config["offset"]:]:
            signals.append(signal_classes[signal_index])
        config["offset"] = len(distribution)

        return signals

    def _parse_morse_code(self):
        """Transform obtained morse code into alphabet."""
        text = self._converter.add(self._morse_code)
        self._morse_code = []
        if text is None:
            return None
        return list(text)

    def _get_minmax_ratio(self, ratios, func=max):
        normed_ratios = self._calc_ratios(ratios)
        minmax_ratio = func(normed_ratios.values())
        return minmax_ratio

    def _check_add_last(self):
        """Returns True if the signal is the longest of its kind."""
        unit = self.unit
        if not unit:
            return False

        stype, slen = self.last_item
        selected = "signals" if stype else "silences"
        config = self.config[selected]
        ratios = config["ratios"]
        normed_ratios_values = self._calc_ratios(ratios).values()
        max_ratio = max(normed_ratios_values)

        closest_ratio = normed_ratios_values[0]
        closest_dist = abs(closest_ratio * unit - slen)
        for ratio in normed_ratios_values:
            new_dist = abs(ratio * unit - slen)
            if new_dist < closest_dist:
                closest_dist = new_dist
                closest_ratio = ratio

        if (closest_ratio == max_ratio and
                slen - closest_ratio * unit > unit):
            return True
        return False

    def _correct_item(self, item, save_state=True):
        """Save some states regarding the given signal/silence,
        while normalizing it to an adequate length.
        """
        unit = self.unit
        if not unit:
            return item

        stype, slen = item
        state = None    # nothing special
        if stype:
            # Analysing a signal.
            conf = self.config["signals"]
        else:
            # Analysing a silence.
            conf = self.config["silences"]

        # Check a long signal/silence.
        max_ratio = self._get_minmax_ratio(conf["ratios"])
        max_length = max_ratio * unit
        delta = slen - max_length
        limit = conf["mean_min_diff"] * unit
        if delta > limit:
            slen = max_length
            if not stype:
                state = STATE.LONG_PAUSE

        if state and save_state:
            self.last_state = state
        return stype, slen

    def _correct_container(self, container, stype):
        """Normalize the maximum length of each item found in `container`."""
        for idx, slen in enumerate(container):
            item = (stype, slen)
            item = self._correct_item(item, save_state=False)
            container[idx] = item[1]

    def _process(self, item):
        # Remove noise.
        unit = self.unit
        if unit and item[1] < settings.NOISE_RATIO * unit:
            return self.CLOSE_SENTINEL
        # Check if skipped.
        if self._skip_type is not None and self._skip_type == item[0]:
            return self.CLOSE_SENTINEL
        self._skip_type = None

        # Decide with what kind of item we begin first (signal/silence).
        if not self._begin:
            # Used for knowing how to bounce between the signals.
            self._begin = item
            if not self._begin[0]:
                # Starting with a silence first.
                next(self._morse_pick)

        # Take the last saved item and join with the new one if it's from the
        # same kind, otherwise just add the last one and mark a new last item
        # out of this new one.
        selected = None
        added_item = False
        if self.last_item:
            # We have a last item available.
            # Now check if is from the same family and if yes, then merge the
            # two of them together.
            add_last = False

            if item[0] == self.last_item[0]:
                # Join durations and update the last item.
                item = (item[0], item[1] + self.last_item[1])
                self.last_item = item
                add_last = self._check_add_last()

            if item[0] != self.last_item[0] or add_last:
                # Decide active container depending on the signal type.
                if self.last_item[0]:
                    container = self._signals
                    selected = "signals"
                else:
                    container = self._silences
                    selected = "silences"
                config = self.config[selected]

                # Got new item type, so add the last one and mark the new one
                # as last. Before appending, adjust the offset according to
                # queue fullness.
                if len(container) >= container.maxlen:
                    if config["offset"] <= 0:
                        raise exceptions.TranslatorMorseError(
                            "missing {} variation".format(selected)
                        )
                    config["offset"] -= 1
                # Add a new corrected signal (duration only).
                last = self._correct_item(self.last_item)
                container.append(last[1])
                added_item = True
                self.last_item = item
                if add_last:
                    # We've just added the last item instead of keeping it,
                    # therefore we don't have a last item anymore.
                    self.last_item = None
                    # And also, we'll not accept the same signal/silence
                    # anymore, until something different will come.
                    self._skip_type = item[0]

        else:
            # There's no last item available, mark the current one as the
            # last one.
            self.last_item = item
            # Nothing will happen, because we just have empty queues.

        # Re-process the new state of the active queues and try to give a
        # result based on the current set of signals and silences.
        pairs = [
            (self._signals, self.config["signals"], self._morse_signals,
             selected == "signals"),
            (self._silences, self.config["silences"], self._morse_silences,
             selected == "silences")
        ]
        for container, config, collection, choice in pairs:
            must_analyse = added_item and choice
            if len(container) >= config["min_length"] and must_analyse:
                stype = config["type"] == "signals"
                self._correct_container(container, stype)
                signals = self._analyse(container, config)
                collection.extend(signals or [])

        # Combine obtained morse signals and silences.
        news = False
        while True:
            self._morse_selected = next(self._morse_pick)
            if not self._morse_selected:
                next(self._morse_pick)
                break
            symbol = self._morse_selected.pop(0)
            self._morse_code.append(symbol)
            news = True

        # Parse the actual morse code and send the result for the output
        # queue if applicable.
        return self._parse_morse_code() if news else self.CLOSE_SENTINEL

    @property
    def medium_gap_ratio(self):
        conf_ratios = self.config["silences"]["ratios"]
        return self._get_minmax_ratio(conf_ratios)


def get_translator_results(translator, force_wait=False):
    """Returns a renewal status and translator results.

    Having the possibility to wait for it to finish completely.
    """
    renew = False
    all_results = []

    if force_wait:
        translator.wait()

    while True:
        state = translator.last_state
        if state:
            # Reset old already read state.
            translator.last_state = None
            # Handle last read state.
            if state == STATE.LONG_PAUSE:
                # Renew the translator (new learning session).
                translator.wait()
                renew = True

        try:
            result = translator.get(block=False)
        except exceptions.TranslatorMorseError:
            break
        else:
            all_results.append(result)

    return renew, all_results


def translate_morse(*args, **kwargs):
    """Translator helper function that handles sessions and corrects
    signals.

    Acts like a coroutine, while handling on-the-fly any issue with the
    supplied signals.
    """
    enable_renewal = kwargs.pop("enable_renewal", settings.ENABLE_RENEWAL)
    get_translator = lambda: MorseTranslator(*args, **kwargs)
    translator = get_translator()

    # This should run indefinitely (until explicit close).
    while True:
        new_trans, results = get_translator_results(translator)

        # Get new item while returning last result.
        item = yield translator, results

        if enable_renewal and new_trans:
            translator.wait()
            translator.close()
            last_item = translator.last_item
            translator = get_translator()
            translator.last_item = last_item
        if item == translator.CLOSE_SENTINEL:
            translator.close()
            break
        else:
            translator.put(item)
