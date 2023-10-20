#include <iostream>
using std::cout;
using std::endl;

#include <stdexcept>

#include "util.h"

C::C(int i) : valeur(i), explosif(false) {
    cout << " C(" << valeur << ") ";
}

C::C(const C& c) : valeur(c.valeur), explosif(c.explosif) {
    if(explosif) throw std::exception();
    cout << " CP(" << valeur << ") ";
}

C& C::operator= (const C& other) {
    if(explosif) throw std::exception();
    valeur = other.valeur;
    explosif = other.explosif;
    cout << " =(" << valeur << ") ";
    return *this;
}

void C::rendExplosif() { explosif = true; }

C::~C() {
    cout << " D(" << valeur << ") ";
}

std::ostream& operator<<(std::ostream& s, const C& c) {
    s << c.valeur;
    return s;
}
