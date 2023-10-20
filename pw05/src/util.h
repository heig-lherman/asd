#ifndef ASD1_LABS_2020_UTIL_H
#define ASD1_LABS_2020_UTIL_H

#include <ostream>

class C {
    friend std::ostream& operator<<(std::ostream& s, const C& v);
    int valeur;
    bool explosif;
public:
    C(int i);
    C(const C& c);
    C& operator= (const C& other);
    ~C();
    void rendExplosif();
};

std::ostream& operator<<(std::ostream& s, const C& v);

#endif //ASD1_LABS_2020_UTIL_H
