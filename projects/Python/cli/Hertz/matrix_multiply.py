import sys

matrices = eval(sys.argv[1])
a, b = matrices[0], matrices[1]
status = True
if len(a) != len(b):
    status = False
else:
    for i in range(len(a)):
        if len(a[i]) != len(b[i]):
            status = False
if status:
    last = list()
    result = list()
    for i in range(len(a)):
        for j in range(len(a[i])):
            result.append(a[i][j] * b[i][j])
        last.append(result)
    print(last)
else:
    print(False)
