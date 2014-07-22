#! /usr/bin/env python3.2

from urllib.request import urlopen
from time import sleep
from winsound import Beep

def connect():
    try:
        urlopen("http://www.google.com/")
        return True
    except:
        return False

def main():
    count = 0
    while True:
        count += 1
        print("Attempt #%d" % count)
        if connect():
            Beep(2100, 1000)
        sleep(11 * 60)

if __name__ == "__main__":
    main()
