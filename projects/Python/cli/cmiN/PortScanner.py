#! /usr/bin/env python3.1
# 13.09.2009 <> 14.09.2009 | cmiN
# Port Scanner (console)


import sys, threading, socket
from winsound import Beep


class Scan(threading.Thread):

    def __init__(self, ip, port):
        threading.Thread.__init__(self)
        self.ip = ip
        self.port = port
            
    def run(self):
        result = socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect_ex((self.ip, self.port))
        if not result:
            print("{}:{}".format(self.ip, str(self.port)))
            Beep(2000, 1000)

            
class PS:
    
    def __init__(self, args):
        usage = """\t\t Port Scanner 1.0

\t Usage: PortScanner.py ip_range_or_list port_range_or_list timeout

Where ip_range_or_list is the IP range separated by "::" or the file path to a list with IPs
      port_range_or_list is the PORT range separated by "::" or the file path to a list with PORTs
      timeout is a float (seconds)

\t Example: PortScanner.py C:\path\ip_list.txt 135::135 0.1"""
        MAX_THREADS = 50
        if len(args) == 4:
            try:
                print("Please wait...")
                self.update(args[1], args[2], float(args[3]))
                for ip in self.ip_generator:
                    for port in self.port_generator:
                        while threading.activeCount() > MAX_THREADS:
                            pass
                        Scan(ip, port).start()
            except Exception as message:
                print("An error occurred: {}".format(message))
            except:
                print("Unknown error.")
            else:
                print("Ready!")
            finally:
                while threading.activeCount() > 1:
                    pass
        else:
            print(usage)
        input()
    
    def update(self, ip, port, timeout):
        socket.setdefaulttimeout(timeout)
        if ip.count("::") == 1:
            ip_start, ip_end = ip.split("::")[0], ip.split("::")[1]
            a1, b1, c1, d1 = int(ip_start.split(".")[0]), int(ip_start.split(".")[1]), int(ip_start.split(".")[2]), int(ip_start.split(".")[3])
            a2, b2, c2, d2 = int(ip_end.split(".")[0]), int(ip_end.split(".")[1]), int(ip_end.split(".")[2]), int(ip_end.split(".")[3])
            self.ip_generator = (".".join([str(a), str(b), str(c), str(d)]) for a in range(a1, a2 + 1)  for b in range(b1, b2 + 1)  for c in range(c1, c2 + 1)  for d in range(d1, d2 + 1))
        else:
            self.ip_generator = (line.strip("\n") for line in open(ip, "r"))
        if port.count("::") == 1:
            port_start, port_end = int(port.split("::")[0]), int(port.split("::")[1])
            self.port_generator = (n for n in range(port_start, port_end + 1))
        else:
            self.port_generator = (int(line.strip("\n")) for line in open(port, "r"))


if __name__ == "__main__":
    PS(sys.argv)
