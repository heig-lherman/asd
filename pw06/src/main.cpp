//IN 0
//IN 1

#include <iostream> 
using std::cout;
using std::endl;

#include <iterator> 
using std::next; 

#include "ListeSimple.h"
#include "util.h"

template < typename input_iterator >
void display(input_iterator first, input_iterator last) {
    for(; first != last; ++first) {
        cout << *first << " ";
    }
    cout << "\n";
}

template <typename T>
void cc(ListeSimple<T>& ls) {

    cout << "\nRemplissage avec push_front() \n";
    for(int i : { 1, 1, 5, 2, 4, 2, 0, 2, 5, 1, 2 } )
        ls.push_front(i);
    cout << "\n";
    display(ls.cbegin(),ls.cend());

    cout << "Elément en tête : ";
    cout << ls.front() << endl;

    auto const& lsc = ls;
    cout << "Elément en tête (const): ";
    cout << lsc.front() << endl;

    cout << "Parcours const: " << endl;
    for(typename ListeSimple<T>::const_iterator i = lsc.begin(); i != lsc.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    cout << "Construction par copie \n";
    ListeSimple<T> l2{ls};
    cout << "\n";
    display(l2.cbegin(),l2.cend());

    cout << "Remplissage avec insert_after() à la fin \n";
    ListeSimple<T> l3;
    auto before_end = l3.before_begin();
    for(auto i : { 2, 5, 7, 3, 1, 0 }) {
        l3.insert_after(before_end,i);
        ++before_end;
    }
    cout << "\n";
    display(l3.cbegin(),l3.cend());

    cout << "auto-affectation\n";
    l3 = l3; //
    cout << "\n";
    display(l3.cbegin(),l3.cend());

    cout << "affectation\n";
    l3 = ls;
    cout << "\n";
    display(l3.cbegin(),l3.cend());

    cout << "push_front() après copie\n";
    for(auto i : { 4, 2, 1, 6, 3, 5 })
        ls.push_front(i);
    cout << "\n";
    cout << "l3 : "; display(l3.cbegin(),l3.cend());
    cout << "ls : "; display(ls.cbegin(),ls.cend());

    cout << "Nouvelle liste l4 \n";
    ListeSimple<T> l4;
    for(auto i : { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 })
        l4.push_front(i);
    cout << "\n";
    display(l4.cbegin(),l4.cend());

    cout << "splice les 4ème à 6émes éléments derrière le premier \n";
    l4.splice_after(next(l4.before_begin(),1),
            next(l4.before_begin(),3),
            next(l4.before_begin(),6));
    cout << "\n";
    display(l4.cbegin(),l4.cend());

    cout << "splice le 5ème élément devant le premier \n";
    l4.splice_after(l4.before_begin(),
                    next(l4.before_begin(),4),
                    next(l4.before_begin(),5));
    cout << "\n";
    display(l4.cbegin(),l4.cend());

    cout << "splice les 3 derniers éléments après le 2ème. \n";
    l4.splice_after(next(l4.before_begin(),2),
                    next(l4.before_begin(),7),
                    next(l4.before_begin(),10));
    cout << "\n";
    display(l4.cbegin(),l4.cend());

    cout << "splice les 4ème à 7ème éléments de l4 vers l5 \n";
    ListeSimple<T> l5;
    l5.splice_after(l5.before_begin(),
                    next(l4.before_begin(),3),
                    next(l4.before_begin(),7));
    cout << "\n";
    cout << "l4: "; display(l4.cbegin(),l4.cend());
    cout << "l5: "; display(l5.cbegin(),l5.cend());

    cout << "Tri des 2 listes \n";
    l4.sort();
    cout << "l4: "; display(l4.cbegin(),l4.cend());
    l5.sort();
    cout << "l5: "; display(l5.cbegin(),l5.cend());

    cout << "\n";
}

int main() {

    cout << "Tapez 0 pour tester avec des entiers, 1 pour le faire avec des objets mouchards : ";

    int i;
    std::cin >> i;

    switch(i) {
        case 0: {
            ListeSimple<int> L;
            cc(L);
            break;
        }
        case 1: {
            ListeSimple<C> L;
            cc(L);
            break;
        }
        default:
            cout << "Unknown CC test\n";
    }
}