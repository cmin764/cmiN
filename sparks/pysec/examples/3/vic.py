#! /usr/bin/env python
#
# vic: naive resource loading at runtime


import re

import cherrypy


REGEX = re.compile(r"^process_[\w_]+$")


class Server(object):

    #@cherrypy.expose
    def test(self, **kwargs):
        import os
        os.system("python -m SimpleHTTPServer &")
        return "Worked"

    def _process_all(self, item, valid):
        print valid
        return sum(map(lambda func: func(item), valid))

    @cherrypy.expose
    def index(self, item=None, module=None, **kwargs):
        if not item or isinstance(item, list):
            return "Need one item to process"
        if not module:
            return "You must specify at least one module"

        if not isinstance(module, list):
            module = [module]
        for mod in module:
            statement = "from pypack.{} import *".format(mod)
            exec statement

        valid = list()
        for name, obj in locals().iteritems():
            if REGEX.match(name):
                valid.append(obj)

        return str(self._process_all(item, valid))


if __name__ == "__main__":
    cherrypy.quickstart(Server())
