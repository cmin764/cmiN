#! /usr/bin/env python
#
# vic: dangerous varying object types pseudo-serialization


import uuid
import threading
import random
import time

from redis import StrictRedis


KEY = "static"
DELAY = 3

WLIST = {    # list, dict, None, str just work
    "True": True,
    "False": False,
    "set": set
}
GLOBS = {"__builtins__": WLIST}    # clear the namespace


class RedisQueue(object):

    """Simple high level redis wrapper over lists."""

    def __init__(self, key=KEY):
        # create the key
        if not key:
            key = str(uuid.uuid4())
        self.key = key
        # and the redis connection
        self.rcon = StrictRedis()
        # clear the sentinels (None(s))
        self.rcon.lrem(self.key, 0, RedisQueue._serialize(None))

    @staticmethod
    def _serialize(item):
        # bad habit
        return repr(item)

    @staticmethod
    def _deserialize(item):
        # even worse
        try:
            return eval(item, GLOBS)
        except Exception as exc:
            return "<Invalid> - {}".format(exc)

    def push(self, item):
        """Insert an item in the queue."""
        # append a "serialized" item to the list (bad habit)
        self.rcon.rpush(self.key, RedisQueue._serialize(item))

    def pop(self, block=True):
        """Remove an item from the queue."""
        if block:    # wait until something is available
            item = self.rcon.blpop(self.key)[1]
        else:
            item = self.rcon.lpop(self.key)
        return RedisQueue._deserialize(item)    


def producer(rque, quit):
    rnd = lambda: random.randint(0, 10)
    _a = ord("a")
    _b = ord("A")

    while not quit.is_set():
        # make a random-sized dictionary with random keys/values
        seq = dict([(rnd(), rnd()) for i in xrange(rnd())])
        # build more items from that sequence
        items = [seq, list(seq), set(seq), True, False,
                 "string-" + "".join([chr(a + _a) + chr(b + _b)
                                      for a, b in seq.iteritems()])]
        # push them into the queue
        for item in items:
            rque.push(item)
            time.sleep(rnd() / 10.0)
        time.sleep(DELAY)

    rque.push(None)


def consumer(rque, quit):
    while True:
        # get an item
        item = rque.pop()
        if item is None:    # reached the sentinel (quit event was set)
            quit.set()    # for reverse stop
            break
        print "{} ({})".format(item, type(item))


def main():
    # create a simple FIFO queue (for sending and receiving objects)
    rque = RedisQueue()
    # and a quit event
    quit = threading.Event()

    # asynchronous lame producer-consumer
    prod = threading.Thread(target=producer, args=[rque, quit])
    cons = threading.Thread(target=consumer, args=[rque, quit])

    # start the threads
    prod.start()
    cons.start()

    # wait until Ctr+C is pressed (SIGINT) or
    # until None is extracted from the queue
    while not quit.is_set():
        try:
            time.sleep(1)
        except KeyboardInterrupt:
            quit.set()

    # wait the threads to finish
    prod.join()
    cons.join()


if __name__ == "__main__":
    main()
