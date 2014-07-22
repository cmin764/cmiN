/*
 * Cod compatibil C pentru inmultirea a doua matrici.
 * Contine inline assembly echivalent procesului de
 * inmultire.
 */


#include <cstdio>
#include <cstdlib>
using namespace std;


void init(int * n, int * mn, int * m,
          int *** mat1, int *** mat2, int *** rez)
{
    fputs("Linii 1: ", stdout);
    scanf("%d", n);
    fputs("Coloane/Linii 1/2: ", stdout);
    scanf("%d", mn);
    fputs("Coloane 2: ", stdout);
    scanf("%d", m);

    // alocam memorie celor doua matrici
    *mat1 = (int **)malloc(sizeof(int *) * *n);
    *mat2 = (int **)malloc(sizeof(int *) * *mn);

    puts("Matricea 1...");
    for (int i = 0; i < *n; ++i) {
        (*mat1)[i] = (int *)malloc(sizeof(int) * *mn);
        printf("Linia %d: ", i + 1);
        for (int j = 0; j < *mn; ++j)
            scanf("%d", &(*mat1)[i][j]);
    }

    puts("Matricea 2...");
    for (int i = 0; i < *mn; ++i) {
        (*mat2)[i] = (int *)malloc(sizeof(int) * *m);
        printf("Linia %d: ", i + 1);
        for (int j = 0; j < *m; ++j)
            scanf("%d", &(*mat2)[i][j]);
    }

    // matricea rezultat are `n` linii si `m` cooloane
    *rez = (int **)malloc(sizeof(int *) * *n);
    for (int i = 0; i < *n; ++i)
        // initializam fiecare linie cu zerouri
        (*rez)[i] = (int *)calloc(*m, sizeof(int));
}


void show(int lin, int col, int ** mat)
{
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j)
            printf("%d ", mat[i][j]);
        putchar('\n');
    }
}


void release(int lin, int ** mat)
{
    for (int i = 0; i < lin; ++i)
        free(mat[i]);
    free(mat);
}


void mul(int ** rez, int n, int mn, int m,
         int ** mat1, int ** mat2)
{
    // inmultirea propriu-zisa
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < mn; ++k)
                rez[i][j] += mat1[i][k] * mat2[k][j];
}


int main()
{
    int n, mn, m;
    int ** rez, ** mat1, ** mat2;
    init(&n, &mn, &m, &mat1, &mat2, &rez);
    //mul(rez, n, mn, m, mat1, mat2);
    _asm {
        xor ecx, ecx
        for0:
            cmp ecx, n
            jge _for0

            push ecx
            xor ecx, ecx
            for1:
                cmp ecx, m
                jge _for1

                push ecx
                xor ecx, ecx
                for2:
                    cmp ecx, mn
                    jge _for2

                    ; eax <- mat1[i][k]
                    mov ebx, mat1
                    mov edx, dword ptr [esp+4]     ; i
                    mov ebx, dword ptr [ebx+edx*4] ; mat1[i]
                    mov eax, dword ptr [ebx+ecx*4] ; mat1[i][k]

                    ; eax <- eax * mat2[k][j]
                    mov ebx, mat2
                    mov edx, dword ptr [esp]       ; j
                    mov ebx, dword ptr [ebx+ecx*4] ; mat2[k]
                    mov edx, dword ptr [ebx+edx*4] ; mat2[k][j]
                    mul edx

                    ; rez[i][j] += eax
                    mov ebx, rez
                    mov edx, dword ptr [esp+4]     ; i
                    mov ebx, dword ptr [ebx+edx*4] ; rez[i]
                    mov edx, dword ptr [esp]       ; j
                    add dword ptr [ebx+edx*4], eax

                    inc ecx
                    jmp for2
                _for2:
                pop ecx

                inc ecx
                jmp for1
            _for1:
            pop ecx
        
            inc ecx
            jmp for0
        _for0:
    }
    show(n, m, rez);
    release(n, mat1);
    release(mn, mat2);
    release(n, rez);
    return 0;
}
