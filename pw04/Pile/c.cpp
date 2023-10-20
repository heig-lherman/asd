#include <iostream>
using std::cout;
using std::endl;

#include "c.h"
using std::string;

C::C(int i) : _i(i) {
    cout << "ic(" << _i << ") ";
}

C::C(const C& c) : _i(c._i) {
    cout << "cc(" << _i << ") ";
}

C::C(C&& c) noexcept : _i(c._i) {
    cout << "mc(" << _i << ") ";
    c._i = -1;
}

C& C::operator= (const C& other) {
    _i = other._i;
    cout << "ca(" << _i << ") ";
    return *this;
}

C& C::operator= (C&& other) noexcept {
    _i = other._i;
    if( &other != this )
        other._i = -2;
    cout << "ma(" << _i << ") ";
    return *this;
}

std::ostream& operator<< (std::ostream& s, const C& c)
{
    s << c._i << ' ';
    return s;
}

C::~C() {
    cout << "d(" << _i << ") ";
}