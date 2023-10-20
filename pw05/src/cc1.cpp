#include <iostream>
#include <string>

#include "ArrayDeque.h"

using namespace std;



int main() {
  
    ArrayDeque<int> dq(16);
    cout << dq << endl;
    for(int i = 0; i < 5; ++i) {
        dq.push_back(i);
        cout << dq << endl;
        dq.push_front(-1-i);
        cout << dq << endl;
    }

    for(int i = 2; i < 5; ++i) {
        dq[size_t(i)] = i*i;
        cout << dq << endl;
        dq.pop_front();
        cout << dq << endl;
    }

    cout << "\nCopie par constructeur\n";
    auto dq2 = dq;
    cout << dq2 << endl;

    cout << "\nSwap \n";
    dq.push_front(42);
    dq.push_back(24);
    dq[5] = 2020;
    dq2.swap(dq);
    cout << "dq  :" << dq << endl;
    cout << "dq2 :" << dq2 << endl;

    cout << "\nCopie par affectation\n";
    ArrayDeque<int> dq3(5);
    dq3 = dq;
    cout << dq3 << endl;

    cout << "\nVidange aléatoire\n";
    while(not dq.empty()) {
        if(rand() % 2)
            dq.pop_front();
        else
            dq.pop_back();
        cout << dq << endl;
    }
}

