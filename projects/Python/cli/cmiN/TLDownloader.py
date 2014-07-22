#! /usr/bin/env python3.1
# 2.10.2009 <> 2.10.2009 | cmiN
# Trilulilu Downloader (console)


import sys, urllib.request


class TLD:

    def __init__(self, args):
        usage = """\t\t Trilulilu Downloader 1.0

\t Usage: TLDownloader.py link

Where link is a valid trilulilu.ro link

\t Example: TLDownloader.py http://www.trilulilu.ro/dragos_adrian/61bc64a77882e0"""
        if len(args) == 2:
            try:
                print("Please wait...")
                link = args[1]
                self.download(link)
            except Exception as message:
                print("An error occurred: {}".format(message))
            except:
                print("Unknown error.")
            else:
                print("Ready!")
        else:
            print(usage)
        input()

    def download(self, link):
        with urllib.request.urlopen(link) as page_source:
            source = str(page_source.read(), encoding="utf-8")
            ao, vo = source.count('value="audio"'), source.count('value="video"')
            if ao > vo:
                type = "audio"
            else:
                type = "video"
            userid = ""
            index = source.index('so.addVariable("userid", "') + len('so.addVariable("userid", "')
            while source[index] != '"':
                userid += source[index]
                index += 1
            hash = ""
            index = source.index('so.addVariable("hash", "') + len('so.addVariable("hash", "')
            while source[index] != '"':
                hash += source[index]
                index += 1
            server = ""
            index = source.index('so.addVariable("server", "') + len('so.addVariable("server", "')
            while source[index] != '"':
                server += source[index]
                index += 1
            key = ""
            index = source.index('so.addVariable("key", "') + len('so.addVariable("key", "')
            while source[index] != '"':
                key += source[index]
                index += 1
            glink = "http://fs{server}.trilulilu.ro/stream.php?type={type}&hash={hash}&username={userid}&key={key}".format(server=server, type=type, hash=hash, userid=userid, key=key)
        with urllib.request.urlopen(glink) as file_source:
            source = file_source.read()
            if type == "audio":
                ext = "mp3"
            else:
                ext = "flv"
            with open("".join(["downloaded_file", ".", ext]), "wb") as f:
                f.write(source)


if __name__ == "__main__":
    TLD(sys.argv)
