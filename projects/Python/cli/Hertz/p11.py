import sys

for x in sys.argv[1:]:
    null = eval(x)
    oarray = list()
    for y in x:
        if not y in (",", "[", "]"):
            oarray.append(y)
    print(oarray)
