#include <iostream>
#define nmax 128

using namespace std;

void insertionsort(int vec[], int vlen)
{
    // avg and wst: O(pow(n, 2)/2)
    int tmp, i, j;
    for (i = 1; i < vlen; i++) {
        tmp = vec[i];
        for (j = i - 1; j >= 0 && tmp < vec[j]; j--) {
            vec[j + 1] = vec[j];
        }
        vec[j + 1] = tmp;
    }
}

void mergesort(int vec[], int vlen)
{
    // avg and wst: O(n*log(n, 2))
    if (vlen > 1) {
        int mlen, i, j, k;
        int* tvec = new int[vlen];
        for (i = 0; i < vlen; i++) {
            tvec[i] = vec[i];
        }
        mlen = vlen / 2;
        mergesort(tvec, mlen);
        mergesort(tvec + mlen, vlen - mlen);
        if (tvec[mlen - 1] < tvec[mlen]) {
            for (i = 0; i < vlen; i++) {
                vec[i] = tvec[i];
            }
        } else {
            for (i = 0, j = mlen, k = 0; i < mlen && j < vlen; k++) {
                if (tvec[i] < tvec[j]) {
                    vec[k] = tvec[i];
                    i++;
                } else {
                    vec[k] = tvec[j];
                    j++;
                }
            }
            while (i < mlen) {
                vec[k++] = tvec[i++];
            }
            while (j < vlen) {
                vec[k++] = tvec[j++];
            }
        }
        delete[] tvec;
    }
}

int main()
{
    int vec[nmax], vlen, i;
    cout << "Vector length: ";
    cin >> vlen;
    for (i = 0; i < vlen; i++) {
        cout << "vec[" << i << "]: ";
        cin >> vec[i];
    }
    //insertionsort(vec, vlen);
    mergesort(vec, vlen);
    for (i = 0; i < vlen; i++) {
        cout << vec[i] << " ";
    }
    return 0;
}
