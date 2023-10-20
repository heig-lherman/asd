#ifndef C_H
#define C_H

#include <string>
#include <ostream>

class C {
    int _i;
    friend std::ostream& operator<< (std::ostream& s, const C& c);
public:
    C(int i) ;
    C(const C& c) ;
    C(C&& c) noexcept;
    C& operator= (const C& other) ;
    C& operator= (C&& other) noexcept;
    ~C();
};

std::ostream& operator<< (std::ostream& s, const C& c);

#endif //C_H
