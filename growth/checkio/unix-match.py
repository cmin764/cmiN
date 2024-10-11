import re


def unix_match(filename: str, pattern: str) -> bool:
    tokens = list(pattern)
    re_map = {
        "*": r"[\w\W]*",
        ".": r"\.",
        "?": r"[\w\W]{1}",
    }
    for idx, token in enumerate(tokens):
        if repl := re_map.get(token):
            tokens[idx] = repl
    pattern_re = re.compile(rf"^{''.join(tokens)}$")
    return bool(pattern_re.match(filename))


def _adjust_pattern(match: re.Match) -> str:
    pattern = str(match.group())
    pattern = pattern.replace("[!", "[^")
    if pattern == "[]":
        return ""
    elif pattern == "[^]":
        return "[!]"
    return pattern


def unix_match2(filename: str, pattern: str) -> bool:
    pattern = re.sub(r"\[[\w\W]+\]", _adjust_pattern, pattern)
    if "[]" in pattern:
        return False
    if pattern == filename:
        return True
    pattern_re = re.compile(rf"^{pattern}$")
    return bool(pattern_re.match(filename))


#
# print("Example:")
# print(unix_match("somefile.txt", "*"))
#
# # # These "asserts" are used for self-checking
# assert unix_match("somefile.txt", "*") == True
# assert unix_match("other.exe", "*") == True
# assert unix_match("my.exe", "*.txt") == False
# assert unix_match("log1.txt", "log?.txt") == True
# assert unix_match("log12.txt", "log?.txt") == False
# assert unix_match("log12.txt", "log??.txt") == True
#
# print("The mission is done! Click 'Check Solution' to earn rewards!")


print("Example:")
assert unix_match2("nametxt", "name[]txt") == False
assert unix_match2("[!]check.txt", "[!]check.txt") == True
# assert unix_match2("log1.txt", "log[1234567890].txt") == True
# assert unix_match2("log1.txt", "log[!1].txt") == False
