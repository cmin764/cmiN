// func.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"


int main(int argc, char * argv[])
{
    int vecLen, evenVecLen = 0;
    fputs("Numar: ", stdout);
    scanf("%d", &vecLen);
    int * vec = (int *)malloc(sizeof(int) * vecLen);
    int * evenVec = (int *)malloc(sizeof(int) * vecLen);
    fputs("Elemente: ", stdout);
    for (int i = 0; i < vecLen; ++i)
        scanf("%d", vec + i);

    _asm {
        lea ebx, evenVecLen
        mov dword ptr [ebx], 0
        push ebx
        mov ebx, evenVec
        push ebx
        mov eax, vecLen
        push eax
        mov ebx, vec
        push ebx
        call start
        jmp end

    start:
        push ebp
        mov ebp, esp
        sub esp, 4

        mov [ebp-4], 0
    for0:
        mov ecx, [ebp-4]
        mov eax, [ebp+12]
        cmp ecx, eax
        jge for0_end

        mov ebx, [ebp+8]
        mov ecx, [ebp-4]
        mov eax, [ebx+ecx*4]

        xor edx, edx
        mov esi, 2
        div esi
        test edx, edx
        jnz increment
        
        mov eax, [ebx+ecx*4]
        mov ebx, [ebp+16]
        mov ecx, [ebp+20]
        mov edx, [ecx]
        mov [ebx+edx*4], eax
        inc dword ptr [ecx]

    increment:
        inc [ebp-4]
        jmp for0
    for0_end:

    start_end:
        mov esp, ebp
        pop ebp
        retn 16

    end:
    }

    for (int i = 0; i < evenVecLen; ++i)
        printf("%d ", evenVec[i]);
    putchar('\n');

    free(vec);
    free(evenVec);
	return 0;
}
