#include <iostream>
#include <stdexcept>

#include "pile.h"
#include "c.h"

using namespace std;

template <typename T>
void videLaPile(Pile<T>& p) {
    while(not p.empty()) {
        std::cout << p.top();
        p.pop();
    }
}

int main() {

    using T = C;

    cout << "** Pile<T> p1(10) + push(5,6,7) **" << endl;
    Pile<T> p1(10);

    p1.push(5);
    p1.push(6);
    p1.push(7);

    cout << endl << "** Pile<T> p2{p1} **" << endl;
    Pile<T> p2{p1};

    cout << endl << "** videLaPile(p2) **" << endl;
    videLaPile(p2);

    cout << endl << "** Pile<T> p3(5) + push(1) **" << endl;
    Pile<T> p3(5);
    p3.push(1);
    cout << endl << "** p3 = p1 "" " << endl;
    p3 = p1;
    cout << endl << "** videLaPile(p3) **" << endl;
    videLaPile(p3);

    cout << endl << "** Pile<T> p4(7) + push(2,0,2,0) **" << endl;
    Pile<T> p4(7);
    for(int e : { 2, 0, 2, 0})
        p4.push(e);

    cout << endl << "** p4 = p1 **" << endl;
    p4 = p1;

    cout << endl << "** videLaPile(p4) **" << endl;
    videLaPile(p4);

    cout << endl << "** Pile<T> p5(2) + push(1) **" << endl;
    Pile<T> p5(2);
    p5.push(1);

    cout << endl << "** p5 = p1  **" << endl;
    p5 = p1;

    cout << endl << "** videLaPile(p5) **" << endl;
    videLaPile(p5);

    cout << endl << "** p1 = p1 **" << endl;
    p1 = p1;

    cout << endl << "** videLaPile(p1) **" << endl;
    videLaPile(p1);

    cout << endl << "** push(++i) until full **" << endl;
    int i = 0;
    while(not p1.full())
        p1.push(++i);

    cout << endl << "** } main **" << endl;
}