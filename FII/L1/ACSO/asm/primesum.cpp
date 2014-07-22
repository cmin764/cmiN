#include <cstdio>
using namespace std;


int _PrimeSum(int nr)
{
    int sum = 0, last = 2;
    while (nr-- > 0) {
        printf("%d ", last);
        sum += last;
        while (1) {
            ++last;
            int ok = 1;
            for (int i = 2; i <= last / 2 && ok; ++i)
                if (!(last % i))
                    ok = 0;
            if (ok)
                break;
        }
    }
    putchar('\n');
    return sum;
}


int PrimeSum(int nr)
{
    _asm {
        sub esp, 20

        xor eax, eax
        mov [ebp-4], eax    ; sum

        mov eax, 2
        mov [ebp-8], eax    ; last

        mov eax, [ebp+8]    ; nr
        mov [ebp-20], eax

    while0:
        mov eax, [ebp-20]
        test eax, eax
        jz end

        ; aduna la suma ultimul numar prim gasit
        mov eax, [ebp-4]
        mov edx, [ebp-8]
        add eax, edx
        mov [ebp-4], eax

        xor eax, eax
        mov [ebp-12], eax    ; prim sau nu
    while1:
        mov eax, [ebp-12]
        test eax, eax
        jnz while1_end

        ; cautam numar prim
        mov eax, [ebp-8]
        inc eax
        mov [ebp-8], eax
        mov eax, 1
        mov [ebp-12], eax    ; presupunem ca este prim

        mov ecx, 1
        mov [ebp-16], ecx    ; contor
    for0:
        mov ecx, [ebp-16]
        inc ecx
        mov [ebp-16], ecx
        mov eax, [ebp-8]
        shr eax, 1
        cmp ecx, eax
        jg for0_end

        mov eax, [ebp-8]
        xor edx, edx
        div ecx
        test edx, edx
        jnz for0    ; nu este divizibil

        ; este divizibil
        mov eax, 0
        mov [ebp-12], eax

    for0_end:
        jmp while1

    while1_end:

        mov eax, [ebp-20]
        dec eax
        mov [ebp-20], eax
        jmp while0

     end:
        mov eax, [ebp-4]
        add esp, 20
    }
}


int main()
{
    int nr;
    fputs("Numar: ", stdout);
    scanf("%d", &nr);
    int sum = PrimeSum(nr);
    printf("%d\n", sum);
    return 0;
}
