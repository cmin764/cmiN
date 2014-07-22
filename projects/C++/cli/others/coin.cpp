// DP and div CHANGE / COINS
#include <iostream>
#include <new>
#define cnr 4

using namespace std;
typedef unsigned long ul_t;
char coins[cnr] = {1, 3, 5, 10};

ul_t cf1(ul_t sum)
{
    ul_t csum = 0;
    for (int i = cnr - 1; i >= 0; i--) {
        csum += sum / coins[i];
        sum %= coins[i];
    }
    return csum;
}

ul_t cf2(ul_t sum)
{
    const ul_t cmax = 4294967295;
    ul_t * csum = new (nothrow) ul_t [sum + 1];
    if (csum == 0) {
        cout << "Suma prea mare!\n";
        return 0;
    }
    csum[0] = 0;
    for (ul_t s = 1; s <= sum; s++) {
        csum[s] = cmax;
        for (int i = 0; i < cnr; i++) {
            if (coins[i] <= s && (csum[s - coins[i]] + 1) < csum[s]) {
                csum[s] = 1 + csum[s - coins[i]];
            }
        }
    }
    return csum[sum];
}

int main()
{
    ul_t sum;
    cout << "Suma: ";
    cin >> sum;
    if (cf1(sum) == cf2(sum)) {
        cout << 1;
    } else {
        cout << 0;
    }
    system("pause >nul");
    return 0;
}
