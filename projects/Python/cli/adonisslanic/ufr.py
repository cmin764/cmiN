#! /usr/bin/env python
# 29.06.2009 <> 29.06.2009 | cmiN
# URL-File-Reader 4 adonisslanic @ rstcenter.com


import os, sys, urllib2, urlparse


def main():
    args=sys.argv
    if len(args) != 2:
        print("\tUsage:\n\n\
\tufr.py http://www.site.com/path/file\n\n\
Press any key to exit. . .\n\n\n")
    else:
        print("Please wait...\n\n")
        url=args[1]
        splited_path=urlparse.urlsplit(url).path.split("/")
        filename=splited_path[len(splited_path)-1]
        sock=urllib2.urlopen(url)
        source=sock.read()
        sock.close()
        f=file(filename, "w")
        f.write(source)
        f.close()
        print("Ready! Check %s." % filename)


if __name__=="__main__":
    try:
        main()
    except:
        print("Invalid URL or timed out!")
    os.system("pause >NUL")
