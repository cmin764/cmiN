// j: operatii cu multimi pe biti


#include <stdio.h>


#define N 32
#define DBG 0


typedef struct {
    unsigned long bit; /* same as uint_32
                          or unsigned int */
    int len, vec[N];
} Multime;


void vec2bit(Multime* mul)
{
    mul->bit = 0;
    for (int i = 0; i < mul->len; ++i)
        mul->bit |= 1 << mul->vec[i];
}


void bit2vec(Multime* mul)
{
    mul->len = 0;
    for (int i = 0; i < 32; ++i)
        if (1 << i & mul->bit)
            mul->vec[mul->len++] = i;
}


Multime reuniune(Multime mul1, Multime mul2)
{
    Multime mul;
    mul.bit = mul1.bit | mul2.bit;
    return mul;
}


Multime intersectie(Multime mul1, Multime mul2)
{
    Multime mul;
    mul.bit = mul1.bit & mul2.bit;
    return mul;
}


Multime diferenta(Multime mul1, Multime mul2)
{
    Multime mul;
    mul.bit = mul1.bit ^ (mul1.bit & mul2.bit);
    return mul;
}


Multime complementara(Multime mul)
{
    mul.bit = ~mul.bit; 
    return mul;
}


int main()
{
    Multime mul1, mul2;
    printf("Dimensiune A: ");
    scanf("%d", &mul1.len);
    printf("A: ");
    for (int i = 0; i < mul1.len; ++i)
        scanf("%d", mul1.vec + i);
    printf("Dimensiune B: ");
    scanf("%d", &mul2.len);
    printf("B: ");
    for (int i = 0; i < mul2.len; ++i)
        scanf("%d", mul2.vec + i);
    putchar('\n');
    vec2bit(&mul1);
    vec2bit(&mul2);
    Multime mul;
    do {
        puts("[1] Reuniune");
        puts("[2] Intersectie");
        puts("[3] Diferenta");
        puts("[4] Complementara");
        puts("[0] Iesire");
        printf(">>> ");
        int ans = 0;
        scanf("%d", &ans);
        switch (ans) {
            case 1:
            mul = reuniune(mul1, mul2);
            break;
            case 2:
            mul = intersectie(mul1, mul2);
            break;
            case 3:
            mul = diferenta(mul1, mul2);
            break;
            case 4:
            mul = complementara(mul1);
            break;
            case 0:
            break;
            default:
            ans = -1;
            puts("Optiune invalida\n");
        }
        if (ans == -1) continue;
        if (ans) {
            bit2vec(&mul);
            for (int i = 0; i < mul.len; ++i)
                printf("%d ", mul.vec[i]);
            puts("\n");
        } else
            break;
    } while(1);
    return 0;
}
