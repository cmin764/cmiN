#include <cstdio>
#include <cstdlib>
using namespace std;


#define DBG 0 // debug


void init(int * & vec, int & len)
{
    fputs("Numar elemente: ", stdout);
    scanf("%d", &len);
    vec = (int *)malloc(sizeof(int) * len);
    if (!vec)
        exit(EXIT_FAILURE);
    fputs("Elemente: ", stdout);
    for (int i = 0; i < len; ++i)
        scanf("%d", vec + i);
}


void show(int * vec, int len)
{
    fputs("Elemente: ", stdout);
    for (int i = 0; i < len; ++i)
        printf("%d ", vec[i]);
    putchar('\n');
}


void bsort(int * vec, int len)
{
    int swed, k = 0;
    do {
        swed = 0;
        ++k;
        for (int i = 0; i < len - k; ++i)
            if (vec[i] > vec[i + 1]) {
                swed = 1;
                vec[i] -= vec[i + 1];
                vec[i + 1] += vec[i];
                vec[i] = vec[i + 1] - vec[i]; 
            }
    } while (swed);
}


int main()
{
    int len = -1, * vec = NULL;
    
    #if DBG
    int _eax, _ebx, _ecx, _edx;
    #endif

    init(vec, len);
    //bsort(vec, len);

    // assembly bubble sort
    _asm {
        mov eax, len    ; lungimea vectorului
        mov ebx, vec    ; pointer la primul element din vector

        while0:
            ; executam cat timp avem interschimbari
            xor edx, edx    ; marcam ca nu s-a facut vreo interschimbare
            dec eax         ; trebuie sa verificam mai putin cu un element
            xor ecx, ecx    ; pornim de la primul element

            for0:
                cmp ecx, eax
                jge _for0

                if0:
                    push eax                              ; salvam vechea valoare
                    ; valoarea urmatorului element
                    inc ecx
                    mov eax, dword ptr [ebx+ecx*4]
                    dec ecx
                    cmp dword ptr [ebx+ecx*4], eax        ; comparam elementul curent cu cel urmator
                    jle _if0                              ; nu avem nimic de facut
                    ; interschimbam
                    or edx, 1                             ; marcam efectuarea interschimbarii
                    xor eax, dword ptr [ebx+ecx*4]
                    xor dword ptr [ebx+ecx*4], eax
                    xor eax, dword ptr [ebx+ecx*4]
                    inc ecx
                    mov dword ptr [ebx+ecx*4], eax
                    dec ecx
                _if0:
                    pop eax                               ; restauram lungimea

                inc ecx
                jmp for0
            _for0:

            cmp edx, 0
            jne while0
        _while0:
    }

    #if DBG
    _asm {
        mov eax, -1
        mov edx, -1
        xor ebx, ebx
        xor ecx, ecx

        mov ebx, vec
        inc ecx
        mov eax, dword ptr [ebx+ecx*4]
        dec ecx

        xor eax, dword ptr[ebx+ecx*4]
        xor dword ptr[ebx+ecx*4], eax
        xor eax, dword ptr[ebx+ecx*4]

        inc ecx
        mov dword ptr [ebx+ecx*4], eax 
        dec ecx

        mov _eax, eax
        mov _ebx, ebx
        mov _ecx, ecx
        mov _edx, edx
    }
    fprintf(stderr, "a: %d b: %d c: %d d: %d\n",
            _eax, _ebx, _ecx, _edx);
    #endif

    show(vec, len);
    free(vec);
    return 0;
}
