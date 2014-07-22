#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define inf 0x7fFFffFF
#define N 10001

short nodes, paths, ord[N];
unsigned int*** list;
char name[N][11];
int data[N],indexx[N],size;
int cost[N];

void swap(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void shift_up(int i)
{
        int j;
        while(i>0)
        {
            j=(i-1)/2;
            if(cost[data[i]]<cost[data[j]])
            {
                swap(&indexx[data[i]],&indexx[data[j]]);
                swap(&data[i],&data[j]);
                i=j;
            }
            else break;
        }
}
void shift_down(int i)
{
        int j,k;
        while(2*i+1<size)
        {
            j=2*i+1;
            k=j+1;
            if(k<size&&cost[data[k]]<cost[data[j]]&&cost[data[k]]<cost[data[i]])
            {
                swap(&indexx[data[k]],&indexx[data[i]]);
                swap(&data[k],&data[i]);
                i=k;
            }
            else if(cost[data[j]]<cost[data[i]])
            {
                swap(&indexx[data[j]],&indexx[data[i]]);
                swap(&data[j],&data[i]);
                i=j;
            }
            else break;
        }
}
void init()
{
        size=0;
        memset(indexx,-1,sizeof(indexx));
        memset(cost,-1,sizeof(cost));
}
short empty()
{
        return(size==0);
}
int pop()
{
        int res=data[0];
        data[0]=data[size-1];
        indexx[data[0]]=0;
        size--;
        shift_down(0);
        return res;
}
int top()
{
        return data[0];
}
void push(int x,int c)
{
        if(indexx[x]==-1)
        {
            cost[x]=c;
            data[size]=x;
            indexx[x]=size;
            size++;
            shift_up(indexx[x]);
        }
        else
        {
            if(c<cost[x])
            {
                cost[x]=c;
                shift_up(indexx[x]);
                shift_down(indexx[x]);
            }
        }
}

inline int cmp(const void* a, const void* b)
{
    return strcmp(name[*((const short*)a)], name[*((const short*)b)]);
}

short getindex(const char* string)
{
    short lo = 1, hi = nodes, mid, res;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        res = strcmp(string, name[ord[mid]]);
        if (!res) {
            return ord[mid];
        } else if (res > 0) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return 0;
}

void read()
{
    short i, j, nbs, nb;
    unsigned int cst;
    scanf("%hd", &nodes);
    list = (unsigned int***) malloc((nodes + 1) * sizeof(unsigned int**));
    for (i = 1; i <= nodes; ++i) {
        scanf("%s\n%hd", name[i], &nbs);
        ord[i] = i;
        list[i] = (unsigned int**) malloc((nbs + 1) * sizeof(unsigned int*));
        list[i][0] = (unsigned int*) malloc(sizeof(unsigned int));
        list[i][0][0] = nbs;
        for (j = 1; j <= nbs; ++j) {
            scanf("%hd %u", &nb, &cst);
            list[i][j] = (unsigned int*) malloc(2 * sizeof(unsigned int));
            list[i][j][0] = nb;
            list[i][j][1] = cst;
        }
    }
    qsort(ord + 1, nodes, sizeof(short), cmp);
    scanf("%hd", &paths);
}

void process()
{
    short i, j, src, dest, var;
    char tmp[11];
    for (i = 0; i < paths; ++i) {
        scanf("%s", tmp);
        src = getindex(tmp);
        scanf("%s", tmp);
        dest = getindex(tmp);
        init();
        push(src, 0);
        while (!empty()) {
            var = pop();
            if (var == dest) {
                printf("%d\n", cost[dest]);
                break;
            }
            for (j = 1; j <= list[var][0][0]; ++j) {
                push(list[var][j][0], cost[var] + list[var][j][1]);
            }
        }
    }
}

int main()
{
    short tests;
    freopen("shpath.in", "rt", stdin);
    for (scanf("%hd", &tests); tests; --tests) {
        read();
        process();
        free(list);
    }
    return 0;
}
