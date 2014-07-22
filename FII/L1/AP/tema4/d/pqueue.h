#ifndef PQUEUE_H
#define PQUEUE_H


#include <stdlib.h>


typedef struct {
    /// Structura unui element.
    int value;    // valoarea
    int priority; // prioritatea
} key_t;


typedef struct {
    size_t size;     // dimensiune
    size_t capacity; // capacitate
    key_t * vec;     // continutul cozii 
} pqueue_t;


// creeaza si initializeaza coada
void pqueue_create(pqueue_t *);


// adauga nod in coada
void pqueue_push(pqueue_t *, key_t);


// scoate nod din coada
key_t pqueue_pop(pqueue_t *);


// verifica daca e vida
int pqueue_empty(const pqueue_t *);


// distruge coada
void pqueue_destroy(pqueue_t *);


#endif /* PQUEUE_H */
