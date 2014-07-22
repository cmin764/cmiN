#! /usr/bin/env python3
# redtube.com video link crawler
# 11.05.2011

import sys, urllib.request, threading

class RTC(threading.Thread):
    def __init__(self, page):
        self.page = page
        threading.Thread.__init__(self)
    def run(self):
        word = b"stat['"
        with urllib.request.urlopen("http://www.redtube.com/?page=" + str(self.page)) as uin:
            source = uin.read()
        start = source.find(b"<!-- Preparation templates -->")
        end = source.find(b"<!-- Preparation templates end -->")
        start = source.find(word, start, end)
        while start != -1:
            start = start + len(word)
            string = ""
            while source[start] != ord("'"):
                string += chr(source[start])
                start += 1
            self.fobj.write("http://www.redtube.com/" + string + "\n")
            start = source.find(word, start, end)

def main(argc, argv):
    if argc == 5:
        RTC.fobj = open(argv[1], "at")
        for page in range(int(argv[2]), int(argv[3]) + 1):
            while threading.active_count() > int(argv[4]):
                pass
            RTC(page).start()
        while threading.active_count() > 1:
            pass
        RTC.fobj.close()
    else:
        print("./rtc.py filename from to threads\n\
filename: path to a text file for storing links\n\
from: start page number\n\
to: end page number\n\
threads: how many pages to parse asinchronously\n")

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
