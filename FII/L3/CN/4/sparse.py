#! /usr/bin/env python


import logging


EPS = 10 ** -8
LOG_LEVEL = logging.DEBUG
SIMPLE = False
S = ""
if SIMPLE:
    S = "s"

FILE_A = "{}a.txt".format(S)
FILE_B = "{}b.txt".format(S)
FILE_APB = "{}aplusb.txt".format(S)
FILE_AOB = "{}aorib.txt".format(S)


def is_zero(nr):
    if abs(nr) < EPS:
        return True
    return False


def reader(path):
    with open(path) as stream:
        for line in stream:
            idx = line.find("#")
            if idx != -1:
                line = line[:idx]
            line = line.strip()
            if line:
                yield line


class Matrix(object):

    def __init__(self, dim):
        self.dim = dim
        self.diagonal = []
        self.values = []
        self.zindex = {}
        self._raw = {}
        self.length = None

    def put(self, val, lin, col):
        if is_zero(val):
            return
        value = self._raw.setdefault(lin, {}).setdefault(col, 0) + val
        self._raw[lin][col] = value

    def finish(self, check_lengths=False):
        zeros = 0
        for lin in sorted(self._raw):
            addzero = True
            cols = self._raw[lin]
            cols_len = len(cols)
            if check_lengths and cols_len > 10:
                logging.warn("%d elemente pe linie", cols_len)
            for col, val in cols.items():
                if lin == col:
                    # Fill diagonal.
                    miss = lin - len(self.diagonal)
                    self.diagonal.extend([0] * miss)
                    self.diagonal.append(val)
                else:
                    # Fill the values vector.
                    miss = max(lin - zeros, 0)
                    zeros = lin + 1
                    self.values.extend([
                        (-idx, 0) for idx in
                        range(lin - miss, lin)
                    ])
                    if addzero:
                        addzero = False
                        self.values.append((-lin, 0))
                        self.zindex[lin] = len(self.values)
                    self.values.append((col, val))
        self.diagonal.extend([0] * (self.dim - len(self.diagonal)))
        self.length = len(self.values)
        self._raw.clear()

    def has_line(self, lin):
        return lin in self.zindex

    def get_line(self, lin, sparse=False):
        values = []
        val = self.diagonal[lin]
        if val:
            values.append((lin, val))
        idx = self.zindex.get(lin)
        if idx is not None:
            while idx < self.length:
                col, val = self.values[idx]
                idx += 1
                if not val:
                    break    # s-a terminat linia curenta
                values.append((col, val))

        if sparse:
            return dict(values)

        line = [0] * self.dim
        for col, val in values:
            line[col] = val
        return line

    def __repr__(self):
        return "<Matrix {}>".format(self.dim)

    def __str__(self):
        return "<Matrix {} {}>".format(len(self.diagonal), len(self.values))

    def __getitem__(self, pos):
        lin, col = pos
        if lin == col:
            return self.diagonal[lin]
        idx = self.zindex.get(lin)
        if idx is None:
            return 0    # nu avem elemente pe aceasta linie
        while idx < self.length:
            _col, val = self.values[idx]
            idx += 1
            if not val:
                break    # s-a terminat linia curenta
            if col == _col:
                return val
        return 0    # nu am gasit coloana cautata


def vec_sum(a, b):
    alen, blen = len(a), len(b)
    diff = abs(alen - blen)
    if diff:
        ext = [0] * diff
        if alen < blen:
            a.extend(ext)
        else:
            b.extend(ext)
    r = []
    for idx, elem in enumerate(a):
        r.append(elem + b[idx])
    return r


def mat_sum(a, b):
    assert a.dim == b.dim
    r = Matrix(a.dim)
    for lin in range(r.dim):
        aline = a.get_line(lin)
        bline = b.get_line(lin)
        rline = map(sum, zip(aline, bline))
        for col, val in enumerate(rline):
            r.put(val, lin, col)
    r.finish()
    return r


def mat_mul(a, b):
    """Multiply A with B^t."""
    assert a.dim == b.dim
    r = Matrix(a.dim)
    # Cache-uim liniile transpuse (coloanele) matricii B.
    blines = {}
    for blin in range(r.dim):
        bline = b.get_line(blin, sparse=True)
        blines[blin] = bline
    # Incepem inmultirea folosind doar linii chele.
    for alin in range(r.dim):
        aline = a.get_line(alin, sparse=True)
        for blin in range(r.dim):
            bline = blines[blin]
            rline = []
            for col, val in aline.items():
                _val = bline.get(col)
                if _val:
                    rline.append(val * _val)
            value = sum(rline)
            r.put(value, alin, blin)
    r.finish()
    return r


def mat_vec_mul(a, b):
    assert a.dim == len(b)
    r = [0] * a.dim
    # Incepem inmultirea folosind doar linii chele.
    for alin in range(a.dim):
        aline = a.get_line(alin, sparse=True)
        bline = b
        rline = []
        for col, val in aline.items():
            _val = bline[col]
            if _val:
                rline.append(val * _val)
        value = sum(rline)
        r[alin] = value
    return r


def mat_equal(a, b):
    assert a.dim == b.dim
    for lin in range(a.dim):
        aline = a.get_line(lin)
        bline = b.get_line(lin)
        if aline != bline:
            return False
    return True


def read_vecmat(path, name="unknown", trans=False, check_lengths=False):
    # Citim vectorul.
    info = reader(path)
    dim = int(next(info))
    vec = []
    mat = Matrix(dim)
    for _ in range(dim):
        vec.append(float(next(info)))
    logging.debug("%s vector length: %d", name, len(vec))
    # Citim matricea si o post-procesam.
    count = 0
    for row in info:
        count += 1
        chunks = map(str.strip, row.split(","))
        val, (lin, col) = float(chunks[0]), map(int, chunks[1:])
        if trans:    # salvam transpus
            lin, col = col, lin
        mat.put(val, lin, col)
    logging.debug("%s matrix entries: %d", name, count)
    mat.finish(check_lengths=check_lengths)
    logging.debug("%s matrix: %r %s", name, mat, mat)
    return vec, mat


def main():
    logging.basicConfig(level=LOG_LEVEL)

    # Citim datele de intrare.
    avec, amat = read_vecmat(FILE_A, name="A", check_lengths=True)
    bvec, bmat = read_vecmat(FILE_B, name="B", check_lengths=True)
    _, tbmat = read_vecmat(FILE_B, name="TB", trans=True)    # B transpus
    # Si cele de iesire.
    pvec, pmat = read_vecmat(FILE_APB, name="P")
    ovec, omat = read_vecmat(FILE_AOB, name="O")

    # Verificari pentru depanare.
    assert amat[0, 0] == 141.5
    assert amat[26, 26] == 134.5
    assert amat[1625, 750] == 48
    assert amat[1625, 749] == 0

    assert bmat[0, 0] == 302.5
    assert bmat[26, 26] == 119.5
    assert bmat[1625, 750] == 0
    assert bmat[1625, 749] == 0

    # # Adunam efectiv vectorii.
    # rvec = vec_sum(avec, bvec)
    # logging.info("R vector length: %d", len(rvec))
    # logging.info("R vector[0]: %f", rvec[0])
    # logging.info("R vector[-1]: %f", rvec[-1])
    # # Si facem verificarea.
    # assert pvec == rvec

    # Adunam matricile.
    rmat = mat_sum(amat, bmat)
    logging.info("R plus matrix: %r %s", rmat, rmat)
    # Si le verificam continutul.
    assert mat_equal(pmat, rmat)

    # Inmultim matricile.
    rmat = mat_mul(amat, tbmat)
    logging.info("R ori matrix: %r %s", rmat, rmat)
    # Si le verificam continutul.
    assert mat_equal(omat, rmat)

    # Inmultirea matricii cu un vector.
    xvec = list(map(float, range(amat.dim, 0, -1)))
    rvec = mat_vec_mul(amat, xvec)
    logging.info("R ori vector[0]: %f", rvec[0])
    assert avec == rvec


if __name__ == "__main__":
    main()
