#include <iostream>
#include <string>

#include "ArrayDeque.h"
#include "util.h"

using namespace std;

int main() {

    ArrayDeque<C> dq(16);
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

    cout << "\nFin\n";
}

