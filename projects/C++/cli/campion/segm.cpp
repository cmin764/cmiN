#include <fstream>
using namespace std;

typedef unsigned long int uli_t;
typedef unsigned int ui_t;

void dsorted(uli_t v[][2], ui_t &N)
{
    uli_t temp[2];
    bool flag;
    do
    {
        flag = false;
        for (ui_t i = 0; i < N - 1; i++)
        {
            if ((v[i][1] - v[i][0]) > (v[i + 1][1] - v[i + 1][0]))
            {
                temp[0] = v[i][0];
                temp[1] = v[i][1];
                v[i][0] = v[i + 1][0];
                v[i][1] = v[i + 1][1];
                v[i + 1][0] = temp[0];
                v[i + 1][1] = temp[1];
                flag = true;
            }
        }
    }
    while (flag);
}

void sorted(uli_t m[], ui_t &M)
{
    uli_t temp;
    bool flag;
    do
    {
        flag = false;
        for (ui_t i = 0; i < M - 1; i++)
        {
            if (m[i] > m[i + 1])
            {
                temp = m[i];
                m[i] = m[i + 1];
                m[i + 1] = temp;
                flag = true;
            }
        }
    }
    while (flag);
}

int main()
{
    ui_t N, M = 0, count;
    ifstream fin("segm.in");
    fin >> N;
    uli_t v[N][2], *m, temp = 0;
    m[0] = 0;
    for (ui_t i = 0; i < N; i++)
    {
        fin >> v[i][0] >> v[i][1];
    }
    fin.close();
    dsorted(v, N);
    for (ui_t i = 0; i < N; i++)
    {
        count = 0;
        for (ui_t j = 0; j <= M; j++)
        {
            if ((v[i][0] <= m[j]) && (m[j] <= v[i][1]))
            {
                count++;
                temp = m[j];
            }
            if (count == 2)
            {
                break;
            }
        }
        if (count == 0)
        {    
            M++;
            m[M] = v[i][0];
            M++;
            m[M] = v[i][1];
        }
        else if (count == 1)
        {
            M++;
            bool flag = true;
            for (ui_t k = i + 1; k <= M; k++)
            {
                if ((v[k][0] >= v[i][0]) && (v[k][0] <= v[i][1]) && (v[k][0] != temp))
                {
                    m[M] = v[k][0];
                    flag = false;
                    break;
                }
                else if ((v[k][1] >= v[i][0]) && (v[k][1] <= v[i][1]) && (v[k][1] != temp))
                {
                    m[M] = v[k][1];
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                if (temp == v[i][0])
                {
                    m[M] = v[i][1];
                }
                else
                {
                    m[M] = v[i][0];
                }
            }
        }
    }
    m++;
    sorted(m, M);
    ofstream fout("segm.out");
    fout << M << "\n";
    for (ui_t i = 0; i < M; i++)
    {
        fout << m[i];
        if (i != M - 1)
        {
            fout << " ";
        }
    }
    fout.close();
    return 0;
}
