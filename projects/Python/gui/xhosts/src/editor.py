#
# editor:   module used for loading and editing the hosts file
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


import os
from sys import platform
from shutil import copyfile


# cross-platform hosts file path
if "linux" in platform:
    HPATH = "/etc/hosts"
else:
    # windows is a pain in the ass
    HPATH = os.getenv("systemroot")
    if os.path.isdir(HPATH + "\\System32"):
        HPATH += "\\System32"
    else:
        HPATH += "\\system32"
    HPATH += "\\drivers\\etc\\hosts"


class HostsManager(object):
    """Class for loading, editing and saving lines with servers
    and their redirects.

    First you must load the file to store and separate its contents
    in a list with useful data (simple lines)
    + a list with junk (comments that user may need).
    """

    def __init__(self):
        # check if this is the first time, to make a backup
        index = max(HPATH.rfind("/"), # get the parent dir
                    HPATH.rfind("\\")) + 1
        newPath = HPATH[:index] + "hosts.old"
        # hosts exists but hosts.old doesn't
        if not os.path.isfile(newPath) \
        and os.path.isfile(HPATH): # make a copy of hosts
            copyfile(HPATH, newPath) # with the name hosts.old
        self.__new_buffers()

    def __new_buffers(self):
        # instance "global" members
        self.redir = dict() # useful
        self.cmts = list() # junk

    def load(self):
        """Read and parse lines from hosts file (read only)."""
        self.__new_buffers() # just in case if load is called again
        if not os.path.isfile(HPATH):
            # warning, file not present
            # no problem, write method will create one
            return
        # the file exists
        fin = open(HPATH, "r")
        for line in fin:
            line = line.strip()
            # now distribute the line
            if line.startswith("#"): # comment
                self.cmts.append(line)
            else:
                # split the line into more words with the meaning:
                # "mapped_to_this    map_this [and_this,  ...]"
                # so our key will be the mapped objects and
                # destination will be the first element
                chunks = line.split()
                for host in chunks[1:]:
                    self.redir[host] = chunks[0]
        fin.close() # job done, close the file

    def add(self, src, dest):
        """Add a line that redirects host `src` to `dest`
        (no direct file change).
        """
        rcode = 1 # just add
        if self.redir.has_key(src):
            rcode = 2 # replace
        self.redir[src] = dest
        return rcode

    def remove(self, src):
        """Remove a line."""
        # remove key, nothing happens if it's not found
        ret = self.redir.pop(src, None)
        if ret is None:
            return False # nothing removed
        return ret

    def write(self):
        """Write changes to hosts file."""
        # sorry to tell you this, but we must first write the comments
        # then the useful lines, we can't guess the corresponding ones
        # and also can't reuse the empty lines (after removal), because
        # the comments will become more ambiguous
        try:
            fout = open(HPATH, "w")
        except IOError:
            raise # no permissions
        for line in self.cmts:
            fout.write(line + "\n")
        for item in self.redir.iteritems():
            fout.write("%s\t%s\n" % tuple(reversed(item)))
        fout.close()

    def get_hosts(self):
        """Returns a dictionary with hosts."""
        return self.redir
