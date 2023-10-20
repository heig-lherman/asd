#ifndef PILE_H
#define PILE_H

#include <cstdlib> // size_t

template <typename T>
class Pile {
    size_t taille;
    size_t capacite;
    T* data;
public:
    Pile(size_t n);
    ~Pile();

    void push(T e);
    void pop();
    const T& top() const;
    bool empty() const noexcept;
    bool full() const noexcept;

    Pile(const Pile& other);
    void swap(Pile& other) noexcept;
    Pile& operator= ( const Pile& other );
};

#include "pile_impl.h"

#endif //ASD1_LABS_2020_PILE_H
