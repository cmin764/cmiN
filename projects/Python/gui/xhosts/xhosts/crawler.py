#
# crawler:   module able to extract websites by searching keywords
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


from urllib2 import build_opener, HTTPError
from urlparse import urlparse


# you can adapt this after any web page model
LINK = "http://www.google.com/search?q={query}&start={begin}"
# the site we are looking for is between two strings
FST = "url?q="
SEC = "&amp"


class Crawler(object):
    """Find in a search engine URLs corresponding to query."""

    def __init__(self, query=""):
        """Build opener and prepare data."""
        self.sites = set()
        self.opener = build_opener()
        # use this to look like a browser
        self.opener.addheaders = [('User-agent', 'Mozilla/5.0')]
        self.set_query(query)

    def __netloc(self, link):
        """Parse the entire link and return it in www.site.com form."""
        return urlparse(link).netloc

    def set_query(self, query):
        """Set a new query and start from the beginning."""
        self.link = LINK.format(query=query.replace(" ", "+"), begin="{begin}") # search for this
        self.begin = 0 # from here we start
        self.count = 2 # how many results for the first time

    def search(self):
        """Search and return a set with found sites."""
        self.sites.clear() # clear previous search
        # search from the current position next count results
        for inc in xrange(self.count):
            # use the opener to open the new formatted link by a new beginning
            try:
                usock = self.opener.open(self.link.format(begin=self.begin + inc))
            except HTTPError as err: # the search engine banned you for a period of time
                raise # know about
            # now read and parse the data
            data = usock.read() # read and store the whole page (noobish)
            usock.close()
            lo = data.find(FST) + len(FST) # here starts the link
            hi = data.find(SEC, lo) # here it ends
            site = self.__netloc(data[lo:hi])
            self.sites.add(site) # add unique sites
        # update the start and length for a next search
        self.begin += inc + 1
        self.count *= 2
        self.sites.discard("") # remove malformed sites
        return self.sites
