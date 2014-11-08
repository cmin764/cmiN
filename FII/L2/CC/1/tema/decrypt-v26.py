#! /usr/bin/python
#
# Alin Cosmin Radu


import sys


def get_ic(chunk):
    fr = {'A': 0, 'C': 0, 'B': 0, 'E': 0, 'D': 0, 'G': 0, 'F': 0, 'I': 0, 'H': 0, 'K': 0, 'J': 0, 'M': 0, 'L': 0, 'O': 0, 'N': 0, 'Q': 0, 'P': 0, 'S': 0, 'R': 0, 'U': 0, 'T': 0, 'W': 0, 'V': 0, 'Y': 0, 'X': 0, 'Z': 0}
    s = 0
    for x in chunk:
        fr[x]+=1
    for x in fr.values():
        s+=x*(x-1)
    return round(float(s)/(len(chunk)*(len(chunk)-1)),3)

if len(sys.argv)!=2:
    print "Usage: "+sys.argv[0]+" target_file"
    exit()
    
crypt = ""
with open(sys.argv[1],"r") as txt:
    while True:
        c = txt.read(1)
        if not c:
            break;
        if ord(c) in range(65,91):
            crypt += c
cl = len(crypt)
print "---\tCryptotext\t---\n"
print crypt
print "(Length: "+str(cl)+")\n"

#m = 20;

for m in range(1,cl):
    sum = 0
    for i in range(m):
        j = 0
        chunk = ""
        ic = 0
        while (m*j+i < cl):
            chunk += crypt[m*j+i]
            j+=1
        #print chunk + "   (" + str(get_ic(chunk)) + ")"
        sum += get_ic(chunk)
    print str(m)+": "+str(float(sum)/m)
    if round(float(sum)/m,3) in (0.066,0.067):
        break
print "Length of the key: " + str(m)
