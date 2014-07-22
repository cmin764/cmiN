#! /usr/bin/env python
# 05.09.2010 <> 05.09.2010 | cmiN
# IEHistoryView Parser 4 Flubber @ rstcenter.com

import urllib

def main():
    # settings
    fname = "log.txt" # name of the text file to be parsed
    dname = "links.txt" # destination file
    ul = 3 # starting url line
    sv = 10 # step value
    dl = True # download links
    ph = "http://anonymouse.org/cgi-bin/anon-www.cgi/" # can be also ""
    # end
    fobj = open(fname, "rt")
    lines = fobj.readlines()
    fobj.close()
    fobj = open(dname, "wt")
    lnlen = len(lines)
    for x in xrange(ul, lnlen, sv):
        fobj.write(lines[x].strip("URL :"))
    fobj.close()
    if dl:
        process(dname, ph)
    return 0
    
def process(dname, ph):
    fobjin = open(dname, "rt")
    for link in fobjin:
        chunks = link.strip("\n").split("/")
        fobjout = open(chunks[len(chunks) - 1], "wb")
        fobjout.write(urllib.urlopen(ph + link.strip("\n")).read())
        fobjout.close()
    fobjin.close()
    
if __name__ == "__main__":
    main()
