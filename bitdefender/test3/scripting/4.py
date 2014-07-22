#! /usr/bin/env python


import json
import sys
import os


page = """
<html>
<head>
<title>Structura pentru folderul: {folder}</title>
</head>

<body>
{fill}
</body>

</html>
"""


def process(path, level, tree, lines):
    item = tree.popitem()
    first = '%s<div id="%s">' % (" " * 4 * level, item[0])
    level += 1
    path = os.path.join(path, item[0])
    second = "%s<h1>%s</h1>" % (" " * 4 * level, path)
    lines.extend([first, second])

    subTrees = list()
    for ent in item[1]:
        if isinstance(ent, dict):
            subTrees.append(ent)
        else:
            line = '%s<a href="%s"></a>' % (" " * 4 * level,
                os.path.join(path, ent))
            lines.append(line)

    for subTree in subTrees:
        process(path, level + 1, subTree, lines)

    lines.append("%s</div>" % (" " * 4 * (level - 1)))
    return item[0]


def main(argc, argv):
    if argc != 2:
        print "Usage: %s JSON" % argv[0]
        return 0

    try:
        fin = open(argv[1], "r")
        tree = json.loads(fin.read())
    except IOError:
        print "Error: couldn't open file"
        return 1
    else:
        fin.close()

    lines = list()
    root = process("", 1, tree, lines)
    print page.format(folder=os.path.basename(root),
                      fill="\n".join(lines))


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
