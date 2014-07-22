#include <fstream>
using namespace std;

void process(char *mystr, int i, int cnr)
{
    char tstr[4000];
    strcpy(tstr, mystr + i + 1);
    while (cnr-- > 0)
    {
        mystr[i++] = '(';
    }
    strcpy(mystr + i, tstr);
}

void dreverse(char *mystr)
{
    int i, j, len;
    char temp;
    len = strlen(mystr);
    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        if (mystr[i] == '(')
        {
            mystr[i] = ')';
        }
        else if (mystr[i] == ')')
        {
            mystr[i] = '(';
        }
        else if (mystr[i] == '[')
        {
            mystr[i] = ']';
        }
        else if (mystr[i] == ']')
        {
            mystr[i] = '[';
        }
        if (mystr[j] == '(')
        {
            mystr[j] = ')';
        }
        else if (mystr[j] == ')')
        {
            mystr[j] = '(';
        }
        else if (mystr[j] == '[')
        {
            mystr[j] = ']';
        }
        else if (mystr[j] == ']')
        {
            mystr[j] = '[';
        }
        temp = mystr[i];
        mystr[i] = mystr[j];
        mystr[j] = temp;
    }
    if (i == j)
    {
        if (mystr[i] == '(')
        {
            mystr[i] = ')';
        }
        else if (mystr[i] == ')')
        {
            mystr[i] = '(';
        }
        else if (mystr[i] == '[')
        {
            mystr[i] = ']';
        }
        else if (mystr[i] == ']')
        {
            mystr[i] = '[';
        }
    }
}

int main()
{
    int i = 0, j, len;
    char mystr[4000];
    bool flag = true;
    fstream myfile;
    myfile.open("scp.in", ios::in);
    myfile.getline(mystr, 2002);
    myfile.close();
    struct
    {
        int ds;
        int is;
    } par1, par2;
    while(mystr[i] || flag)
    {
        if (mystr[i] == '[')
        {
            par1.ds = 0;
            par1.is = 0;
            par2.ds = 0;
            par2.is = 0;
            len = strlen(mystr);
            for (j = i + 1; j < len; j++)
            {
                if (mystr[j] == '(')
                {
                    par1.ds++;
                }
                else if (mystr[j] == ')')
                {
                    if (par1.ds > 0)
                    {
                        par1.ds--;
                    }
                    else
                    {
                        par1.is++;
                    }
                }
            }
            for (j = i - 1; j >= 0; j--)
            {
                if (mystr[j] == ')')
                {
                    par2.is++;
                }
                else if (mystr[j] == '(')
                {
                    if (par2.is > 0)
                    {
                        par2.is--;
                    }
                    else
                    {
                        par2.ds++;
                    }
                }
            }
            process(mystr, i, par1.is - par2.ds);
            i--;
        }
        i++;
        if (!mystr[i] && flag)
        {
            flag = false;
            i = 0;
            dreverse(mystr);
        }
    }
    dreverse(mystr);
    len = strlen(mystr);
    par1.ds = 0;
    par1.is = 0;
    for (i = 0; i < len; i++)
    {
        if (mystr[i] == '(')
        {
            par1.ds++;
        }
        else if (mystr[i] == ')')
        {
            if (par1.ds > 0)
            {
                par1.ds--;
            }
            else
            {
                par1.is++;
            }
        }
    }
    myfile.open("scp.out", ios::out);
    if (par1.ds == 0 && par1.is == 0)
    {
        myfile << mystr;
    }
    else
    {
        myfile << "IMPOSIBIL";
    }
    myfile.close();
    return 0;
}
