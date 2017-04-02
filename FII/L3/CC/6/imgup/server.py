#! /usr/bin/env python3


import asyncio
import base64

import requests
import websockets


CLIENT_ID = "cfca8174de30d75"
CLIENT_SECRET = "46b33b0589a7f140343608b4bf0e5b83d891da3d"


def upload_image(content):
    url = "https://api.imgur.com/3/image"
    headers = {'Authorization': 'Client-ID {}'.format(CLIENT_ID)}
    image = base64.b64decode(content)
    resp = requests.post(url, headers=headers, data={"image": image})
    resp.raise_for_status()
    return resp.json()["data"]["link"]


async def imgup(websocket, path):
    content = await websocket.recv()
    print("Received image of length {}".format(len(content)))

    url = upload_image(content)

    await websocket.send(url)
    print("Sent response: {}".format(url))


start_server = websockets.serve(imgup, 'localhost', 8765)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
