import decimal

decimal.getcontext().prec = 1000000
n = 100000
s = decimal.Decimal("0")
x = 1
while n > 0:
    part1, part2 = "d0, ", "for d0 in ('1') "
    for y in range(1, x):
        part1 += "d{}, ".format(str(y))
        part2 += "for d{} in ('0', '1') ".format(str(y))
    source = "(''.join([{0}]) {1})".format(part1.strip(", "), part2.strip(" "))
    generator = eval(source)
    for z in generator:
        w = decimal.Decimal(z)
        if w % 19 == 0:
            s += w
            n -= 1
    x += 1
print(s)
input()
