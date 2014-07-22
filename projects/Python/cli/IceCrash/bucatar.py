#! /usr/bin/env python3
# Bucataras.ro recipe extractor
# 21.04.2011 cmiN

import sys, os, urllib.request

def save(title, picture, ingredients, prepar):
    string = """<html>
<body>
<font size="10" color="#ff0000">{}</font><br>
<img src="{}"><br>
<font size="5">Ingrediente:</font><br>""".format(title, picture)
    for word in ingredients:
        string += "<b>- {}</b><br>\n".format(word)
    string += """<font size="5">Mod de preparare:</font><br>
{}
</body> 
</html>""".format(prepar)
    fname = str()
    for char in title:
        if char.isalpha():
            fname += char
        else:
            fname += "_"
    with open("recipes/" + fname + ".html", "wt") as fobj:
        fobj.write(string)

def edit(word):
    string = str()
    flag = False
    for char in word:
        if char == ">":
            flag = False
        elif char == "<" or flag:
            flag = True
        else:
            string += char
    return string

def extract(source, first, last):
    findex = source.find(first) + len(first)
    lindex = source.find(last)
    return source[findex:lindex].decode()

def crawl(link):
    with urllib.request.urlopen(link) as uobj:
        source = uobj.read()
    title = extract(source, b"<title>", b"</title>")
    picture = extract(source, b'<meta property="og:image" content="', b'">\r\n<link rel="alternate"')
    ingred = extract(source, b'<div class="lista listaIncrediente ingredient">\r\n\t\t\t<ul>\r\n', b'\r\n</ul>\r\n\t\t</div>')
    ingred = ingred.replace("</li>\r\n", "")
    ingredients = list()
    for word in ingred.split("<li>")[1:]:
        ingredients.append(edit(word.strip()))
    prepar = extract(source, b'<div class="contentArticol instructions" id="contentArticol">\r\n\t\t<p>', b'</p>\r\n\t\t<p>Citeste cele mai proaspete retete')
    prepar = edit(prepar.strip())
    save(title, picture, ingredients, prepar)

def process(path):
    if not os.path.isdir("recipes"):
        os.mkdir("recipes")
    with open(path, "rt") as fobj:
        for line in fobj:
            crawl(line.strip())

def main(argc, argv):
    if argc == 2:
        process(argv[1])
    else:
        print("./bucatar.py links.txt")

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
