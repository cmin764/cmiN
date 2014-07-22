#! /usr/bin/env python3.1
# 14.10.2009 <> 17.10.2009 | cmiN
# Challenge [Programming] Letter Grid [www.wechall.net] @ rstcenter.com


import urllib.request


def main():
    with open("dict.txt", "r") as f:
        words = sorted(f.read().split("\n"))
    url = "http://www.wechall.net/challenge/lettergrid/generate.php"
    sessionid = "2d9b7c26769e4c0d2cb1c471df460f7c"
    headers = {
        "Cookie": "PHPSESSID={};".format(sessionid),
        "Referer": "http://www.wechall.net/",
        "User-Agent": "Mozilla/4.0 (compatible; MSIE 6.0)"
        }
    req = urllib.request.Request(url, headers=headers)
    with urllib.request.urlopen(req) as f:
        source = str(f.read(), encoding="utf-8")
    grid = source.split("\n")[1:-2]
    solution = dict()
    for y in grid:
        for x in words:
            for z in (x, x[::-1]):
                if y.find(z) != -1:
                    gindex = grid.index(y)
                    cindex = y.find(z)
                    if z == x:
                        solution["{row}-{column}".format(row=str(gindex).zfill(2), column=str(cindex).zfill(2))] = x
                    else:
                        solution["{row}-{column}".format(row=str(gindex).zfill(2), column=str(cindex + len(z) - 1).zfill(2))] = x
    for x in words:
        for y in grid:
            for z in (x, x[::-1]):
                n = 0
                while y.find(z[0], n) != -1:
                    gindex = grid.index(y)
                    cindex = y.find(z[0], n)
                    if gindex <= len(grid) - len(z):
                        gvec = range(gindex, gindex + len(z))
                        word = "".join([grid[gvec[i]][cindex] for i in range(len(gvec))])
                        if word == z:
                            if z == x:
                                solution["{row}-{column}".format(row=str(gindex).zfill(2), column=str(cindex).zfill(2))] = x
                            else:
                                solution["{row}-{column}".format(row=str(gindex + len(z) - 1).zfill(2), column=str(cindex).zfill(2))] = x
                    if gindex <= len(grid) - len(z) and cindex <= len(y) - len(z):
                        gvec = range(gindex, gindex + len(z))
                        cvec = range(cindex, cindex + len(z))
                        word = "".join([grid[gvec[i]][cvec[i]] for i in range(len(gvec))])
                        if word == z:
                            if z == x:
                                solution["{row}-{column}".format(row=str(gindex).zfill(2), column=str(cindex).zfill(2))] = x
                            else:
                                solution["{row}-{column}".format(row=str(gindex + len(z) - 1).zfill(2), column=str(cindex + len(z) - 1).zfill(2))] = x
                    if gindex <= len(grid) - len(z) and cindex >= len(z) - 1:
                        gvec = range(gindex, gindex + len(z))
                        cvec = range(cindex, cindex - len(z), -1)
                        word = "".join([grid[gvec[i]][cvec[i]] for i in range(len(gvec))])
                        if word == z:
                            if z == x:
                                solution["{row}-{column}".format(row=str(gindex).zfill(2), column=str(cindex).zfill(2))] = x
                            else:
                                solution["{row}-{column}".format(row=str(gindex + len(z) - 1).zfill(2), column=str(cindex - len(z) + 1).zfill(2))] = x            
                    n = cindex + 1
    string_solution = ""
    for x in sorted(solution.keys()):
        string_solution += solution[x]
        #print("{position}: {word}".format(position=x, word=solution[x]))
    url = "http://www.wechall.net/challenge/lettergrid/index.php?solution="
    req = urllib.request.Request(url + string_solution, headers=headers)
    with urllib.request.urlopen(req) as f:
        source = f.read()
    print(source)
    #input()


if __name__ == "__main__":
    main()
