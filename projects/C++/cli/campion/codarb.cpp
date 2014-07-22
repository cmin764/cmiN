#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
using namespace std;


struct Node {
    char val;
    Node* left;
    Node* right;
    Node()
    {
        val = 0;
        left = right = NULL;
    }
};


Node* root;
deque<char> seq;


bool in(char chr, const string& str)
{
    if (str.find(chr) == string::npos) return false;
    return true;
}


void rsd(Node*& pnt)
{
    pnt = new Node;
    pnt->val = seq.front();
    seq.pop_front();
    if (in(pnt->val, "BFJ")) { // go left
        rsd(pnt->left);
    } else if (in(pnt->val, "CGK")) { // or right
        rsd(pnt->right);
    } else if (in(pnt->val, "DHL")) { // or both
        rsd(pnt->left);
        rsd(pnt->right);
    }
}


Node* srd(Node* pnt)
{
    // ret=right and pnt=left
    Node* tmp = new Node;
    tmp->left = pnt;
    tmp->val = seq.front(); seq.pop_front();
    if (in(tmp->val, "CGKDHL")) tmp->right = srd(NULL); // have right son
    if (in(tmp->val, "EFGH")) return srd(tmp); // is left son
    else return tmp; // right son or root
}


Node* sdr(Node* pnt)
{
    if (seq.empty()) return pnt; // main root
    char val = seq.front(); seq.pop_front();
    Node* tmp = new Node;
    if (in(val, "BFJ")) {
        tmp->left = pnt;
        tmp->val = val;
        return sdr(tmp);
    } else if (in(val, "CGKDHL")) {
        while(in(val, "CGK")) {
            tmp->val = val;
            tmp->right = pnt;
            pnt = tmp;
            val = seq.front(); seq.pop_front();
        }
        seq.push_front(val);
        return pnt;
    } else {
        if (pnt != NULL) {
            tmp->left = pnt;
            seq.push_front(val);
            tmp->right = sdr(NULL);
            val = seq.front(); seq.pop_front();
            tmp->val = val;
            return sdr(tmp);
        }
        if (in(val, "IJKL")) {
            tmp->val = val;
            val = seq.front(); seq.pop_front();
            while (in(val, "CGK")) {
                Node* aux = new Node;
                aux->val = val;
                aux->right = tmp;
                tmp = aux;
                val = seq.front(); seq.pop_front();
            }
            seq.push_front(val);
            return tmp;
        } else {
            tmp->val = val;
            return sdr(tmp);
        }
    }
}


void show_rsd(Node* x)
{
    if (x == NULL) return;
    cout << x->val;
    show_rsd(x->left);
    show_rsd(x->right);
}


void show_srd(Node* x)
{
    if (x == NULL) return;
    show_srd(x->left);
    cout << x->val;
    show_srd(x->right);
}


void show_sdr(Node* x)
{
    if (x == NULL) return;
    show_sdr(x->left);
    show_sdr(x->right);
    cout << x->val;
}


int main()
{
    freopen("codarb.in", "r", stdin);
    freopen("codarb.out", "w", stdout);
    char buf[4];
    cin.get(buf, 4);
    string head(buf), rest;
    cin >> rest;
    for (int i = 0; i < rest.size(); ++i) seq.push_back(rest[i]);
    if (!head.compare("RSD")) rsd(root);
    else if (!head.compare("SRD")) root = srd(NULL);
    else if (!head.compare("SDR")) root = sdr(NULL);
    else cerr << "Invalid header.\n";
    cout << "RSD";
    show_rsd(root);
    cout << "\nSRD";
    show_srd(root);
    cout << "\nSDR";
    show_sdr(root);
    cout << endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
