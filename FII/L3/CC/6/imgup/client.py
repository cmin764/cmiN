#!/usr/bin/env python3


import asyncio
import base64
import os
import sys

import websockets


def prepare_image(imgpath):
    if not os.path.isfile(imgpath):
        raise Exception("invalid image path {!r}".format(imgpath))
    with open(imgpath, "rb") as stream:
        content = stream.read()
    return base64.b64encode(content)


async def imgup(imgpath):
    async with websockets.connect('ws://localhost:8765') as websocket:

        content = prepare_image(imgpath)
        await websocket.send(content)

        url = await websocket.recv()
        print("Url: {}".format(url))


def main(argv):
    if len(argv) != 2:
        print("Usage: {} FILE".format(argv[0]))
        return

    asyncio.get_event_loop().run_until_complete(imgup(argv[1]))


if __name__ == "__main__":
    main(sys.argv)
