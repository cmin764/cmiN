// b: cea mai lunga secventa de elemente egale


#include <stdio.h> // i/o
#include <stdlib.h> // alocare dinamica


typedef struct {
    int ind;
    int len;
} Sec;


void sec_init(Sec* sec)
{
    sec->ind = -1;
    sec->len = 0;
}


void max_secv(int len, int* vec, Sec* sec)
{
    if (!len) return; // vector vid
    // pozitia si lungimea curenta
    int secLen = 1, secInd = 0;
    // element ce inca respecta proprietatea
    int last = vec[secInd];
    for (int i = 1; i < len; ++i) {
        // iteram si pentru fiecare potrivire
        // se mareste lungimea secventei
        if (vec[i] == last) ++secLen;
        // elementul difera, deci incheiem
        // secventa, apoi ii comparam lungimea
        else {
            if (secLen > sec->len) {
                sec->len = secLen;
                sec->ind = secInd;
            }
            // actualizam
            secInd = i;
            secLen = 1;
            last = vec[i]; 
        }
    }
    // redundanta din cauza optimizarii
    if (secLen > sec->len) {
        sec->len = secLen;
        sec->ind = secInd;
    }
}


int main()
{
    int* vec;
    int nr;
    printf("Numarul de numere: ");
    scanf("%d", &nr);
    vec = (int*)malloc(nr * sizeof(int));
    printf("Numerele: ");
    for (int i = 0; i < nr; ++i)
        scanf("%d", vec + i);
    // structura pentru stocarea rezultatului
    Sec sec;
    sec_init(&sec);
    max_secv(nr, vec, &sec);
    free(vec);
    printf("Pozitia %d, lungimea %d\n", sec.ind, sec.len);
    return 0;
}
