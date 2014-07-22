#include <iostream>
using namespace std;

int main()
{
    int vec[128], n, len[128], k, i, mlen, gmlen = 0, pos;
    cout << "Lungimea sirului: ";
    cin >> n;
    cout << "Introduceti elementele...";
    for (i = 0; i < n; i++) {
        cin >> vec[i];
    }
    len[n - 1] = 1;
    for (k = n - 2; k >= 0; k--) {
        mlen = 0;
        for (i = k + 1; i < n; i++) {
            if ((vec[k] < vec[i]) && (len[i] > mlen)) {
                mlen = len[i];
            }
        }
        len[k] = mlen + 1;
        if (len[k] > gmlen) {
            gmlen = len[k];
            pos = k;
        }
    }
    cout << "Cel mai lung subsir crescator are " << gmlen << " elemente si este...\n";
    cout << vec[pos] << " ";
    gmlen--;
    for (i = pos + 1; i < n; i++) {
        if ((vec[i] > vec[pos]) && (gmlen == len[i])) {
            cout << vec[i] << " ";
            gmlen--;
        }
    }
    system("pause >nul");
    return 0;
}
