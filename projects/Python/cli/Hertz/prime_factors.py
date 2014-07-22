import sys

args = sys.argv
for number in args[1:]:
    x = int(number)
    array = list()
    n = 2
    while x != 1:
        if x % n == 0:
            array.append(n)
            x /= n
        else:
            n += 1
    array.sort()
    print(array)
