#! /usr/bin/env python
#
# rms-cli: Release Management System - client
#
# Author: cmin764@yahoo/gmail.com


import os
import shutil
import socket
import struct
import argparse
from binascii import hexlify, unhexlify


HOST = "127.0.0.1"
PORT = 51337


class RMS(object):

    SEARCH = 0
    DOWNLOAD = 1
    ISIZE = 4
    PEXT = "tar.gz"

    def __init__(self, host=HOST, port=PORT):
        self.host = host
        self.port = port

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))

    def close(self):
        self.sock.close()

    def __enter__(self):
        self.connect()
        return self

    def __exit__(self, *args):
        self.close()

    def _send_package(self, package):
        self.sock.send(struct.pack("!i", len(package)))
        self.sock.send(package)

    def search(self, package):
        self.sock.send(struct.pack("!i", RMS.SEARCH))
        self._send_package(package or "")
        packcnt = struct.unpack("!i", self.sock.recv(RMS.ISIZE))[0]
        packvec = list()
        for _ in range(packcnt):
            packlen = struct.unpack("!i", self.sock.recv(RMS.ISIZE))[0]
            packvec.append(self.sock.recv(packlen))
        return packvec

    def download(self, package):
        self.sock.send(struct.pack("!i", RMS.DOWNLOAD))
        self._send_package(package)
        fsize = struct.unpack("!i", self.sock.recv(RMS.ISIZE))[0]
        data = self.sock.recv(fsize)
        return data


def search_func(args):
    rms = RMS(host=args.server, port=args.port)
    with rms:
        packages = rms.search(args.package)
    if not packages:
        if args.verbose:
            print("No packages found")
        return
    if args.verbose:
        print("Found {} package(s):".format(len(packages)))
    for package in packages:
        print(package)


def download_func(args):
    rms = RMS(host=args.server, port=args.port)
    with rms:
        packages = rms.search(args.package)
    if not packages:
        if args.verbose:
            print("No packages found")
        return
    package = None
    if len(packages) > 1:
        for _package in packages:
            if _package == args.package:
                package = _package
                break
        if package is None:
            if args.verbose:
                print("Multiple packages found, please select one of them:")
                for package in packages:
                    print(package)
            return
    if package is None:
        package = packages[0]
    if args.verbose:
        print("Downloading package {}...".format(package))
    with rms:
        data = rms.download(package)
    fpath = os.path.join(
        args.output,
        "{}.{}".format(package, RMS.PEXT)
    )
    with open(fpath, "wb") as fout:
        fout.write(data)
    print("Downloaded: {}".format(fpath))
    return package, fpath


def install_func(args):
    ret = download_func(args)
    if ret is None:
        if args.verbose:
            print("Nothing to install")
        return
    package, fpath = ret
    if args.verbose:
        print("Installing package {} from {}..."
              .format(package, fpath))
    os.chdir(args.output)
    os.system("tar -xzvf {}".format(os.path.basename(fpath)))
    os.chdir(package)
    os.system("python setup.py install")
    os.chdir("..")
    os.remove(fpath)
    shutil.rmtree(package)
    print("Installed: {}".format(package))


def main():
    parser = argparse.ArgumentParser(
        description="Release Management System - client"
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="show debugging messages"
    )
    parser.add_argument(
        "-s",
        "--server",
        metavar="SERVER",
        default=HOST,
        help="server address"
    )
    parser.add_argument(
        "-p",
        "--port",
        metavar="PORT",
        default=PORT,
        type=int,
        help="server port"
    )

    subparsers = parser.add_subparsers(title="commands")
    commonp = argparse.ArgumentParser(add_help=False)
    commonp.add_argument(
        "package",
        metavar="PACKAGE",
        help="package name"
    )
    commono = argparse.ArgumentParser(add_help=False)
    commono.add_argument(
        "-o",
        "--output",
        metavar="OUTPUT",
        default=os.getcwd(),
        help="output directory for downloaded packages"
    )

    spsearch = subparsers.add_parser(
        "search",
        help="search for packages"
    )
    spsearch.add_argument(
        "package",
        metavar="PACKAGE",
        nargs="?",
        help="package name"
    )
    spsearch.set_defaults(func=search_func)

    spdownload = subparsers.add_parser(
        "download",
        parents=[commonp, commono],
        help="download a specific package"
    )
    spdownload.set_defaults(func=download_func)

    spinstall = subparsers.add_parser(
        "install",
        parents=[commonp, commono],
        help="download and install a specific package"
    )
    spinstall.set_defaults(func=install_func)

    args = parser.parse_args()
    if hasattr(args, "output"):
        args.output = os.path.abspath(args.output)
    args.func(args)


if __name__ == "__main__":
    main()
