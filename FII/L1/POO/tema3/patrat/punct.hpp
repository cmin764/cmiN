#ifndef PUNCT_H_INCLUDED
#define PUNCT_H_INCLUDED


#include <iostream>


using namespace std;


class Punct {

private:
    int x, y;

public:
    Punct(int = 0, int = 0);
    Punct(const Punct &);

    int getX() const;
    int getY() const;

    void setX(int);
    void setY(int);

    void moveBy(int, int);

    bool operator==(const Punct &) const;
    bool operator!=(const Punct &) const;

    friend istream &operator>>(istream &, Punct &);
    friend ostream &operator<<(ostream &, const Punct &);
};


#endif // PUNCT_H_INCLUDED
