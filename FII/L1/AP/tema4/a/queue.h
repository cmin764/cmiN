#ifndef QUEUE_H
#define QUEUE_H


#include "arbin.h"


// tipul valorilor din coada
typedef Node key_t;


struct _Queue {
    /// Structura unui nod din coada.
    key_t value; // valoare
    struct _Queue * link; // legatura
};


// sinonim pentru tipul substructurilor
typedef struct _Queue  _queue_t;


struct Queue {
    /// Structura intregii cozi.
    _queue_t * lo, * hi;
};


// sinonim pentru tipul cozilor
typedef struct Queue queue_t;


/// Cream substructurile unei cozi.
int queue_create(queue_t *);


/**
 * Testam daca coada este vida sau nu,
 * mai exact daca adresele capetelor sunt egale.
 */
int queue_empty(queue_t);


/**
 * Eliberam toata memoria ocupata
 * de elemente si distrugem substructurile.
 */
void queue_destroy(queue_t *);


/// Adaugam element in coada.
int queue_push(queue_t *, key_t);


/// Extragem element din coada.
int queue_pop(queue_t *, key_t *);


#endif /* QUEUE_H */
