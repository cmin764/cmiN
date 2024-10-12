import string
from collections import deque
from typing import Generator

KeyType = dict[str, tuple[int, int]]

# Letters available for usage in the key table.
KEY_SPACE = set(string.ascii_lowercase) - {"j"}
# At what position in the key table will we find a specific character.
IN_KEY: KeyType = {}
# The key table itself (5x5 2D matrix) linearized as a 1D vector.
KEY_TABLE: deque[str | None] = deque([None] * 25)


def _get_key(row: int, col: int) -> str | None:
    assert 0 <= row < 5
    assert 0 <= col < 5
    return KEY_TABLE[row * 5 + col]


def _set_key(row: int, col: int, *, value: str | None):
    assert 0 <= row < 5
    assert 0 <= col < 5
    KEY_TABLE[row * 5 + col] = value


def _show_key_table():
    for row in range(5):
        print(*(_get_key(row, col) or " " for col in range(5)), sep=" ")
    print()


def _populate_key_lookup():
    for row in range(5):
        for col in range(5):
            char = _get_key(row, col)
            if char:
                IN_KEY[char] = (row, col)


def encrypt(plain_text: str) -> str:
    _populate_key_lookup()

    crypt_pairs = []
    for idx in range(0, len(plain_text), 2):
        plain_pair: str = plain_text[idx : idx + 2]
        row1, col1 = IN_KEY[plain_pair[0]]
        row2, col2 = IN_KEY[plain_pair[1]]
        if row1 == row2:
            crypt_pair = (
                f"{_get_key(row1, (col1 + 1) % 5)}{_get_key(row2, (col2 + 1) % 5)}"
            )
        elif col1 == col2:
            crypt_pair = (
                f"{_get_key((row1 + 1) % 5, col1)}{_get_key((row2 + 1) % 5, col2)}"
            )
        else:
            crypt_pair = f"{_get_key(row1, col2)}{_get_key(row2, col1)}"
        crypt_pairs.append(crypt_pair)

    return "".join(crypt_pairs)


def validate_bigrams(plain_pair: str, crypt_pair: str, *, encrypt: bool) -> KeyType:
    """Fills in the key table based on the present chars and existing rules.

    This is triggered when we have at least one complete pair on any side:
    - the plain one which encrypts into crypt and fills/validates the key table
    - the crypt one which decrypts into plan and fills/validates the key table

    This returns what new keys need to be added in the table.
    It raises `ValueError` when the rules cannot hold true anymore due to the current
    key table state.
    """
    if encrypt:
        source_pair, dest_pair = plain_pair, crypt_pair
        movement = 1
    else:
        source_pair, dest_pair = crypt_pair, plain_pair
        movement = -1
    row1, col1 = IN_KEY[source_pair[0]]
    row2, col2 = IN_KEY[source_pair[1]]

    if row1 == row2:
        # Chars are on the same row, therefore we move right or left.
        new_dest = {
            dest_pair[0]: (row1, (col1 + movement) % 5),
            dest_pair[1]: (row2, (col2 + movement) % 5),
        }
    elif col1 == col2:
        # Chars are on the same column, therefore we move down or up.
        new_dest = {
            dest_pair[0]: ((row1 + movement) % 5, col1),
            dest_pair[1]: ((row2 + movement) % 5, col2),
        }
    else:
        # Chars describe the corners of a rectangle.
        new_dest = {
            dest_pair[0]: (row1, col2),
            dest_pair[1]: (row2, col1),
        }

    for char, pos in list(new_dest.items()):
        if old_char := _get_key(*pos):
            if old_char != char:
                raise ValueError(
                    f"new char {char!r} tries to override existing {old_char!r}"
                    f" at position {pos!r}"
                )
            else:
                # An existing validated key should be discarded from the "to add"
                #  response.
                new_dest.pop(char)

    return new_dest


def place_char(char: str) -> Generator[tuple[int, int], bool, None]:
    """Places a required character in the key table for every available position."""
    for row in range(5):
        for col in range(5):
            if _get_key(row, col):
                continue

            _set_key(row, col, value=char)
            IN_KEY[char] = row, col
            state = (yield row, col)
            if state:
                return  # stop the generator early

            _set_key(row, col, value=None)
            del IN_KEY[char]


def break_cipher(bigram_map: list[tuple[str, str]], *, index: int = 0) -> bool:
    if index >= len(bigram_map):
        return True

    # _show_key_table()
    plain_pair, crypt_pair = bigram_map[index]
    chars_in_key = lambda chrs: set(chrs) & IN_KEY.keys()  # noqa
    plain_chars, crypt_chars = tuple(map(chars_in_key, (plain_pair, crypt_pair)))

    if (max_pair := max(len(plain_chars), len(crypt_chars))) == 2:
        try:
            new_dest = validate_bigrams(
                plain_pair, crypt_pair, encrypt=len(plain_chars) == 2
            )
        except ValueError:
            # Rules can't hold true anymore in the current state.
            return False
        else:
            for char, pos in new_dest.items():
                _set_key(*pos, value=char)
                IN_KEY[char] = pos
            state = break_cipher(bigram_map, index=index + 1)
            if not state:
                for char, pos in new_dest.items():
                    _set_key(*pos, value=None)
                    del IN_KEY[char]
            return state
    elif max_pair == 1:
        target_pair, target_chars = (
            (plain_pair, plain_chars) if len(plain_chars) else (crypt_pair, crypt_chars)
        )
        missing_char = (set(target_pair) - target_chars).pop()
        char_placement = place_char(missing_char)
        next(char_placement)
        while True:
            # Keeping the same position in order to validate the complete pair.
            state = break_cipher(bigram_map, index=index)
            try:
                char_placement.send(state)
            except StopIteration:
                break
        if state:
            return state
    else:
        # There is no char on the table at all, from none of the pairs, so place the
        #  first one randomly.
        missing_char = plain_pair[0]
        char_placement = place_char(missing_char)
        next(char_placement)
        while True:
            # Keeping the same position in order to validate the complete pair.
            state = break_cipher(bigram_map, index=index)
            try:
                char_placement.send(state)
            except StopIteration:
                break
        if state:
            return state

    return False


def playfair_attack(plaintext: str, cryptogram: str) -> str:
    bigram_map = [
        (plaintext[idx : idx + 2], cryptogram[idx : idx + 2])
        for idx in range(0, len(plaintext), 2)
    ]
    # TODO(cmin764): Sort the mapping based on character frequency.
    _populate_key_lookup()  # useful when debugging hardcoded key tables
    state = break_cipher(bigram_map)
    if not state:
        raise RuntimeError("couldn't break cipher")

    _show_key_table()
    return encrypt("topsecretmessage")


if __name__ == "__main__":
    print("Example:")
    print(
        playfair_attack(
            "secret",
            "dcembk",
        )
    )
