"""Main package classes, functions and utilities."""


from .converter import (
    MEDIUM_GAP,
    AlphabetConverter,
    MorseConverter,
)
from .exceptions import (
    MorseError,
    ProcessMorseError,
    TranslatorMorseError,
)
from .settings import PROJECT, UNIT
from .translator import (
    AlphabetTranslator,
    MorseTranslator,
    get_translator_results,
    translate_morse,
)
from .utils import (
    get_logger,
    get_mor_code,
    get_return_code,
    humanize_mor_code,
)


CLOSE_SENTINEL = MorseTranslator.CLOSE_SENTINEL
