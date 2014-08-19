1. Evaluarea
------------

Fiecare proiect se va evalua in felul urmator:

a) se pregateste emitatorul cu tot cu mesajul de testat si primit de la juriu incarcat, iar declansarea se va face rapid cu o tasta sau un click etc.
b) inainte ca emitatorul sa fie pornit, se porneste receptorul prin script-ul *run.py* unde se da ca parametru calea catre executabilul ce porneste receptorul in sine si asteapta sa se sincronizeze cu emitatorul, ca mai apoi sa scrie in timp real intr-un fisier mesajul primit si decodificat; imediat cum script-ul respectiv va fi pornit, este indicat ca si emitatorul din celalalt dispozitiv sa fie pornit pentru a nu pierde timpul
c) in limita de timp setata sau a rularii normale, procesul va fi inchis si se va crea un fisier special cu rezultatul primit de receptor
d) se fac N astfel de fisiere speciale ce contin separate de un delimitator urmatoarele: <nume_program>-_-<nume_fisier>-_-<timestamp_inceput>-_-<timestamp_sfarsit>.txt (in functie de numarul de teste, in cazul de fata doar trei)
e) aceste N fisiere speciale sunt mai apoi mutate intr-un folder unic cu numele proiectului si/sau a echipei, iar toate aceste foldere sunt stranse intr-un director


2. Verificarea datelor
----------------------

Pentru a verifica si a acorda un punctaj proiectelor, se va folosi script-ul *check.py* care va primi ca argument la linia de comanda, numele folder-ului general in care sunt stranse toate sub-folderele ce contin cele N fisiere speciale cu datele primite si decodificate de catre receptor. Dupa rularea cu succes a acestui script, va aparea un fisier numit **total.txt** ce continte pe cate o linie urmatoarele: "<nume_folder/proiect>: <punctaj>" si acesta reprezinta clasamentul neordonat final.


3. Calcularea scorului
----------------------

Scorul este calculat in functie de niste metode simple si obiective, iar acestea tin cont foarte mult de datele primite, dar si putin de timpul in care acestea au fost transmise (pentru departajare). Acesta este calculat pentru fiecare proiect in parte, independent, in felul urmator:

a) fiecare test este notat cu un punctaj real de la 0 la 100
b) fiecare test are o pondere, de ex.: 20%, 30%, 50% (pentru ca sunt din ce in ce mai lungi si mai complexe) si in functie de aceasta pondere este calculat punctajul total
c) fiecare test isi formeaza punctajul din intervalul 0-100 printr-o subpondere ce se aplica fiecarui test, iar aceasta e de 80% pentru calitatea datelor primite si de 20% pentru timpul alocat primirii text-ului
d) punctajele partiale pentru date sunt calculate facand distanta Levenshtein si alocand punctaj maxim pentru o potrivire perfecta si punctaj minim dar mai mare ca zero pentru o potrivire ambigua ce nu depaseste ca distanta intreaga lugime a textului de testat; atentie, aici pot aparea si punctaje negative in cazul in care textul scris de receptor este mai lung (si mai irelevant) decat mesajul de test in sine
e) punctajele partiale pentru viteza sunt calculate facand o simpla distributie constanta in functie de timpul maxim alocat


4. Precizari
------------

Este recomandat, ca inainte de inceperea testului propriu-zis, sa se faca un metatest folosind optiunea *-t/--time* cu un timp mult mai mic, pentru a vedea daca sincronizarea este posibila cu erori minime si daca ansamblul de verificari functioneaza cum trebuie.


P.S.: Script-ul de verificare are nevoie de biblioteca `python-levenshtein`, iar acesta poate fi transformat destul de usor in executabil de sine statator cu cx_Freeze sau PyInstaller.
