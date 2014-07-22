#include <stdio.h>

const int n = 5120;
const long minf = -0x7FffFFff;
int col, step, mat[2][n];
long sol[2][n];

void file_handler(bool flag)
{
    if (flag) {
        freopen("joc13.in", "rt", stdin);
        freopen("joc13.out", "wt", stdout);
    } else {
        fclose(stdin);
        fclose(stdout);
    }
}

void read()
{
    scanf("%d %d", &col, &step);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", mat[i] + j);
        }
    }
}

void write()
{
    printf("%d", sol[1][col - 1]);
}

void compute()
{
    long max;
    int sum;
    sol[0][0] = mat[0][0];
    sol[0][1] = 0;
    for (int i = 1; i < col; i++) {
        for (int j = 0; j < 2; j++) {
            max = minf;
            sum = mat[j][i];
            for (int k = 1; k < step && k <= i; k++) {
                sum += mat[j][i - k];
                if (sum + sol[1 - j][i - k] > max) {
                    max = sum + sol[1 - j][i - k];
                }
            }
            sol[j][i] = max;
        }
    }
    if (sol[0][col - 1] + mat[1][col - 1] > sol[1][col - 1]) {
        sol[1][col - 1] = sol[0][col - 1] + mat[1][col -1];
    }
}

int main()
{
    file_handler(1);
    read();
    compute();
    write();
    file_handler(0);
    return 0;
}
