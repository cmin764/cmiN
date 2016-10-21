"""Base module for both scripts."""


import re


_COEF = r"[+-]?\d*"
REGEX = r"({coef}x|)({coef}y|)({coef}z|)=({coef})".format(coef=_COEF)


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
        x, y, z, r = match.groups()
        cfs = [x, y, z]
        for idx, cf in enumerate(cfs):
            if not cf:
                cfs[idx] = cf
                continue
            cf = cf.rstrip("xyz")
            if not cf or not cf[-1].isdigit():
                cf += "1"
            cfs[idx] = cf
        mat.append(list(map(lambda arg: float(arg) if arg else 0.0, cfs)))
        vec.append(float(r) or 0.0)
    return mat, vec


def main(argv):
    if len(argv) != 2:
        print("[i] Usage: {} {}".format(argv[0], "FILE"))
        return 1
    
    ret = parse(argv[1])
    if not ret:
        print("[x] Invalid expression")
        return 2

    res = solve(*ret)
    if not res:
        print("[x] Couldn't solve")
        return 3

    print("x={0}, y={1}, z={2}".format(*res))
    return 0
