import sys

for x in sys.argv[1:]:
    nr = int(x)
    array = list()
    n = 2
    while nr != 1:
        if nr % n == 0:
            array.append(n)
            nr /= n
        else:
            n += 1
    output = 0
    for y in range(1, int(x)):
        status = True
        for z in array:
            if y % z == 0:
                status = False
        if status:
            output += 1
    print(output)
