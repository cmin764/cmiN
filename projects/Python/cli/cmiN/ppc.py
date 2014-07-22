#! /usr/bin/env python3.1
# 09.03.2010 <> 09.03.2010 | cmiN
# Php Proxy Clicker (console)

import sys, time, urllib.request, threading

def main(args):
    usage = """\t\t Php Proxy Clicker 1.0

\t Usage: ppc.py lfile pfile requests delay timeout verbose

Where lfile is the path to a file with links
      pfile is the path to a file with proxies
      requests is an integer (how many)
      delay is a float (seconds)
      timeout is a float (seconds)
      verbose is an integer
          1 - print status
          0 - print nothing
Note: Leave the pfile empty if you want to use global settings

\t Example: ppc.py C:\\links.txt C:\\proxy.txt 10 2 5 1"""
    if len(args) == 7:
        try:
            print("Please wait...")
            process(args[1], args[2], int(args[3]), float(args[4]), float(args[5]), int(args[6]))
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
        else:
            print("Ready!")
    else:
        print(usage)
        input()

def process(lfile, pfile, requests, delay, timeout, verbose):
    headers = {"User-Agent": "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.6) Gecko/2009020911 Ubuntu/8.04 (hardy) Firefox/3.0.6"}
    Click.timeout = timeout
    Click.headers = headers
    Click.verbose = verbose
    links, hosts = list(), list()
    with open(lfile, "rt") as lfin, open(pfile, "rt") as pfin:
        for line in lfin:
            links.append(line.strip("\n"))
        for line in pfin:
            hosts.append(line.strip("\n"))
    while requests > 0:
        for link in links:
            if len(hosts):
                for host in hosts:
                    Click(link, host).start()
                    time.sleep(delay)
            else:
                Click(link, None).start()
                time.sleep(delay)
        requests -= 1
    while threading.active_count() > 1:
        pass

class Click(threading.Thread):

    timeout = int()
    headers = dict()
    verbose = int()

    def __init__(self, link, host):
        threading.Thread.__init__(self)
        self.link = link
        self.host = host

    def run(self):
        request = urllib.request.Request(self.link, headers=self.headers)
        if self.host:
            request.set_proxy(self.host, "http")
        try:
            with urllib.request.urlopen(request, timeout=self.timeout) as uin:
                uin.read()
            if self.verbose:
                print("{} {} OK".format(self.link, self.host))
        except urllib.request.URLError as message:
            if self.verbose:
                print("{} {} {}".format(self.link, self.host, self.message))

if __name__ == "__main__":
    main(sys.argv)
