#! /usr/bin/env python3.1
# 08.11.2009 <> 09.11.2009 | cmiN
# URL Path Finder (console) 4 pacealik @ rstcenter.com


import sys, threading, urllib.request, urllib.parse


def main():
    usage = """\t\t URL Path Finder 1.0

\t Usage: upf.py q paths start::end timeout threads

Where q is the word that are you searching for
      paths is a file with paths (like /admin /images /forum)
      start is an integer; from here begins the searching
      end is an integer; here the searching stops
      timeout is a float in seconds
      threads is an integer representing how many threads are running asynchronously

\t Example: upf.py rstcenter C:\\paths.txt 0::20 1 50"""
    args = sys.argv
    if len(args) == 6:
        try:
            print("Please wait...")
            q = args[1]
            paths = list()
            with open(args[2], "r") as fin:
                for line in fin.readlines():
                    paths.append(line.strip("\n"))
            start = int(args[3].split("::")[0])
            end = int(args[3].split("::")[1])
            timeout = float(args[4])
            threads = int(args[5])
            url = "http://www.google.com/search?q={q}&start={start}&hl=en"
            headers = {"User-Agent": "Mozilla/5.0 (compatible; MSIE 8.0)"}
            for i in range(start, end + 1):
                while threading.active_count() > threads:
                    pass
                Scan(url.format(q=q, start=str(i)), headers, timeout, paths).start()
            while threading.active_count() > 1:
                pass
            with open("links.txt", "w") as fout:
                for link in Scan.links:
                    while Scan.links.count(link) > 1:
                        Scan.links.remove(link)
                Scan.links.sort()
                for link in Scan.links:
                    fout.write(link + "\n")
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
        else:
            print("Ready!")
    else:
        print(usage)
    input()


class Scan(threading.Thread):

    links = list()

    def __init__(self, url, headers, timeout, paths):
        threading.Thread.__init__(self)
        self.url = url
        self.headers = headers
        self.timeout = timeout
        self.paths = paths

    def run(self):
        request = urllib.request.Request(self.url, headers=self.headers)
        with urllib.request.urlopen(request, timeout=self.timeout) as usock:
            source = usock.read()
            source = source[source.find(b"Search Results"):]
            source = source[:source.find(b"</a>")]
            source = source.decode()
        url = source[source.find("http://"):]
        url = url[:url.find('"')]
        uparser = urllib.parse.urlparse(url)
        url = "{scheme}://{netloc}".format(scheme=uparser.scheme, netloc=uparser.netloc)
        for path in self.paths:
            request = urllib.request.Request(url + path, headers=self.headers)
            try:
                with urllib.request.urlopen(request, timeout=self.timeout) as usock:
                    Scan.links.append(usock.geturl())
            except:
                pass
                

if __name__ == "__main__":
    main()
