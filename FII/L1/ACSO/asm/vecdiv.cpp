#include <cstdio>
using namespace std;


#define N 100


bool check(int vec[], int nr)
{
    int sum = vec[0];
    bool flag = 1;
    for (int i = 1; i < nr; ++i) {
        if (vec[i] % sum)
            flag = 0;
        sum += vec[i];
    }
    return flag;
}


int asm_check(int vec[], int nr)
{
    _asm {
        sub esp, 16

        mov ebx, [ebp+8]
        mov [ebp-4], ebx     ; vec 
        mov eax, [ebp+12]
        mov [ebp-8], eax     ; nr
        mov eax, 1
        mov [ebp-12], eax    ; i

        mov ebx, [ebp-4]
        mov eax, [ebx]
        mov [ebp-16], eax    ; sum

    for0:
        mov eax, [ebp-8]
        cmp [ebp-12], eax
        jge for0_end

        mov ebx, [ebp-4]
        mov ecx, [ebp-12]
        mov eax, [ebx+ecx*4]

        xor edx, edx
        mov ecx, [ebp-16]
        div ecx
        test edx, edx
        jnz exit_0

        mov edx, [ebp-12]
        mov eax, [ebx+edx*4]
        add ecx, eax
        mov [ebp-16], ecx
        inc edx
        mov [ebp-12], edx
        jmp for0
    for0_end:
        mov eax, 1
        jmp end

    exit_0:
        xor eax, eax
    end:
        add esp, 16
    }
}


int main()
{
    int vec[N], nr;
    fputs("Numar: ", stdout);
    scanf("%d", &nr);
    nr = nr > N ? N : nr;

    fputs("Elemente: ", stdout);
    for (int i = 0; i < nr; ++i)
        scanf("%d", vec + i);

    int ret = asm_check(vec, nr);
    printf("%d\n", ret);
    return 0;
}
