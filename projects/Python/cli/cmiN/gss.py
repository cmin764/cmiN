#! /usr/bin/env python3.1
# 12.03.2010 <> 12.03.2010 | cmiN
# Google Search Script (console)

import sys, threading, urllib.request, urllib.parse

def main(args):
    usage = """\t\t Google Search Script 1.0

\t Usage: gss.py query lfile start end timeout threads

Where query is the string that are you searching for
      lfile is the file in which the links will be stored
      start is an integer (from here the search begins)
      end is an integer (here the search stops)
      timeout is a float (seconds)
      threads is an integer representing how many threads are running asynchronously

\t Example: gss.py rst links.txt 0 10 1 50"""
    if len(args) == 7:
        try:
            print("Please wait...")
            process(args[1], args[2], int(args[3]), int(args[4]), float(args[5]), int(args[6]))
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
        else:
            print("Ready!")
    else:
        print(usage)
        input()
        
def process(query, lfile, start, end, timeout, threads):
    GS.query = query
    GS.timeout = timeout
    GS.headers = {"User-Agent": "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.6) Gecko/2009020911 Ubuntu/8.04 (hardy) Firefox/3.0.6"}
    for result in range(start, end):
        while threading.active_count() > threads:
            pass
        GS(str(result)).start()
    while threading.active_count() > 1:
        pass
    with open(lfile, "wt") as fout:
        for link in GS.links:
            fout.write(link)

class GS(threading.Thread):

    link = "http://www.google.com/search?q={}&start={}"
    links = list()
    headers = dict()
    query = str()
    timeout = float()

    def __init__(self, result):
        threading.Thread.__init__(self)
        self.result = result

    def run(self):
        request = urllib.request.Request(self.link.format(self.query, self.result), headers=self.headers)
        with urllib.request.urlopen(request, timeout=self.timeout) as uin:
            source = uin.read()
        source = source[source.find(b"Search Results"):]
        source = source[:source.find(b"</a>")]
        source = source[source.find(b"http://"):]
        source = source[:source.find(b'"')]
        uparser = urllib.parse.urlparse(source.decode())
        url = "{scheme}://{netloc}\n".format(scheme=uparser.scheme, netloc=uparser.netloc)
        self.links.append(url)

if __name__ == "__main__":
    main(sys.argv)
