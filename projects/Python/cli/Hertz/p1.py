import sys

for x in sys.argv[1:]:
    iarray = eval(x)
    oarray = list()
    while len(iarray) > 0:
        for y in iarray[:]:
            if not hasattr(y, "append"):
                oarray.append(y)
                iarray.remove(y)
        tarray = list()
        for y in iarray:
            tarray.extend(y)
        iarray = tarray
    oarray.sort()
    print(oarray)
