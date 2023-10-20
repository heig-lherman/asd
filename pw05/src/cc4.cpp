#include <iostream>
#include <string>

#include "ArrayDeque.h"
#include "util.h"

using namespace std;

int main() {

    ArrayDeque<C> dq(0);
    cout << dq << endl;
    for(int i = 0; i < 5; ++i) {
        dq.push_back(i);
        cout << endl << dq << endl;
        dq.push_front(-1-i);
        cout << endl << dq << endl;
    }

    for(int i = 2; i < 5; ++i) {
        dq[size_t(i)] = i*i;
        cout << endl << dq << endl;
        dq.pop_front();
        cout << endl << dq << endl;
    }

    cout << "\nCopie par constructeur\n";
    auto dq2 = dq;
    cout << endl << dq2 << endl;

    cout << "\nAjout et modification \n";
    dq.push_front(42);
    dq.push_back(24);
    dq[5] = 2020;

    cout << "\n\nSwap";
    dq2.swap(dq);
    cout << endl << "dq  :" << dq << endl;
    cout << "dq2 :" << dq2 << endl;

    cout << "\nCopie par affectation\n";
    ArrayDeque<C> dq3(5);
    dq3 = dq;
    cout << endl << dq3 << endl;

    cout << "\nVidange aléatoire\n";
    while(not dq.empty()) {
        if(rand() % 2)
            dq.pop_front();
        else
            dq.pop_back();
        cout << endl << dq << endl;
    }

    cout << "\nShrink\n";
    dq2.shrink_to_fit();
    cout << endl << dq2 << endl;

    cout << "\npush_front garantie forte 1\n";
    cout << dq3 << endl;
    try {
        C c(7);
        c.rendExplosif();
        dq3.push_front(c);
    } catch (...) {
        cout << "\nExplosion contenue\n";
    }
    cout << dq3 << endl;

    cout << "\npush_front garantie forte 2\n";
    cout << dq2 << endl;
    try {
        dq2[3].rendExplosif();
        dq2.push_front(3);
    } catch (...) {
        cout << "\nExplosion contenue\n";
    }
    cout << dq2 << endl;

    cout << "\npush_back garantie forte 1\n";
    cout << dq3 << endl;
    try {
        C c(7);
        c.rendExplosif();
        dq3.push_back(c);
    } catch (...) {
        cout << "\nExplosion contenue\n";
    }
    cout << dq3 << endl;

    cout << "\npush_back garantie forte 2\n";
    cout << dq2 << endl;
    try {
        dq2[3].rendExplosif();
        dq2.push_back(3);
    } catch (...) {
        cout << "\nExplosion contenue\n";
    }
    cout << dq2 << endl;


    cout << "\naffectation garantie fort\n";
    cout << dq3 << endl;
    try {
        dq3 = dq2;
    } catch(...) {
        cout << "\nExplosion contenue\n";
    }
    cout << dq3 << endl;

    cout << "\nConstructeur de copie garantie de base\n";
    try {
        auto dq4 = dq2;
    } catch(...) {
        cout << "\nExplosion contenue\n";
    }

    cout << "\nFin\n";
}

