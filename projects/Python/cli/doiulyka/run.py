#! /usr/bin/env python
# Shell Multi Runner
# 12.02.2012 cmiN
#
# Execute commands in terminal asynchronously using subprocess
# and show all output merged into one console.
#
# Contact: cmin764@yahoo/gmail.com


import subprocess # better than popen/system/respawn
from sys import argv, stdout
from time import sleep
from threading import active_count, Thread # parallelism


# some settings
FILE = None     # output to file too
THRD = 10       # threads
DLAY = 1        # delay
CHAR = '@'      # wildcard


# instantiated in only one object
class Show(file):
    """
    Thread safe printing class.
    Uses primitive locks.
    """

    def __init__(self, fname=None):
        """ If `fname` isn't `None` write output to file too. """
        self.locked = False # unlocked
        self.open_file(fname)

    def __del__(self):
        """ Destructor. Close an opened file. """
        if self.fname:
            self.close()

    def open_file(self, fname):
        """ Open file for writing. """
        self.fname = fname
        if fname: # init file
            super(Show, self).__init__(fname, 'w')

    def write(self, data):
        """ Safe write. """
        while self.locked: # if writing in progress
            pass # wait
        # lock
        self.locked = True
        # write data
        if self.fname:
            super(Show, self).write(data)
        stdout.write(data)
        # flush data
        if self.fname:
            self.flush()
        stdout.flush()
        # release
        self.locked = False

    def fileno(self):
        """ Experimental. Used as file descriptor replacing pipes. """
        if self.fname:
            return super(Show, self).fileno()
        return stdout.fileno()


class Engine(Thread):
    """
    Execute each command in a separate thread
    and listen for its output.
    """

    def __init__(self, command):
        super(Engine, self).__init__() # superclass constructor
        self.command = command

    def run(self):
        """ Function called from outside by `start` method. """
        # fork the fucking process
        pobj = subprocess.Popen(self.command.split(), stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        # listen for new input
        while True:
            line = pobj.stdout.readline()
            if line == "": # more output it's about to come
                if pobj.poll() != None: # nope
                    break # so exit
                continue # try again
            report.write(line)


# globals
usage = """
Usage: {0} [options] command

Options:
    -t, --threads <int>        how many asynchronous threads to run
    -d, --delay <float>        time in seconds to wait between each run
    -f, --file <str>           write output to file too

Commands:
    <any valid command>        ex: wget {1}links.txt

If you preceed a parameter with {1} it becomes a list with parameters
taken from a file called like itself.
Old: ./scan -h 91.202.91.119 -u usr.txt -p pwd.txt
New: {0} ./scan -h {1}hosts.txt -u usr.txt -p pwd.txt
""".format(argv[0], CHAR)
report = Show() # make verbose object


def generate(command, expand, pos):
    """ Format command recursively. """
    if pos == len(expand):
        # now command string is complete
        sleep(DLAY) # delay
        while active_count() > THRD:
            pass # wait if number of threads is exceeded
        report.write("[+] Start: %s\n" % command)
        Engine(command).start()
        return
    expand[pos].seek(0) # rewind
    for line in expand[pos]:
        generate(command.replace("{%d}" % pos, line.strip()), expand, pos + 1)


def main():
    global FILE, THRD, DLAY, CHAR
    # check
    if len(argv) == 1 or argv[1] in ('-h', "--help"):
        print usage
        return # insuficient parameters
    # parse
    report.write("[+] Parsing...\n")
    argv.pop(0) # remove script name
    command = ""
    ind = 0 # index
    expand = [] # list with special parameters
    while ind < len(argv):
        if argv[ind] in ('-t', "--threads"):
            ind += 1
            THRD = int(argv[ind])
        elif argv[ind] in ('-d', "--delay"):
            ind += 1
            DLAY = float(argv[ind])
        elif argv[ind] in ('-f', "--file"):
            ind += 1
            FILE = argv[ind]
            report.open_file(FILE)
        elif argv[ind][0] == CHAR:
            # reserve variable parameter for special ones
            command += ' ' + "{%d}" % (len(expand))
            # add to list special parameters (`CHAR`<smth>)
            expand.append(open(argv[ind][1:], 'r')) # file objects
        else:
            command += ' ' + argv[ind]
        ind += 1
    # process
    report.write("[+] Processing...\n")
    generate(command.strip(), expand, 0)
    while active_count() > 1:
        pass # wait for running threads
    report.write("[+] Done.\n")


if __name__ == "__main__":
    main()
