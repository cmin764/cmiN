#!/usr/bin/env python


import os
import sys  
import hashlib
import argparse
 
print """
#############################
# Rst Duplicate file finder #
#           Usr6            #
#############################
#nytro edition*
#*are la baza fallen edition
# + some stuff from cmiN
"""
 
biblioteca = {}
librarie = {}

def show(msg):
    if args.verbose:
        print(msg)
 
def hashfile(afile):
    #####
    #http://www.pythoncentral.io/hashing-files-with-python/
    #####
    BLOCKSIZE = 65536
    hasher = hashlib.sha256()
    with open(afile, "rb") as afile:
        buf = afile.read(BLOCKSIZE)
        while len(buf) > 0:
            hasher.update(buf)
            buf = afile.read(BLOCKSIZE)
    return hasher.hexdigest()
 
def fileparsing(root):
    for root, subFolders, files in os.walk(root):
        for file in files:
            fullpath = os.path.join(root, file)
            try:
                file_size = os.path.getsize(fullpath)
                biblioteca.setdefault(file_size, list()).append(fullpath)
                show(fullpath)
            except Exception as bug:
                with open(args.error, "a") as handle:
                    handle.write(str(bug) + "\n")
                    handle.close

DUP = "duplicate.txt"
ERR = "error.txt"

parser = argparse.ArgumentParser(description="Cauta fisiere duplicate.")
parser.add_argument("input", metavar="INPUT",
                    help="director pentru scanat")
parser.add_argument("-o", "--output", metavar="FILE",
                    default=DUP,
                    help="fisier de iesire pentru duplicate")
parser.add_argument("-e", "--error", metavar="FILE",
                    default=ERR,
                    help="fisier cu erori intampinate pe parcurs")
parser.add_argument("-v", "--verbose", action="store_true",
                    help="afiseaza mesaje de depanare")
args = parser.parse_args()
 
if os.path.isdir(args.input):
    fileparsing(args.input)
else:
    parser.error("Director de intrare invalid")
 
show("Filtram rezultatele:")
for f_size in biblioteca.keys():
    if len(biblioteca[f_size]) > 1:
        for f_path in biblioteca[f_size]:
            try:
                md5hash = hashfile(f_path)
                librarie.setdefault(md5hash, list()).append(f_path)
                show(f_path)
            except Exception as bug:
                with open(args.error, "a") as handle:
                    handle.write(str(bug) + "\n")
                    handle.close
 
show("Scriu rezultatele finale in fisierul '{}'".format(args.output))
for md5_, f_paths in librarie.items():
    if len(f_paths) > 1: 
        with open(args.output, "a") as handle:
            handle.write("{} ({})\n".format(md5_, os.path.getsize(f_paths[0])))
            for f_path in f_paths:
                handle.write("\t\t" + str(f_path) + "\n")
            handle.close()
 
print("\nRezultate:")
print("Probleme: ", args.error if os.path.isfile(args.error) else "N-am gasit")
print("Duplicate: ", args.output if os.path.isfile(args.output) else "N-am gasit")
