import itertools
import random
import time
import unittest

import mock
import numpy as np

import libmorse
from libmorse import settings


DEBUG = True
log = libmorse.get_logger(__name__, debug=DEBUG)


class TestMorseMixin(object):

    def _test_mixed_signals(self, to_adapt=True, safe=True):
        # Get two common morse codes.
        morse_code = []
        code, noise_code = map(
            libmorse.get_mor_code, ["basic.mor", "basic_noise.mor"])
        # Make the test coherent.

        def adapt(a_code):
            if not to_adapt:
                return a_code
            # Remove (by reducing to 1ms) the first silence in a code,
            # if exists.
            item = a_code[0]
            if not item[0]:
                item = (item[0], 1)
                a_code[0] = item
                if safe:
                    a_code.pop(0)
            return a_code

        code, noise_code = map(adapt, [code, noise_code])

        times = random.randint(4, 6)
        for _ in range(times):
            sel_code = random.choice([code, noise_code])
            morse_code.extend(sel_code)
        expected = " ".join(["MORSE CODE"] * times)

        return morse_code, expected

    @staticmethod
    def _humanize(morse_code):
        libmorse.humanize_mor_code(morse_code)


class TestMorseTranslator(unittest.TestCase, TestMorseMixin):

    # Morse code resources.
    MORSE = {
        "basic.mor": [
            "-- --- .-. ... . / -.-. --- -.. .",
            "MORSE CODE"
        ],
        "basic_noise.mor": [
            "-- --- .-. ... . / -.-. --- -.. .",
            "MORSE CODE"
        ],
    }

    def setUp(self):
        self.translator = libmorse.MorseTranslator(debug=DEBUG)

    def tearDown(self):
        self.translator.close()

    def _send_mor_code(self, mor_code):
        for signal in mor_code:
            self.translator.put(signal)
        self.translator.wait()

    def _get_translation(self, mor_file, get_alphabet=True, morse_code=None,
                         humanize=False):
        mor_code = morse_code or libmorse.get_mor_code(mor_file)
        if humanize:
            self._humanize(mor_code)

        if get_alphabet:
            self._send_mor_code(mor_code)
        else:
            with mock.patch("libmorse.translator.MorseTranslator."
                            "_parse_morse_code") as mock_parse:
                def parse():
                    code = self.translator._morse_code[:]
                    self.translator._morse_code = []
                    return code
                mock_parse.side_effect = parse
                self._send_mor_code(mor_code)

        results = []
        while True:
            try:
                result = self.translator.get(block=False)
            except libmorse.TranslatorMorseError as exc:
                log.debug(exc)
                break
            results.append(result)

        return results

    def _test_alphamorse(self, name, test_alphabet=True, morse_code=None,
                         message=None, expected=None, humanize=False):
        translation = self._get_translation(
            name,
            get_alphabet=test_alphabet,
            morse_code=morse_code,
            humanize=humanize
        )
        result = "".join(translation).strip()
        if not test_alphabet:
            result = result.strip(" /")

        if expected is None:
            expected = self.MORSE[name][int(test_alphabet)]
        args = [expected, result]
        if message:
            args.append(message)
        self.assertEqual(*args)

    def test_basic_morse(self):
        self._test_alphamorse("basic.mor", test_alphabet=False)

    def test_basic_alphabet(self):
        self._test_alphamorse("basic.mor", test_alphabet=True,
                              humanize=True)

    def test_basic_noise_morse(self):
        self._test_alphamorse("basic_noise.mor", test_alphabet=False)

    def test_basic_noise_alphabet(self):
        self._test_alphamorse("basic_noise.mor", test_alphabet=True,
                              humanize=True)

    def _test_no_silence_morse(self, message, remove_idx, expected=None,
                               humanize=False):
        """Strip the beginning and ending silence."""
        mor_code = libmorse.get_mor_code("basic.mor")
        for idx in remove_idx:
            mor_code.pop(idx)
        self._test_alphamorse("basic.mor", morse_code=mor_code,
                              message=message, expected=expected,
                              humanize=humanize)

    def test_no_silence_morse_begin(self):
        self._test_no_silence_morse(
            "no silence at beginning",
            [0],
            humanize=True
        )

    def test_no_silence_morse_end(self):
        self._test_no_silence_morse(
            "no silence at the end",
            [-1],
            expected="MORSE COD"
        )

    def test_no_silence_morse_all(self):
        self._test_no_silence_morse(
            "no silence at all",
            [0, -1],
            expected="MORSE COD"
        )

    def test_mixed_signals(self):
        morse_code, expected = self._test_mixed_signals()
        self._test_alphamorse(None, morse_code=morse_code, expected=expected,
                              humanize=True)

    def _test_stable_kmeans(self, clusters_dim, tests_dim=100):
        # Generate random signals that should be classified in `clusters_dim`
        # groups.
        unit = settings.UNIT
        ideal_means = [unit]
        for _ in range(clusters_dim - 1):
            ideal_means.append(ideal_means[-1] * 2 + unit)
        # Make a few tests with different data, but the very same labeling.
        for crt in range(tests_dim):
            # How many signals of each label.
            sig_dim = np.random.randint(*settings.SIG_RANGE) / clusters_dim
            # The actual signals.
            signals = []
            for mean in ideal_means:
                dist = np.random.randn(sig_dim) * 10 + mean
                signals.extend(dist.tolist())
            # Run clustering.
            random.shuffle(signals)
            _, labels = self.translator._stable_kmeans(
                signals, clusters_dim)
            labels_list = labels.tolist()
            for idx in range(clusters_dim):
                self.assertEqual(sig_dim, labels_list.count(idx),
                                 "iteration #{}".format(crt + 1))

    def test_stable_kmeans_2_clusters(self):
        self._test_stable_kmeans(2)

    def test_stable_kmeans_3_clusters(self):
        self._test_stable_kmeans(3)


class TestTranslateMorse(unittest.TestCase, TestMorseMixin):

    # Sleep at each signal (as they would take while captured).
    SLEEP_FACTOR = 100    # set to None in order to not use sleeping

    def setUp(self):
        self.translate = libmorse.translate_morse(debug=DEBUG)
        self.translate.next()

    def tearDown(self):
        try:
            self.translate.send(libmorse.CLOSE_SENTINEL)
        except StopIteration:
            pass

    @classmethod
    def _sleep_by(cls, item):
        factor = cls.SLEEP_FACTOR
        if not factor:
            return

        # Mimic the reality (diverged by a factor).
        quantum = item[1] / 1000.0    # from ms to seconds
        quantum /= factor
        time.sleep(quantum)

    def _test_morse(self, mor_code, expected, humanize=True):
        results = []
        trans = None
        if humanize:
            self._humanize(mor_code)

        for item in mor_code:
            self._sleep_by(item)
            trans, res = self.translate.send(item)
            results.extend(res)
        # Wait for the finish of the entire processing.
        if trans:
            _, res = libmorse.get_translator_results(trans, force_wait=True)
            results.extend(res)

        obtained = "".join(results).strip()
        self.assertEqual(expected, obtained)

    def test_basic(self):
        mor_code = libmorse.get_mor_code("basic.mor")
        # Add long time of silence at the end.
        self._test_morse(mor_code, "MORSE CODE")

    def test_mixed_signals_adapt_safe(self):
        morse_code, expected = self._test_mixed_signals()
        self._test_morse(morse_code, expected)

    def test_mixed_signals_no_adapt(self):
        morse_code, expected = self._test_mixed_signals(
            to_adapt=False, safe=False)
        self._test_morse(morse_code, expected)

    def test_mixed_signals_adapt_no_safe(self):
        # Here we have very small noise.
        morse_code, expected = self._test_mixed_signals(
            to_adapt=True, safe=False)
        self._test_morse(morse_code, expected)

    def test_noise(self):
        mor_code = libmorse.get_mor_code("isolated_noise.mor")
        # Add long time of silence at the end.
        self._test_morse(mor_code, "MORSE CODE")

    def test_long_pause(self):
        mor_code = libmorse.get_mor_code("long_pause.mor")
        self._test_morse(mor_code, "MORSE C O DE")

    def test_long_silence(self):
        mor_code = [(False, 900) for _ in range(10)]
        self._test_morse(mor_code, "", humanize=False)

    def test_invalid_char(self):
        mor_code = libmorse.get_mor_code("invalid_char.mor")
        # D is skipped because it is not found due to: ..-- (invalid).
        self._test_morse(mor_code, "MORSE COE")

    def _test_incoherent(self, fraction, range_factor=2):
        unit = settings.UNIT
        delta = unit * fraction
        bools = [True, False]
        signal, use_delta = map(
            itertools.cycle,
            (
                bools,
                itertools.chain(*zip(bools, bools))
            )
        )
        get_unit = (
            lambda: (
                (unit + random.uniform(-delta, delta)) if fraction < 1 else
                (unit + int(use_delta.next()) * delta +
                 random.uniform(0, unit * settings.NOISE_RATIO))
            )
        )

        max_range = max(settings.SIG_RANGE, settings.SIL_RANGE)
        mor_code = [
            (signal.next(), get_unit())
            for _ in range(int(max_range[1] * range_factor))
        ]
        self._test_morse(mor_code, "", humanize=False)

    def test_incoherent_close(self):
        self._test_incoherent(0.5)

    def test_incoherent_far(self):
        self._test_incoherent(13, range_factor=3)

    def test_signal_fractions(self):
        mor_code = libmorse.get_mor_code("signal_fractions.mor")
        self._test_morse(mor_code, "MORSE CODE 0M")

    def test_basic_slow(self):
        mor_code = libmorse.get_mor_code("basic_slow.mor")
        self._test_morse(mor_code, "MORSE CODE")

    def test_fluctuation(self):
        mor_code = libmorse.get_mor_code("basic_fluctuation.mor")
        self._test_morse(mor_code, "MORSE CODE")

    def test_fluctuation_multi(self):
        mor_code = libmorse.get_mor_code("basic_fluctuation.mor")

        morse_code = []
        times = random.randint(4, 6)
        for _ in range(times):
            morse_code.extend(mor_code)
        expected = " ".join(["MORSE CODE"] * times)

        self._test_morse(morse_code, expected)
