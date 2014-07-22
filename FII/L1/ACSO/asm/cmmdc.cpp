#include <cstdio>
using namespace std;


int cmmdc(int a, int b)
{
    while (b) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}


int main()
{
    
    int a, b, rez = -1;
    fputs("Numerele: ", stdout);
    scanf("%d %d", &a, &b);
    /*_asm {
        mov eax, 2
        mov ebx, 4
        mov edx, 0
        div ebx
        mov rez, edx
    }*/
    printf("[C] %d\n", cmmdc(a, b));
    // acum si varianta asm
    _asm {
        mov eax, a
        mov ebx, b

    while1:
        cmp ebx, 0
        je end

        mov edx, 0
        div ebx
        mov eax, ebx
        mov ebx, edx

        jmp while1
    end:
        mov rez, eax
    }
    printf("[ASM] %d\n", rez);
    return 0;
}
