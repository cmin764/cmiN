#! /usr/bin/env python
# 20.06.2010 <> 20.06.2010 | cmiN
# [concurs] 1 milion useri twitter

import threading, urllib2
from time import sleep
from os import linesep

def main():
    threads = 50
    count = 1000
    while len(Crawl.users) < count:
        while threading.active_count() > threads:
            sleep(1)
        Crawl().start()
    while threading.active_count() > 1:
        sleep(1)
    fout = open("users.txt", "at")
    for x in Crawl.users:
        fout.write(x + linesep)
    fout.close()
    return 0
    
class Crawl(threading.Thread):

    users = set()
    string = '<span class="hc-username">@<a href="/'
    length = len(string)
    timeout = 10

    def __init__(self):
        threading.Thread.__init__(self)
        
    def run(self):
        try:
            fin = urllib2.urlopen("http://twitter.com", timeout=self.timeout)
            source = fin.read()
            fin.close()
            index = 0
            while True:
                index = source.find(self.string, index + self.length)
                if index == -1:
                    break
                user = source[index + self.length:source.find('"', index + self.length)]
                self.users.add(user.decode())
        except Exception as message:
            print message

if __name__ == "__main__":
    main()
