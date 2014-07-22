#! /usr/bin/env python
#
# ssps: Simple Single Port Scanner
# Copyright (C) 2012  cmiN
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Author(s): Cosmin Poieana <cmin764@yahoo.com>


import sys
import socket
import threading
import time


# some constants referring to options
THRD = 50 # how many threads
TOUT = 2 # socket timeout
OUTP = None # output file
VERB = False # verbose
USAGE = """Usage: {0} FILE PORT [OPTION]...
Scan for open PORT using hosts from FILE

Options:
    -o, --output <str>       file name to store the output
    -t, --threads <int>      number of threads, default {1}
    -T, --timeout <float>    timeout in seconds, default {2}
    -v, --verbose            see all the activity

For "can't start new thread" error try to reduce stack size:
    ulimit -s 1024
Report bugs to cmin764@yahoo.com""".format("{0}", THRD, TOUT)


def scan(host):
    # create the socket and try to connect
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rcode = sock.connect_ex((host, port))
    # critical print
    lock.acquire()
    if not rcode:
        print host + " OK"
        if OUTP:
            OUTP.write(host + "\n")
    elif VERB:
        print host
    lock.release()
    # increment the semaphore
    semaphore.release()


def strtime(wtime):
    # convert seconds to string
    sec = wtime % 60
    wtime /= 60
    mnt = wtime % 60
    hrs = wtime / 60
    return "%dh %dm %ds" % (hrs, mnt, sec)


def main(argc, argv):
    if argc == 1:
        print "Run with --help"
        return 0
    elif argv[1] in ("-h", "--help"):
        print USAGE.format(argv[0])
        return 0
    elif argc < 3:
        print "Missing argument(s)"
        return 6
    else:
        # check file
        try:
            fin = open(argv[1], "r")
        except IOError:
            print "Can't find file '%s' or read data" % argv[1]
            return 1
        # check port
        try:
            global port
            port = int(argv[2])
        except ValueError:
            print "Invalid port '%s'" % argv[2]
            return 2
        # and now the options
        ind = 3
        while ind < argc:
            if argv[ind] in ("-t", "--threads"):
                ind += 1
                if ind == argc:
                    print "Missing value"
                    return 5
                try:
                    global THRD
                    THRD = int(argv[ind])
                except ValueError:
                    print "Invalid value '%s'" % argv[ind]
                    return 3
            elif argv[ind] in ("-T", "--timeout"):
                ind += 1
                if ind == argc:
                    print "Missing value"
                    return 5
                try:
                    global TOUT
                    TOUT = float(argv[ind])
                except ValueError:
                    print "Invalid value '%s'" % argv[ind]
                    return 3
            elif argv[ind] in ("-o", "--output"):
                ind += 1
                if ind == argc:
                    print "Missing value"
                    return 5
                try:
                    global OUTP
                    OUTP = open(argv[ind], "a")
                except IOError:
                    print "Can't find file '%s' or write data" % argv[ind]
                    return 1
            elif argv[ind] in ("-v", "--verbose"):
                global VERB
                VERB = True
            else:
                print "Invalid option '%s'" % argv[ind]
                return 4
            ind += 1
        # if we get here, everything (almost) is fine
        start = time.time()
        print "Started at %s" % time.ctime()
        global lock, semaphore
        lock = threading.Lock()
        semaphore = threading.Semaphore(THRD)
        socket.setdefaulttimeout(TOUT)
        for host in fin:
            semaphore.acquire()
            threading.Thread(target=scan,
                             args=(host.strip(),)).start()
        fin.close()
        # now wait for the remaining threads
        while threading.active_count() > 1:
            pass
        if OUTP:
            OUTP.close()
        print "Ended at %s and took %s" % (time.ctime(),
                                           strtime(time.time() - start))
        return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
