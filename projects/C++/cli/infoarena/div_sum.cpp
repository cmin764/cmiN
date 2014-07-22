#include <cstdio>

int divsum(int vec[], int sta, int end)
{
    if (sta == end - 1) {
        return vec[sta];
    } else {
        int mid = (sta + end) / 2;
        return divsum(vec, sta, mid) + divsum(vec, mid, end);
    }
}

int main()
{
    int len, vec[32];
    printf("Numar de elemente: ");
    scanf("%d", &len);
    printf("Introduceti %d elemente: ", len);
    for (int i = 0; i < len; i++) {
        scanf("%d", vec + i);
    }
    printf("Suma este %d.\n", divsum(vec, 0, len));
    return 0;
}
