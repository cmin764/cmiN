#! /usr/bin/env python3.1
# 07.10.2009 <> 9.10.2009 | cmiN
# Challenge [Programming] Flow Over Astronomy [www.wechall.net] @ rstcenter.com


import urllib.request
from decimal import *


class FOA:

    def __init__(self):
        self.url = "http://www.wechall.net/challenge/FlowOverAstronomy/index.php"
        sessionid = "bedddee80571bab46705fe26f394121b"
        self.headers = {"Cookie": "PHPSESSID={};".format(sessionid),
                   "Referer": "http://www.wechall.net/",
                   "User-Agent": "Mozilla/4.0 (compatible; MSIE 6.0)"}
        req = urllib.request.Request(self.url, headers=self.headers)
        sock = urllib.request.urlopen(req)
        source = str(sock.read(), encoding="utf-8")
        sock.close()
        self.parse_source(source)

    def parse_source(self, source):
        tl = len("<br/>")
        charset = ""
        index = source.index("Charset: ") + len("Charset: ")
        while source[index:index + tl] != "<br/>":
            charset += source[index]
            index += 1
        input_base = ""
        index = source.index("Input Base: ") + len("Input Base: ")
        while source[index:index + tl] != "<br/>":
            input_base += source[index]
            index += 1
        solution_base = ""
        index = source.index("Solution Base: ") + len("Solution Base: ")
        while source[index:index + tl] != "<br/>":
            solution_base += source[index]
            index += 1
        tl = len("<div class='box_text'>")
        while source[index:index + tl] != "<div class='box_text'>":
            index += 1
        input_text = ""
        index += tl
        while source[index:index + 6] != "</div>":
            input_text += source[index]
            index += 1
        input_text = input_text.replace("<br/>", "")
        self.compute_and_submit(charset, int(input_base), int(solution_base), input_text)

    def compute_and_submit(self, charset, input_base, solution_base, input_text):
        input_numbers = list()
        for x in input_text.split(" * "):
            input_numbers.extend(x.split(" + "))
        decimal_input_numbers = list()
        for x in input_numbers:
            number, power = 0, 0
            y = list(x)
            while len(y) != 0:
                z = y.pop()
                number += (input_base ** power) * charset.index(z)
                power += 1
            decimal_input_numbers.append(number)
        decimal_output_solution = 1
        for x in decimal_input_numbers[:-1]:
            decimal_output_solution *= x
        decimal_output_solution += decimal_input_numbers[-1]
        getcontext().prec = 200
        decimal_output_solution = Decimal(decimal_output_solution)
        output_solution = ""
        while int(decimal_output_solution) != 0:
            r = int(decimal_output_solution % solution_base)
            decimal_output_solution = decimal_output_solution / solution_base
            output_solution = charset[r] + output_solution
        req = urllib.request.Request(self.url + "?answer={}&action=Submit".format(output_solution), headers=self.headers)
        sock = urllib.request.urlopen(req)
        sock.close()
                

if __name__ == "__main__":
    FOA()
