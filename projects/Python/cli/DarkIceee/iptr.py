#! /usr/bin/env python3.2
# Ip Tracer
# 23.01.2011 cmiN

import sys, urllib.request

class IPScan:
    def __init__(self, iplist, timeout):
        self.ipdetailslist = list()
        self.link = "http://whatismyipaddress.com/ip/"
        self.iplist = iplist
        self.timeout = timeout
        self.headers = {"User-Agent": "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.6) Gecko/2009020911 Ubuntu/8.04 (hardy) Firefox/3.0.6"}

    def parse(self, source):
        if source.find(b"Invalid IP address.") != -1:
            return ["invalid", "invalid", "invalid", "invalid"]
        index = source.find(b"ISP:</th><td>") + len(b"ISP:</th><td>")
        source = source[index:]
        isp = source[:source.find(b"</td>")]
        index = source.find(b"Country:</th><td>") + len(b"Country:</th><td>")
        source = source[index:]
        country = source[:source.find(b"</td>")]
        index = source.find(b"State/Region:</th><td>") + len(b"State/Region:</th><td>")
        source = source[index:]
        state = source[:source.find(b"</td>")]
        index = source.find(b"City:</th><td>") + len(b"City:</th><td>")
        source = source[index:]
        city = source[:source.find(b"</td>")]
        if country.find(b" <img") != -1:
            country = country[:country.find(b" <img")]
        datain = [country, state, city, isp]
        dataout = list()
        for word in datain:
            if word == b"":
                dataout.append("None")
            else:
                string = str()
                for char in word:
                    string += chr(char)
                dataout.append(string)
        return dataout

    def scan(self):
        for ip in self.iplist:
            print(ip + "...")
            urlrequest = urllib.request.Request(self.link + ip, headers=self.headers)
            urlobj = urllib.request.urlopen(urlrequest, timeout=self.timeout)
            self.ipdetailslist.append([ip] + self.parse(urlobj.read()))
            urlobj.close()
        print()

def process(inp, outp, verbose, timeout):
    iplist = list()
    if inp.count(".") == 3:
        iplist.append(inp)
    else:
        fobj = open(inp, "rt")
        iplist.extend(fobj.read().split())
        fobj.close()
    if outp == "stdout":
        fobj = sys.stdout
        flag = False
    else:
        fobj = open(outp, "wt")
        flag = True
    rangelist = [0]
    for char in verbose:
        rangelist.append(int(char))
    scanobj = IPScan(iplist, float(timeout))
    scanobj.scan()
    for ipdetails in scanobj.ipdetailslist:
        string = " ".join([ipdetails[i] for i in rangelist])
        print(string, file=fobj)
    if flag:
        fobj.close()

def main(args):
    usage = "iptr.py input output verbose timeout\n\
input - stdin or a file (91.202.90.81 or ips.txt)\n\
output - stdout or a file (stdout or loc.txt)\n\
verbose - country, state, city, ISP (1, 2, 3, 4)\n\
timeout - float\n\
Example: iptr.py ips.txt stdout 342 5\n"
    if len(args) != 5:
        print(usage)
        return 1
    else:
        process(args[1], args[2], args[3], args[4])
        return 0

if __name__ == "__main__":
    main(sys.argv)
