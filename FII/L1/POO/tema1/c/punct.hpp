#ifndef PUNCT_HPP_INCLUDED
#define PUNCT_HPP_INCLUDED


#include <iostream>
#include <utility>


using namespace std;


class Punct {

    int x, y;

public:

    typedef pair<Punct, Punct> corners_t;

    static const Punct Origine;
    static const Punct UnuZero;
    static const Punct ZeroUnu;

    Punct(int=0, int=0);
    ~Punct();

    int GetX() const;
    int GetY() const;

    void MutaX(int=1);
    void MutaY(int=1);
    void MutaXY(int=1, int=1);

    bool equals(const Punct&) const;
    bool is_origin() const;
    void swaps(Punct&);
    double dist(const Punct&) const;
    static corners_t rectangle(const Punct&, const Punct&);
};


ostream& operator<<(ostream&, const Punct&);
istream& operator>>(istream&, Punct&);

bool operator==(const Punct&, const Punct&);
bool operator!=(const Punct&, const Punct&);


#endif // PUNCT_HPP_INCLUDED
