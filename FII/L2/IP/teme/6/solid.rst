Cyclomatic Complexity
---------------------

1. Se numara ramurile pe care se poate duce instruction pointer-ul la executia codului,
de ex.: conditii (if), bucle (while/for) etc.
2. Se incearca a se reduce complexitatea ciclomatica, pentru a creste stabilitatea
programului: se inlocuiesc ramuri cu blocuri de cod mai elegante (posibil si complexe),
care fac aceste alegeri automat, fara a avea trieri logice explicite.
3. Acest aspect este foarte imortant si in testare pentru a nu scrie cod redundant de fiecare
data cand adaugam si testam un nou aspect.


Defensive Programming
---------------------

1. Se verifica inputul functiilor (parametri) pentru a fi potrivit pentru ceea ce
face functia in cauza.
2. Daca ceva nu este in regula, se arunca o exceptie (loudly) care sa intrerupa executia.
3. Nu se ascund buguri/exceptii prin tratarea lor in interior si indeplinirea executiei
orice ar fi.


SOLID
-----

- cuplaj mic (dependenta intre clase si obiecte diverse) si coeziune mare
(metode ce fac putine lucruri si strans legate intre ele)
- metode si clase responsabile cu un singur lucru
- clasele trebuiesc pastrate intern insa a fi usor de extins
- Liskov: clasele derivate trebuie sa nu neglijeze/stearga din comportamentul de baza
- DontRepeatYourself, KISS
