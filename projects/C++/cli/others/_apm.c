/* Ai un graf cu n noduri si m muchii pe care le citesti dintr-un fisier.
 * Vrem sa construim APM asta inseamna ca trebuie sa ordonam muchiile
 * crescator in functie de costul lor apoi sa le selectam pe primele n-1
 * care nu formeaza cicluri.
 */

#include <stdio.h> // pentru citire
#include <stdlib.h> // pentru sortare (qsort)
#define N 100 // nr. max de noduri
#define M 1000 // nr. max de muchii

typedef struct {
    int x, y, c;
} Edge;

int nodes, edges, slct; // nodurile, muchiile si cele selectate
int cluster[N]; // cluster verifica ciclicitatea, actualizand componentele conexe
Edge edgeVec[M]; // vectorul de muchii, unde fiecare muchie leaga pe 'x' de 'y' avand constul 'c'
Edge apm[M]; // doar acele muchii care imi formeaza APM

void read()
{
    int i, x, y;
    //freopen("apm.in", "rt", stdin); // daca vrem deschidem fisierul si-l directionam in consola
    scanf("%d %d", &nodes, &edges); // citim
    for (i = 0; i < edges; ++i) { // citim iar
        scanf("%d %d %d", &edgeVec[i].x, &edgeVec[i].y, &edgeVec[i].c);
    }
    fclose(stdin);
}

inline int cmp(const void* first, const void* second)
{
    return ((const Edge*)first)->c - ((const Edge*)second)->c;
}

void kruskal()
{
    int i, j, ind1, ind2;
    for (i = 1; i <= nodes; ++i) {
        cluster[i] = i;
    }
    i = 0;
    while (slct < nodes - 1) { // cat timp nu avem un arbore
        if ((ind1 = cluster[edgeVec[i].x]) != (ind2 = cluster[edgeVec[i].y])) {
            /* retinem in ind1 indicele nodului 'x' din vectorul de muchii
             * asa facem si pentru ind2 ('y') apoi ii comparam si daca difera
             * inseamna ca cele 2 noduri nu fac parte din aceeasi componenta conexa
             * adica nu se obtine ciclu, adica totul e ok
             */
            apm[slct++] = edgeVec[i];
            for (j = 1; j <= nodes; ++j) {
                if (cluster[j] == ind2) {
                    cluster[j] = ind1;
                }
            }
        }
        ++i;
    }
}

void process()
{
    qsort(edgeVec, edges, sizeof(Edge), cmp); // sortam elementele vezi google: C qsort
    kruskal(); // sunt 2 metode Kruskal sau Prim ambele functioneaza cam la fel
}

void write()
{
    int total = 0, i;
    puts("Arborele partial de cost minim este format din muchiile: ");
    for (i = 0; i < slct; ++i) {
        printf("%d %d\n", apm[i].x, apm[i].y);
        total += apm[i].c;
    }
    printf("Si are costul: %d.\n", total);
}

int main()
{
    read();
    process();
    write();
    return 0;
}
