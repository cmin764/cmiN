#! /usr/bin/env python3.1


import urllib.request, urllib.parse, os


def main():
    url = "http://www.wechall.net/challenge/can_you_readme/gimme.php"
    sessionid = "e6ce089dca77414e9ce990eb508bf9e6"
    headers = {"Cookie": "PHPSESSID={};".format(sessionid),
               "Referer": "http://www.wechall.net/",
               "User-Agent": "Mozilla/4.0 (compatible; MSIE 6.0)"}
    request = urllib.request.Request(url=url, headers=headers)
    with open("read.png", "wb") as fout, urllib.request.urlopen(request) as usock:
        fout.write(usock.read())
    os.system("START /REALTIME /WAIT ConvertImage\\ConvertImage.exe /S read.png /T {}\\read.jpg".format(os.getcwd()))
    os.system("START /REALTIME /WAIT djpeg.exe -greyscale -dither none read.jpg read.pnm")
    os.system("START /REALTIME /WAIT gocr.exe -i read.pnm -o read.txt")
    with open("read.txt", "r") as fin:
        url = urllib.parse.urljoin(url, "index.php?solution={}".format(fin.read().strip("\n")))
        request = urllib.request.Request(url=url, headers=headers)
        print(url)
        with urllib.request.urlopen(request) as usock:
            print(usock.read(200))
    input()


if __name__ == "__main__":
    main()
