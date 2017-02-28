Message Classifier
==================


Cuprins:
--------

    1. Descriere
    2. Domenii
    3. Actori si obiective
    4. Scenarii de utilizare
        4.1 Utilizatorul salveaza un mesaj
        4.2 Continutul este analizat
        4.4 Mesajul este invalid


1. Descriere
------------

O companie ce produce dispozitive digitale de sticky notes, doreste
instalarea unei extensii ce sa permita clasificarea mesajelor pe baza
unor indicii prezente in continutul acestora.


2. Domenii
----------

Vom descrie scenarii de utilizare corespunzatoare folosirii aplicatiei, 
pentru activitatile suportate.


3. Actori si obiective
----------------------

Sticky Notes: dispozitivul digital pe care va rula softul implicit, dar si extensiile acestuia.
Client: persoana ce va introduce un mesaj cu aspect divers.
Mesaj: Continutul mesajului in sine, cu aspect pozitiv, negativ sau neutru in baza unor
indicii sau tag-uri
Server: Gazda centrala pe care se vor salva/sincroniza datele fiecarui client in parte.


4. Scenarii de utilizare
------------------------

In continuare vom prezenta cateva cazuri de utilizare, prin care utilizatorul
poate sa foloseasta facilitatile programului.

    4.1 Utilizatorul salveaza un mesaj

        4.1.1 Obiectiv
            
            Clientul doreste a produce continut prin intermediul aplicatiei implicite,
            apoi va dori a salva cu suportul din partea clasificatorului bifat.

        4.1.2 Scenariu

            a. Clientul produce continutul.
            b. Clientul bifeaza extensia clasificatorului.
            c. Clientul salveaza mesajul.
            d. Mesajul va trece printr-o serie speciala de procesari.

        4.1.3 Extensii

            Clasificatorul nefiind bifat, nu va produce clasificare.
    
    4.2 Continutul este analizat

        4.1.1 Obiectiv

            Clasificatorul incearca a analiza continutul mesajului si in baza unor indicii
            sa ofere un verdict in legatura cu aspectul acestuia.
            
        4.1.2 Scenariu
            
            a. Analiza se declanseaza imediat dupa salvarea mesajului.
            b. Sunt cautate indicii cheie/tag-uri ce clasifica mesajul intr-una din categorii.
            c. Mesajul este salvat in categoria corespunzatoare.

        4.1.3 Extensii

            Daca nu se gaseste niciun tag, utilizatorul este rugat sa introduca explicit unul.

    4.4 Mesajul este invalid

        4.1.1 Obiectiv

            Se incearca rectificarea acestuia prin interogarea utilizatorului asupra unor informatii suplimentare.

        4.1.2 Scenariu

            a. In urma analizei, a reiesit faptul ca mesajul este corupt sau nu poate fi introdus in una din categorii.
            b. Se afiseaza un mesaj de eroare cu posibilitatea reeditarii sau anularii mesajului.

        4.1.3 Extensii

            Daca nu este luata in mod explicit o decizie in termen de 10 secunde,
            atunci mesajul ramane intr-o sectiune speciala numita "Others".
