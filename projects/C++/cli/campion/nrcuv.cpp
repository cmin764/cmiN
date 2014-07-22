#include <fstream>
using namespace std;

int main()
{
    int cuv = 0, min = int('a'), max = int('z'), i;
    char mystr[200], *pch, *ptr;
    bool flag1, flag2;
    fstream myfile;
    myfile.open("nrcuv.in", ios::in);
    myfile.getline(mystr, 200);
    myfile.close();
    pch = strtok(mystr, " .,!?");
    while (pch)
    {
        ptr = strchr(pch, int('-'));
        if (ptr)
        {
            flag1 = false;
            flag2 = false;
            for (i = min; i <= max; i++)
            {
                if (int(*(ptr - 1)) == i)
                {
                    flag1 = true;
                }
                if (int(*(ptr + 1)) == i)
                {
                    flag2 = true;
                }
            }
            if (flag1 && flag2)
            {
                cuv++;
            }
        }
        else
        {
            cuv++;
        }
        pch = strtok(NULL, " .,!?");
    }
    myfile.open("nrcuv.out", ios::out);
    myfile << cuv;
    myfile.close();
    system("pause >NUL");
    return 0;
}
