#include <iostream>
using std::cout;
using std::endl;

#include "util.h"

C::C(int i) : _i(i) {
    cout << " C(" << _i << ") ";
}

C::C(const C& c) : _i(c._i) {
    cout << " CP(" << _i << ") ";
}

C& C::operator= (const C& other) noexcept {
    _i = other._i;
    cout << " =(" << _i << ") ";
    return *this;
}

C::~C() {
    cout << " D(" << _i << ") ";
}

bool C::operator==(const C& other) const noexcept {
    return other._i == _i;
}

int C::operator%(int m) const noexcept {
    return _i % m;
}

bool C::operator<(const C& other) const noexcept {
    return _i < other._i;
}

bool C::operator>(const C& other) const noexcept {
    return other < *this;
}

bool C::operator<=(const C& other) const noexcept {
    return not(other < *this);
}

bool C::operator>=(const C& other) const noexcept {
    return not(*this < other);
}

std::ostream& operator<<(std::ostream& s, const C& c) {
    s << c._i;
    return s;
}
