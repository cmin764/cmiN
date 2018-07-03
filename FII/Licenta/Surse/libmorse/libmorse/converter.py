"""Basic converter from morse code to alphabet and reverse."""


import abc

import anytree
import six

from libmorse import exceptions, utils


# Signals.
DOT = "."
DASH = "-"

# Silences.
INTRA_GAP = ""
SHORT_GAP = " "
MEDIUM_GAP = " / "


@six.add_metaclass(abc.ABCMeta)
class BaseConverter(utils.Logger):

    """Base class for morse-alphabet conversion."""

    def __init__(self, *args, **kwargs):
        self._silence_errors = kwargs.pop("silence_errors", True)
        super(BaseConverter, self).__init__(__name__, *args, **kwargs)

        self._morse_dict = None
        self._morse_tree = anytree.Node("Morse")
        self._input = []

        self._load_morse_code()

    @classmethod
    def _fill_tree(cls, node, char, code):
        if not code:
            # We've reached the end of the code; mark it with its related
            # character.
            node.char = char
            return

        # Take the first one from the remaining symbols.
        next = code.pop(0)
        # Search for its existence.
        target = [child for child in node.children if child.name == next]
        if target:
            target = target[0]
        else:
            # Create a new node if missing.
            target = anytree.Node(next, parent=node)
        # And proceed further with the markings.
        cls._fill_tree(target, char, code)

    def _load_morse_code(self):
        # Obtain morse codes from resource.
        self._morse_dict = utils.get_resource(
            "morse.json", resource_type=utils.RES_JSON)
        for char, code in self._morse_dict.items():
            self._fill_tree(self._morse_tree, char, list(code))

    def free(self):
        del self._morse_tree
        del self._input

    @abc.abstractmethod
    def _process(self):
        """Convert the current list of items and return the result."""

    def add(self, symbols):
        """Add new items and return results."""
        # Add the newly received items.
        self._input.extend(symbols)
        # Try to process the current state of the list of unprocessed
        # items.
        return self._process()


class AlphabetConverter(BaseConverter):

    """Alphabet to simple morse code converter."""

    def __init__(self, *args, **kwargs):
        super(AlphabetConverter, self).__init__(*args, **kwargs)

        self._last_char = None

    def _process(self):
        letters = []

        for char in self._input:
            gap = None

            if char == " ":
                letter = MEDIUM_GAP
            else:
                letter = self._morse_dict.get(char)
                if not letter:
                    msg = "latin character {!r} not found".format(char)
                    if self._silence_errors:
                        self._log_error(msg)
                    else:
                        raise exceptions.ConverterMorseError(msg)
                if self._last_char not in (None, " "):
                    gap = SHORT_GAP
            self._last_char = char

            if gap:
                letters.append(gap)
            if letter:
                letters.append(letter)

        self._input = []
        return letters


class MorseConverter(BaseConverter):

    """Simple morse code to alphabet converter."""

    def _get_tree_char(self, node, code, letter):
        def raise_not_found():
            msg = "morse letter {!r} not found".format(letter)
            if self._silence_errors:
                self._log_error(msg)
            else:
                raise exceptions.ConverterMorseError(msg)

        if not code:
            if hasattr(node, "char") and node.char:
                return node.char
            raise_not_found()
            return None    # nothing found and no error raised

        # Take the first one from the remaining symbols.
        next_code = code.pop(0)
        # Search for its existence.
        target = [child for child in node.children if child.name == next_code]
        if target:
            return self._get_tree_char(target[0], code, letter)
        else:
            raise_not_found()
            return None    # nothing found and no error raised

    def _get_char(self, letter):
        """Return the corresponding char given morse `letter`."""
        if not letter:
            return None
        return self._get_tree_char(self._morse_tree, list(letter), letter)

    def _process_word(self, word, last=False):
        # Span the list of dots, dashes and short gaps into groups
        # forming letters.
        letters = "".join(word).split(SHORT_GAP)

        char_list = []
        size = len(letters)
        for idx, letter in enumerate(letters):
            if last and idx == size - 1:
                # We've just reached the end of the signal list and may have
                # an unfinished letter (other dots or dashes may append).
                # Therefore, we mustn't process this (probable) incomplete
                # letter and we need to truncate the input list from the
                # beginning until the start of the last incomplete letter.
                self._input = []
                for symbol in letter:
                    self._input.extend([symbol, ""])
                break

            char = self._get_char(letter)
            if char is not None:
                char_list.append(char)

        return "".join(char_list)

    def _process(self):
        # Split the entire list of signals into chunks containing only one
        # word each.
        words = []
        count = self._input.count(MEDIUM_GAP)
        lo = 0
        for _ in range(count):
            hi = self._input.index(MEDIUM_GAP, lo)
            words.append(self._input[lo:hi])
            lo = hi + 1
        hi = len(self._input)
        words.append(self._input[lo:hi])

        chars_list = []
        size = len(words)
        for idx, word in enumerate(words):
            last = idx == size - 1
            chars = self._process_word(word, last=last)
            if chars is not None:
                chars_list.append(chars)

        return " ".join(chars_list) or None
