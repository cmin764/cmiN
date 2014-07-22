#include <cstdio>
#include <set>

using namespace std;

int main()
{
    freopen("heapuri.in", "rt", stdin);
    freopen("heapuri.out", "wt", stdout);
    unsigned short int op;
    unsigned long int value, nr, vec[200001], poz = 1;
    set<unsigned long int> myset;
    scanf("%lu", &nr);
    while (nr > 0) {
        scanf("%hu", &op);
        switch (op) {
        case 1:
            scanf("%lu", &value);
            myset.insert(value);
            vec[poz++] = value;
            break;
        case 2:
            scanf("%lu", &value);
            myset.erase(vec[value]);
            break;
        case 3:
            printf("%ld\n", *(myset.begin()));
            break;
        }
        nr--;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
