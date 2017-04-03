#!/usr/bin/env python3


import asyncio
import base64
import json
import os
import sys

import websockets


def prepare_image(imgpath):
    if not os.path.isfile(imgpath):
        raise Exception("invalid image path {!r}".format(imgpath))
    with open(imgpath, "rb") as stream:
        content = stream.read()
    return base64.b64encode(content).decode()


def prepare_request(action, imgpath):
    req = {"action": action}
    if action == "upload":
        req["data"] = prepare_image(imgpath)
    return req


async def imgup(cid, action, imgpath=None):
    async with websockets.connect('ws://localhost:8765') as websocket:

        content = prepare_request(action, imgpath)
        content["cid"] = cid
        await websocket.send(json.dumps(content))

        resp = await websocket.recv()
        resp = json.loads(resp)
        print("Response: {}".format(resp))


def main(argv):
    if len(argv) not in (3, 4):
        print("Usage: {} CLIENT ACTION [FILE]".format(argv[0]))
        return

    asyncio.get_event_loop().run_until_complete(imgup(*argv[1:]))


if __name__ == "__main__":
    main(sys.argv)
