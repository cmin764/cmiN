#! /usr/bin/env python3


import asyncio
import base64
import itertools
import json
import os

import requests
import websockets


CLIENT_ID = "cfca8174de30d75"
CLIENT_SECRET = "46b33b0589a7f140343608b4bf0e5b83d891da3d"

DB = {}
DB_PATH = "db.json"


def upload_image(content):
    url = "https://api.imgur.com/3/image"
    headers = {'Authorization': 'Client-ID {}'.format(CLIENT_ID)}
    image = base64.b64decode(content)
    resp = requests.post(url, headers=headers, data={"image": image})
    resp.raise_for_status()
    return resp.json()["data"]["link"]


def save():
    with open(DB_PATH, "w") as stream:
        json.dump(DB, stream)


def load():
    if not os.path.isfile(DB_PATH):
        return
    with open(DB_PATH, "r") as stream:
        global DB
        DB = json.load(stream)


def interpret_content(content):
    action = content.get("action")
    cid = content.get("cid")
    if action == "getall":
        return {"urls": list(itertools.chain(*DB.values()))}
    elif action == "get":
        return {"urls": DB.get(cid, [])}
    elif action == "upload":
        url = upload_image(content["data"])
        DB.setdefault(cid, []).append(url)
        save()
        return {"url": url}
    raise Exception("Invalid action {!r}".format(action))


async def imgup(websocket, path):
    content = await websocket.recv()
    print("Received image of length {}".format(len(content)))

    response = interpret_content(json.loads(content))
    response = json.dumps(response)

    await websocket.send(response)
    print("Sent response: {}".format(response))


load()
start_server = websockets.serve(imgup, 'localhost', 8765)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
