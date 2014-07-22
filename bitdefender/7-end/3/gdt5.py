#! /usr/bin/env python


hexDump = "51 75 74 69 75 70 7A 2F 84 82 81 8D 7E 7F 3D 59 65 43 73 90 8C 90 4D 5B 51 A5 9A 98 A5 B4 5D 8D AA A6 AA 67 83 44"
hexDump = hexDump.split()

result = list()
for i in xrange(len(hexDump)):
    val = int(hexDump[i], 16) - (2 * i + 1)
    if val < 0:
        val += 256
    result.append(chr(val))

print "".join(result)
