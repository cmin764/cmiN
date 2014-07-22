#! /usr/bin/env python
# 09.08.2009 <> 09.08.2009 | cmiN
# Challenge [Programare] Pi (Hertz) @ rstcenter.com


import urllib2
from multiprocessing import Pool, freeze_support


def main():
    url = "http://www.exploratorium.edu/pi/Pi10-6.html"
    sock = urllib2.urlopen(url)
    source = sock.read()
    sock.close()
    source = source.replace(" ", "")
    source = source.replace("\n", "")
    source = source[source.index("3.1415926535"):]
    digits = source[2:1000002]
    del url, sock, source
    maxlen = 0
    for x in digits.split("9"):
        if len(x) > maxlen:
            maxlen = len(x)
            sequence = x
    return (maxlen, sequence)


def cb((maxlen, sequence)):
    print("The length of the longest sequence is %s and the sequence is: \n\
%s" % (maxlen, sequence))
    

if __name__ == "__main__":
    freeze_support()
    pool = Pool(2)
    pool.apply_async(main, callback = cb)
    input("Please wait...\n")
