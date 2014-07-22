#! /usr/bin/env python
#
# xhosts:   main script with both cli and gui support
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
# Author: Cosmin Poieana <cmin764@yahoo.com>


import sys

from editor import HostsManager
from crawler import Crawler, HTTPError
from ui import Gui


USAGE = """
Usage: %s [OPTION] COMMAND...
Show and edit entries from hosts file, also search for hostnames on the web.

Options:
    -h, --help          show this help message and exit
    -p, --power         affect the number of search results

Commands:
    list                load and print all entries from hosts
    add SRC DEST        redirect SRC to DEST
    remove SRC          remove SRC mapping
    search KEY          search for KEY over the internet and print websites

Report bugs to cmin764@yahoo.com
Author:    Cosmin "cmiN" Poieana
Home page: https://github.com/cmin764/xhosts
License:   GPLv3
"""


class ParseError(Exception):
    """Custom error class for parsing exceptions."""

    def __init__(self, *args, **kwargs):
        """Behave like the superclass."""
        super(ParseError, self).__init__(*args, **kwargs)


class Core(object):
    """Main class of the program.

    Here we define methods to handle hosts file
    for services like reading, adding and removing
    entries for redirecting (hostname resolving) purposes.
    All this with web support, that means you can type
    a keyword and receive sites referring to it.
    """

    def __init__(self):
        # preparing core objects
        self.sites = set() # search results
        self.manager = HostsManager() # edit entries
        self.grabber = Crawler() # search the web
        self.manager.load()

    def list_entries(self):
        """Load the current entries from hosts file and return them.
        Returns the entries (a list of pairs).
        """
        self.manager.load()
        return self.manager.get_hosts().iteritems() # [(), ...]

    def add_entry(self, src, dest):
        """Add entry to hosts buffer.
        Returns: 1 -> if the entry was new
                 2 -> if already there (and replaced)
        """
        return self.manager.add(src, dest)

    def remove_entry(self, src):
        """Remove entry from hosts buffer.
        Returns: True -> if source found and removed
                 False -> if source not found
        """
        return self.manager.remove(src)

    def write_entries(self):
        """Write changes (add/remove) to hosts file.
        Can raise IOError.
        """
        self.manager.write()

    def set_key(self, key):
        """Set word(s) we must search for."""
        self.sites.clear()
        self.grabber.set_query(key)

    def search_sites(self, power=1):
        """Retrieve sites accordingly to key.
        Can raise HTTPError.
        """
        # this is somehow redundant (especially with gui)
        # but only in this mode we ensure no duplicates
        for i in xrange(power): # add sum{2^k | k=t+1,t+p} sites
                                # where t represents how many times
                                # search was called and p is the
                                # number of calls to make this time
                                # (see search from HostsManager)
            self.sites = self.sites.union(self.grabber.search())
        return self.sites


def main(argc, argv):
    """Main function.

    Here we create the core object for the application
    that can be used by both cli and gui to edit
    hosts file and search for sites over the internet.
    """
    core = Core() # all actions are triggered from here
    if argc == 1:
        # no arguments so create the gui
        gui = Gui(core=core)
        gui.mainloop() # wait until destroyed
        return # gui was destroyed so exit
    # arguments are present, enter cli mode
    power = 1 # default value
    at = 1 # while we have arguments to parse
    while at < argc:
        # first, parse options
        if argv[at] in ("-h", "--help"):
            print USAGE % argv[0]
            return
        elif argv[at] in ("-p", "--power"):
            # affects the number of search results
            if at + 1 >= argc:
                raise ParseError("No value for -p/--power")
            try:
                power = int(argv[at + 1])
            except ValueError:
                raise ParseError("Invalid value for -p/--power")
            at += 1
        # then commands
        elif argv[at] == "list":
            # show hosts mapping structure
            for item in core.list_entries():
                print "%s -> %s" % item
        elif argv[at] == "add":
            if at + 2 >= argc: # check for needed values
                raise ParseError("Insufficient values to add")
            src, dest = argv[at + 1], argv[at + 2]
            at += 2
            rcode = core.add_entry(src, dest) # add map
            core.write_entries() # write changes
            if rcode == 1:
                print "%s -> %s added" % (src, dest)
            else:
                print "%s -> %s replaced" % (src, dest)
        elif argv[at] == "remove":
            if at + 1 >= argc:
                raise ParseError("No value to remove")
            src = argv[at + 1]
            at += 1
            dest = core.remove_entry(src)
            core.write_entries()
            if dest:
                print "%s -> %s removed" % (src, dest)
            else:
                print "%s not found" % src
        elif argv[at] == "search":
            # set key and make power searches
            if at + 1 >= argc:
                raise ParseError("No value to search for")
            key = argv[at + 1]
            at += 1
            core.set_key(key)
            for site in core.search_sites(power):
                # print all sites from beginning
                print site
        else:
            # none of the above
            raise ParseError("Invalid argument '%s', run with --help" % argv[at])
        at += 1 # parse the next one


if __name__ == "__main__":
    # if not imported, execute
    try:
        main(len(sys.argv), sys.argv)
    except ParseError as err:
        print err # invalid arguments
    except HTTPError as err:
        print err # to many searches
    except IOError as err:
        print err # usually permission denied
