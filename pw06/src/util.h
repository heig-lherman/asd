#ifndef ASD1_LABS_2020_UTIL_H
#define ASD1_LABS_2020_UTIL_H

#include <ostream>

class C {
    friend std::ostream& operator<<(std::ostream& s, const C& v);
    int _i;
public:
    C(int i = -42);
    C(const C& c);
    C& operator= (const C& other) noexcept;
    ~C();
    bool operator==(const C& other) const noexcept;
    int operator%(int m) const noexcept;
    bool operator<(const C& other) const noexcept;
    bool operator>(const C& other) const noexcept;
    bool operator<=(const C& other) const noexcept;
    bool operator>=(const C& other) const noexcept;
};

std::ostream& operator<<(std::ostream& s, const C& v);

#endif //ASD1_LABS_2020_UTIL_H
