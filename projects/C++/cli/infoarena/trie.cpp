#include <cstdio>
#define nxt (*str - 'a')

struct Trie {
    int words, sons;
    Trie* to[26];
    Trie()
    {
        words = sons = 0;
        for (int i = 0; i < 26; i++) {
            to[i] = NULL;
        }
    }
}* root = new Trie;

void add(Trie* node, char* str)
{
    if (!(*str)) {
        node->words++;
    } else {
        if (!node->to[nxt]) {
            node->to[nxt] = new Trie;
            node->sons++;
        }
        add(node->to[nxt], str + 1);
    }
}

bool rmv(Trie* node, char* str)
{
    if (!(*str)) {
        node->words--;
    } else if (rmv(node->to[nxt], str + 1)) {
        node->to[nxt] = NULL;
        node->sons--;
    }
    if (!node->sons && !node->words && node != root) {
        delete node;
        return 1;
    } else {
        return 0;
    }
}

int cnt(Trie* node, char* str)
{
    if (!(*str)) {
        return node->words;
    } else if (node->to[nxt]) {
        return cnt(node->to[nxt], str + 1);
    } else {
        return 0;
    }
}

int prf(Trie* node, char* str, int nr)
{
    if (!(*str) || !node->to[nxt]) {
        return nr;
    } else {
        return prf(node->to[nxt], str + 1, nr + 1);
    }
}

int main()
{
    int op;
    char str[32];
    freopen("trie.in", "rt", stdin);
    freopen("trie.out", "wt", stdout);
    while (!feof(stdin)) {
        scanf("%d %s\n", &op, str);
        switch (op) {
        case 0:
            add(root, str);
            break;
        case 1:
            rmv(root, str);
            break;
        case 2:
            printf("%d\n", cnt(root, str));
            break;
        case 3:
            printf("%d\n", prf(root, str, 0));
            break;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
