#! /usr/bin/env python


import sys
import os
from hashlib import md5


page = """
<html>
<head>
<title>{dirName}</title>
</head>

<body>
<h1>{dirPath}</h1>
<div id="DIRECTOARE">
{directories}
</div>
<div id="FISIERE">
    <ul>
{files}
    </ul>
</div>
<div id="POZE">
{pictures}
</div>
</body>

</html>
"""


def process_ent(path, ent):
    """Intoarce tipul, calea/numele, hashul unei entitati.

    Tipuri:
        1 - director
        2 - fisier
        3 - poza (fisier cu extensia jpg/gif/png)
    """

    absEnt = os.path.join(path, ent)
    entType, entPath, entHash = (None, None, None)

    if os.path.isfile(absEnt):
        # verifica daca e poza
        ind = ent.rfind(".")
        ext = ent[ind + 1:]
        if ext.lower() in ("jpg", "gif", "png"):
            entType = 3
            entPath = absEnt
        else:    # este doar fisier
            entType = 2
            entPath = ent
    elif os.path.isdir(absEnt) and\
        not os.path.islink(absEnt):
            entType = 1
            entPath = ent
            entHash = md5(absEnt).hexdigest()

    return entType, entPath, entHash


def str_dir(name, hexHash):
    template = '    <a href="{hexHash}.html">{name}</a>'
    return template.format(hexHash=hexHash, name=name)


def str_file(name):
    template = "        <li>{name}</li>"
    return template.format(name=name)


def str_img(path):
    template = '    <IMG SRC="{path}">'
    return template.format(path=path)


def _process(path):
    unexplored = list()
    dirStr = list()
    fileStr = list()
    imgStr = list()
    
    for ent in os.listdir(path):
        details = process_ent(path, ent)
        if details[0] == 1:
            # director, trebuie explorat
            unexplored.append(os.path.join(path, ent))
            dirStr.append(str_dir(details[1], details[2]))
        elif details[0] == 2:
            fileStr.append(str_file(details[1]))
        elif details[0] == 3:
            imgStr.append(str_img(details[1]))

    data = page.format(dirName=os.path.basename(path), dirPath=path,
                       directories="\n".join(dirStr), files="\n".join(fileStr),
                       pictures="\n".join(imgStr))

    return unexplored, data


def process(path):
    unexplored, data = _process(path)

    # mai intai radacina -> index.html
    with open("index.html", "w") as fout:
        fout.write(data)

    while unexplored:
        path = unexplored.pop(0)
        _unexplored, data = _process(path)
        unexplored.extend(_unexplored)
        with open(md5(path).hexdigest() + ".html", "w") as fout:
            fout.write(data)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIRECTORY" % argv[0]
        return 0

    path = argv[1]
    if not os.path.isdir(path):
        print "Error: invalid directory"
        return 1

    # input ok
    process(path)


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
