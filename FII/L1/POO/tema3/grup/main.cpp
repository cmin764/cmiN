#include <iostream>

#include "grup.hpp"
#include "cerc.hpp"
#include "punct.hpp"


using namespace std;


int main()
{
    Grup grup;
    Cerc cerc1(Punct(1, 2), 2), cerc2(Punct(3, 0), 4);

    grup.add(&cerc1);
    grup.add(&cerc2);
    cout << grup;
    grup.remove(&cerc1);
    cout << "After delete" << endl;
    cout << grup;

    Grup grup2;
    grup2.add(&cerc2);

    cout << (grup == grup2) << endl;

    return 0;
}
