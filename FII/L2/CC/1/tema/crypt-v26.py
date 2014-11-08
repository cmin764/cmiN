#! /usr/bin/python
#
# Alin Cosmin Radu


import sys

if len(sys.argv) not in (3, 4):
    print "Usage: " + sys.argv[0] + " input key [output]"
    exit()


plain = ""
key = ""

# --- filtrare
with open(sys.argv[1]) as txt:
    while True:
        c = txt.read(1)
        if not c:
            break;
        if ord(c) in range(97,123):
            plain += chr(ord(c)-32)
        elif ord(c) in range(65,91):
            plain += c

for c in sys.argv[2]:
    if ord(c) in range(97,123):
        key += chr(ord(c)-32)
    elif ord(c) in range(65,91):
        key += c
# --- /

crypt = ""
i = 0
for x in plain:        
    crypt += chr(((ord(x)+ord(key[i%len(key)]))%26)+65)        
    i+=1
    

print "\n---\tPlaintext\t---"
print plain
print "\n---\tCryptokey\t---"
print key
print "\n---\tCryptotext\t---"
print crypt
print "\n"
if len(sys.argv) == 4:
    out = open(sys.argv[3],"w")
    out.write(crypt)
    out.close()
    print "Cryptotext wrote in file: " + sys.argv[3]
