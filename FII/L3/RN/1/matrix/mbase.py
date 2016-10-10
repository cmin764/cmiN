"""Base module for both scripts."""


import re


_COEF = r"([+-]?\d+)"
REGEX = r"{coef}x{coef}y{coef}z={coef}".format(coef=_COEF)


def parse(fname):
	# Parse input.
    with open(fname, "rb") as stream:
        data = stream.read()
    mat = []
    vec = []
    for line in data.strip().splitlines():
        line = line.strip().replace(" ", "")
        match = re.match(REGEX, line)
        if not match:
            return None
        a, b, c, r = match.groups()
        mat.append(list(map(float, [a, b, c])))
        vec.append(float(r))
    return mat, vec


def main(argv):
    if len(argv) != 2:
        print("[i] Usage: {} {}".format(argv[0], "FILE"))
        return 1
    
    ret = parse(argv[1])
    if not ret:
        print("[x] Invalid expression: {}".format(line))
        return 2

    res = solve(*ret)
    if not res:
        print("[x] Couldn't solve")
        return 3

    print("x={0}, y={1}, z={2}".format(*res))
    return 0
