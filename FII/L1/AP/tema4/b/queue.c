#include <stdlib.h>

#include "queue.h"


static int nalloc(_queue_t ** tmp)
{
    *tmp = (_queue_t *) \
           malloc(sizeof(_queue_t));
    if (!*tmp)
        return 1; // memorie insuficienta
    return 0;
}


int queue_create(queue_t * queue)
{
    // alocam memorie substructurilor 
    _queue_t * tmp;
    if (nalloc(&tmp))
        return 1;
    queue->lo = queue->hi = tmp;
    return 0; // memorie alocata cu succes
}


int queue_empty(queue_t queue)
{
    // returneaza valoare de adevar
    if (queue.lo == queue.hi)
        return 1; // este goala
    return 0; // are cel putin un element
}


void queue_destroy(queue_t * queue)
{
    /* iteram coada pana cele doua
       capete sunt egale, eliberand
       memoria fiecarui nod */
    while (!queue_empty(*queue)) {
        _queue_t * tmp = queue->lo;
        queue->lo = queue->lo->link;
        free(tmp);
    }
    free(queue->lo);
    queue->lo = queue->hi = NULL;
}


int queue_push(queue_t * queue, key_t value)
{
    // cream un nou nod
    _queue_t * tmp;
    if (nalloc(&tmp))
        return 1;
    // modificam continutul lui `hi`
    queue->hi->value = value;
    queue->hi->link = tmp;
    queue->hi = tmp;
    return 0;
}


int queue_pop(queue_t * queue, key_t * value)
{
    if (queue_empty(*queue))
        return 1; // este vida, nu avem ce scoate
    // scriem valoarea
    *value = queue->lo->value;
    // eliberam memoria
    _queue_t * tmp = queue->lo;
    queue->lo = queue->lo->link;
    free(tmp);
    return 0;
}
