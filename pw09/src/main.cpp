#include <iostream>
#include <sstream>
#include "avlTree.h"

using namespace std;

int main() {

    avlTree<int> t;

    for (int i: {3, 5, 2, 6, 8, 4, 6, 4, 1}) {
        t.insert(i);
        t.show_indented();
        cout << endl;
    }

    cout << t << endl;
    t.erase(6);
}