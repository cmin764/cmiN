def ascii_sum(text):
    return sum(ord(text[i]) for i in range(1, len(text), 2))


def combine_dicts(d1, d2):
    d = {}
    for k, v in d1.items():
        if k in d2:
            v += d2[k]
        d[k] = v
    for k, v in d2.items():
        if k not in d1:
            d[k] = v
    return d


def sort_tuples(s):
    _dist = lambda a, b: (a ** 2 + b ** 2) ** 0.5
    return sorted(s, key=lambda arg: _dist(*arg))


assert ascii_sum("Hello-world") == 473
assert (combine_dicts(d1={1: "a", 2: "b"},
    d2={1: "x", "y":"y"}) == {1: "ax", 2: "b", "y": "y"})
assert (sort_tuples({(1,1), (10, 10), (3, 2)})
        == [(1, 1), (3, 2), (10, 10)])
