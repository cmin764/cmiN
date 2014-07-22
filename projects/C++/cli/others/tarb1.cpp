#include <iostream>
using namespace std;

struct Node {
    short int key;
    Node* lt, * rt;
    Node()
    {
        key = 0;
        lt = rt = 0;
    }
};
typedef Node* arb;

void create(arb pObj)
{
    bool ans;
    cout << "Nod " << pObj->key << " are fiu stang (1/0)? ";
    cin >> ans;
    if (ans) {
        pObj->lt = new Node;
        cout << "Cheie: ";
        cin >> pObj->lt->key;
        create(pObj->lt);
    }
    cout << "Nod " << pObj->key << " are fiu drept (1/0)? ";
    cin >> ans;
    if (ans) {
        pObj->rt = new Node;
        cout << "Cheie: ";
        cin >> pObj->rt->key;
        create(pObj->rt);
    }
}

void search(arb root, short int value)
{
    arb temp = root;
    while (temp) {
        if (temp->key == value) {
            cout << "Valoare gasita.\n";
            return;
        } else if (temp->key < value) {
            temp = temp->rt;
        } else {
            temp = temp->lt;
        }
    }
    cout << "Valoare negasita.\n";
}

int main()
{
    short int cheie;
    arb root = new Node;
    cout << "Cheie radacina: ";
    cin >> root->key;
    create(root);
    do {
        cout << "Cheia cautata (0 pentru oprire): ";
        cin >> cheie;
        search(root, cheie);
    } while(cheie);
    return 0;
}
