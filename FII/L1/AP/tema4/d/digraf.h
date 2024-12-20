#ifndef DIGRAF_H
#define DIGRAF_H


typedef struct {
    /**
     * Structura unui digraf (graf orientat).
     * Aceasta contine numarul entitatilor si
     * o lista (sub forma de vectori) cu vecinii
     * fiecarui nod.
     */
    int nodes; // numarul de varfuri
    int edges; // numarul de arce
    int ** list; // lista de adiacenta
} Digraf;


// creeaza structura folosind fisierul
void creeaza(Digraf *, char *);


// returneaza gradul interior pentru un nod
int grad_int(Digraf, int);


// returneaza gradul exterior pentru un nod
int grad_ext(Digraf, int);


// returneaza daca este sau nu este tare conex
int este_tare_conex(Digraf);


/* problema 4 */


// exista sau nu un nod
int contine_groapa(Digraf);


// Dijkstra
int min_dist(Digraf, int, int);


// distruge graful
void distruge(Digraf *);


// returneaza transpus
Digraf transpus(Digraf);


// afiseaza componente conexe
void comp_conexe(Digraf);


#endif /* DIGRAF_H */
