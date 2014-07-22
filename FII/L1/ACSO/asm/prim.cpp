#include <cstdio>
#include <cmath>
using namespace std;


typedef unsigned int ui_t;


int main()
{
    ui_t nr, srNr;
    fputs("Numar: ", stdout);
    scanf("%u", &nr);
    srNr = (ui_t)sqrt((float)nr);
    ui_t flag = 1; // este prim
    ui_t _ecx = 0;
    _asm {
        mov eax, nr
        mov edx, 0

        cmp eax, 0
        je end0

        cmp eax, 1
        je end0

        cmp eax, 2
        je end1

        mov ebx, 2
        div ebx
        cmp edx, 0
        je end0

        ; numar impar, mai mare
        ; sau egal cu 3
        mov ebx, srNr ; radacina
        mov ecx, 3
    for0:
        cmp ecx, ebx
        jg end1
        mov eax, nr
        mov edx, 0
        div ecx
        mov _ecx, ecx
        cmp edx, 0
        je end0
        add ecx, 2
        jmp for0
    end0:
        mov flag, 0
    end1:
    }
    if (flag)
        printf("Este prim\n");
    else
        printf("Nu este prim: %u\n", _ecx);
    return 0;
}
