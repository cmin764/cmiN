#include <cstdio>
using namespace std;


#define N 128


void asm_process(char string[])
{
    char letters[N];
    letters[0] = 0;

    _asm {
        sub esp, 16

        mov eax, 97
        sub eax, 65
        mov [esp], eax    ; diff

        mov eax, 1
        mov [esp+4], eax    ; show

        mov ebx, [ebp+8]
        mov [esp+8], ebx    ; pc

        lea ebx, letters
        mov [esp+12], ebx

    for0:
        mov ebx, [esp+8]
        mov cl, byte ptr [ebx]
        test cl, cl
        jz for0_end

        cmp cl, 32
        jne next0
        mov eax, 1
        mov [esp+4], eax
    next0:
        cmp cl, 65
        jl increment
        cmp cl, 122
        jg increment
        cmp cl, 90
        jg check
        jmp next1
    check:
        cmp cl, 97
        jl increment

    next1:
        mov eax, [esp+4]
        test eax, eax
        jz increment
        mov eax, 0
        mov [esp+4], eax
        cmp cl, 97
        jl big
        mov eax, [esp]
        movsx al, eax
        sub cl, al
    big:
        mov ebx, [esp+12]
        mov byte ptr [ebx], cl
        inc dword ptr [esp+12]

    increment:
        inc dword ptr [esp+8]
        jmp for0
    for0_end:
        mov ebx, [esp+12]
        mov byte ptr [ebx], cl

    end:
        add esp, 16
    }
    puts(letters);
}


void process(char string[])
{
    int diff = 'a' - 'A';
    bool show = true;
    for (char * pc = string; *pc; ++pc) {
        if (*pc == ' ')
            show = true;
        if (!(*pc >= 'a' && *pc <= 'z' ||
              *pc >= 'A' && *pc <= 'Z'))
                continue;

        if (show) {
            if (*pc >= 'a' && *pc <= 'z')
                *pc -= diff;
            putchar(*pc);
            show = false;
        }
    }
    putchar('\n');
}


int main()
{
    char string[N];
    fputs("Propozitie: ", stdout);
    gets(string);

    asm_process(string);

    return 0;
}
