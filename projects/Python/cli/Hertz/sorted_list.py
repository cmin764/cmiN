import sys

array = eval(sys.argv[1])
for x in array:
    while array.count(x) > 1:
        array.remove(x)
array.sort()
print(array)
