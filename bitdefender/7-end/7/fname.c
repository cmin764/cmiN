#include <cstdio>


int main()
{
    char vec[128];
    int len = 0;

    _asm {
        xor esi, esi
        mov ebx, 6656
start:
        mov     eax, 1321528399
        imul    ebx             ; eax * ebx -> edx:eax
        sar     edx, 3          ; edx = edx / 8
        mov     ecx, edx        ; ecx = SUP(1321528399 * ebx) / 8
        shr     ecx, 31         ; ecx = MSB(ecx)
        add     ecx, edx        ; ecx = edx + (1|0) (semnul lui (SUP(...) / 8))
        mov     al, cl
        mov     dl, 26
        imul    dl              ; inmulteste ultimii 8 biti din ecx cu 26 si scade din
                               ; ultimii 8 biti ai dimensiunii, acest rezultat
        sub     bl, al
        add     bl, 97          ; apoi adauga 97 (ca sa inceapa cu "a")
        lea     eax, vec
        mov     byte ptr [eax+esi], bl ; scrie octetul calculat in buffer
        add len, 1
        mov     ebx, ecx    
        add     esi, 1          ; incrementeaza contorul si continua procesul pana cand
                              ; dimensiunea devine 0 sau negativa
        test    ebx, ebx
        jg  start
    }
    vec[len] = '\0';
    printf("%d %s\n", len, vec);
	return 0;
}

