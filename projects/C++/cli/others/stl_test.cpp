#include <iostream>
#include <vector>

using namespace std;

template<class T> class MyList: public vector<T> {
private:
    typename MyList<T>::iterator it;
public:
    void append(const T& obj)
    {
        this->push_back(obj);
    }
    unsigned int count(const T& obj)
    {
        unsigned int cnt = 0;
        for (it = this->begin(); it != this->end(); ++it) {
            if (*it == obj) {
                cnt++;
            }
        }
        return cnt;
    }
    void remove(const T& obj)
    {
        for (it = this->begin(); it != this->end(); ++it) {
            if (*it == obj) {
                this->erase(it);
                break;
            }
        }
    }
    void inser(unsigned int poz, const T& obj)
    {
        it = this->begin() + poz;
        this->insert(it, obj);
    }
    T pop()
    {
        T temp = this->back();
        this->erase(this->end() - 1);
        return temp;
    }
};

int main()
{
    MyList<int> list;
    for (int i = 1; i < 10; i++) {
        list.append(i % 3);
    }
    list.inser(0, 3);
    cout << list.size() << " " << list.count(3) << endl;
    while (list.count(0) - 1) {
        list.remove(0);
    }
    cout << list.size() << endl;
    int x = list.pop();
    for (unsigned int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << x << endl;
    return 0;
}
