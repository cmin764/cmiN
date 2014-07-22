#include <iostream>
#include <fstream>
#include <vector>

#include "shape.hpp"
#include "cerc.hpp"
#include "triunghi.hpp"
#include "dreptunghi.hpp"
#include "grup.hpp"
#include "shapefactory.hpp"
#include "patrat.hpp"


using namespace std;


vector<Shape<> *> shapes;


void createSampleShapeVector()
{
    cout << "Shapes created:" << endl;
    Triunghi<> *t1 = new Triunghi<>(Punct<>(10, 10), Punct<>(20, 20), Punct<>(10, 20));
    Triunghi<> *t2 = new Triunghi<>(Punct<>(15, 15), Punct<>(35, 35), Punct<>(35, 15));
    Shape<> &s1(*t1);
    Shape<> &s2(*t2);
    cout << s1 << endl;
    t1->moveBy(6, 7);
    cout << s1 << endl;
    s1.moveBy(1, 0);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << endl;
    Dreptunghi<> *d1 = new Dreptunghi<>(Punct<>(15, 15), Punct<>(35, 35));
    Shape<> &s3(*d1);
    cout << s3 << endl;
    d1->moveBy(5, 5);
    cout << s3 << endl;
    s3.moveBy(-10, -10);
    cout << *d1 << endl;
    cout << endl;
    Cerc<> *c1 = new Cerc<>(Punct<>(5, 5), 10);
    Shape<> &s4(*c1);
    cout << s4 << endl;
    c1->moveBy(5, 5);
    cout << s4 << endl;
    s4.moveBy(-10, -10);
    cout << *c1 << endl;
    cout << endl;
    Grup<> *g1 = new Grup<>();
    Shape<> &s5(*g1);
    g1->add(&s1);
    g1->add(&s2);
    g1->add(&s3);
    g1->add(&s4);
    cout << s5 << endl;
    s1.moveBy(100, 100);
    cout << s5 << endl;
    cout << endl;
    Grup<> *g2 = new Grup<>();
    g2->add(g1);
    g2->add(new Cerc<>(Punct<>(3, 4), 5));
    cout << *g2 << endl;
    Patrat<> * p1 = new Patrat<>(Punct<>(2, 2), Punct<>(10, 10));
    shapes.push_back(t1);
    shapes.push_back(t2);
    shapes.push_back(c1);
    shapes.push_back(d1);
    shapes.push_back(g1);
    shapes.push_back(g2);
    shapes.push_back(p1);
}


int main()
{
    createSampleShapeVector();
    cout << endl << endl << "Writing shapes to file" << endl;
    ofstream fout("shapes.txt");
    fout << shapes.size() << endl;

    for (int i = 0; i < (int)shapes.size(); ++i)
        shapes[i]->output(fout);
    fout.close();

    cout << endl << endl << "Reading shapes from file" << endl;
    vector<Shape<> *> shapesRead;
    ifstream fin("shapes.txt");
    int n;
    fin >> n;
    ShapeFactory<> * factory = ShapeFactory<>::get_instance();
    factory->register_function("patrat", Patrat<>::create);
    for (int i = 0; i < n; ++i) {
        Shape<> * s = factory->create_shape(fin);
        s->readFrom(fin);
        shapesRead.push_back(s);
    }

    fin.close();
    cout << endl << endl << "Shapes read from file:" << endl;
    for (int i = 0; i < (int)shapesRead.size(); ++i) {
        cout << *shapesRead[i] << endl;
    }
    cout << endl;
    return 0;
}
