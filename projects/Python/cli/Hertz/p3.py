import sys

for x in sys.argv[1:]:
    nr = int(x)
    n = 1
    while str(n * nr)[0:5] != str(11111):
        n += 1
    print (n * nr)
