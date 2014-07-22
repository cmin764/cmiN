/*******************************************************************************************************
Enunt prima problema:

a) Care sunt primitivele de tip exec ce cauta numele de fisier executabil primit ca parametru in
directoarele din variabila de mediu PATH?
b) Scrieti apelul comenzii "ls" cu parametrii "-l" si "-a" fara a indica locatia exacta a fisierului
executabil "ls". 

NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
*******************************************************************************************************/

/* 

    a) execl, execle, execv

    b) execl("ls", "ls", "-l", "-a", NULL);

*/
