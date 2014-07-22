#include <stdlib.h>

#include "pqueue.h"


#define PARENT(x) ((x - 1) / 2)
#define LEFT(x) (x * 2 + 1)
#define RIGHT(x) (x * 2 + 2)


void pqueue_create(pqueue_t * pqueue)
{
    pqueue->size = 0;
    pqueue->capacity = 1;
    pqueue->vec = (key_t *)malloc(sizeof(key_t));
}


static inline void swap(key_t * first,
                        key_t * second)
{
    key_t tmp = *first;
    *first = *second;
    *second = tmp;
}


static void heapify_up(key_t * vec, size_t pos)
{
    /* daca am ajuns in radacina sau daca
       este respectata proprietatea */
    if (!pos || vec[pos].priority >=
                vec[PARENT(pos)].priority)
        return; // proprietate restabilita
    // trebuie sa "urcam" elementul
    swap(&vec[pos], &vec[PARENT(pos)]);
    heapify_up(vec, PARENT(pos));
}


void pqueue_push(pqueue_t * pqueue, key_t key)
{
    // verificam daca incape in memorie
    if (pqueue->size + 1 > pqueue->capacity)
        // extindem vectorul
        pqueue->vec = (key_t *)realloc(pqueue->vec,
        sizeof(key_t) * (pqueue->capacity *= 2));
    if (!pqueue->vec)
        exit(EXIT_FAILURE);
    pqueue->vec[pqueue->size++] = key;
    // acum trebuie sa mentinem proprietatea de heap
    heapify_up(pqueue->vec, pqueue->size - 1);
}


static inline key_t min(key_t first, key_t second)
{
    return first.priority < second.priority \
           ? first : second;
}


static void heapify_down(key_t * vec, size_t pos,
                         size_t maxPos)
{
    if (LEFT(pos) > maxPos)
        return; // nu mai avem cu ce compara
    // avem stanga, verificam si pentru dreapta
    if (RIGHT(pos) <= maxPos) {
        // avem si fiu drept
        if (vec[pos].priority <= min(vec[LEFT(pos)],
            vec[RIGHT(pos)]).priority)
            return; // proprietate restabilita
        if (vec[LEFT(pos)].priority <=
            vec[RIGHT(pos)].priority) {
            swap(&vec[pos], &vec[LEFT(pos)]);
            heapify_down(vec, LEFT(pos), maxPos);
        } else {
            swap(&vec[pos], &vec[RIGHT(pos)]);
            heapify_down(vec, RIGHT(pos), maxPos);
        }
    } else {
        // avem doar fiu stang
        if (vec[pos].priority <=
            vec[LEFT(pos)].priority)
            return; // proprietate restabilita
        swap(&vec[pos], &vec[LEFT(pos)]);
        heapify_down(vec, LEFT(pos), maxPos);
    }
}


key_t pqueue_pop(pqueue_t * pqueue)
{
    /* interschimbam primul cu ultimul element
       din vector si mentinem proprietatea de
       heap dupa ce scoatem noul ultim element */
    key_t ret = *pqueue->vec;
    swap(pqueue->vec, pqueue->vec + pqueue->size - 1);
    --pqueue->size;
    if (pqueue->size)
        heapify_down(pqueue->vec, 0, pqueue->size - 1);
    return ret;
}


int pqueue_empty(const pqueue_t * pqueue)
{
    return !pqueue->size;
}


void pqueue_destroy(pqueue_t * pqueue)
{
    free(pqueue->vec);
    pqueue->size = 0;
    pqueue->capacity = 0;
}
