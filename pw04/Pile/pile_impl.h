#ifndef PILE_IMPL_H
#define PILE_IMPL_H

#include <stdexcept> // std::out_of_range
#include "pile.h"

// AJOUTEZ VOTRE CODE ICI ...

// ----------------------------------------------------------------------------
// CONSTRUCTORS
template<typename T>
Pile<T>::Pile(size_t n) : capacite(n), taille(0) {
    data = (T *) ::operator new(n * sizeof(T));
}

template<typename T>
Pile<T>::Pile(const Pile<T> &other): capacite(other.capacite), taille(other.taille) {
    data = (T *) ::operator new(other.capacite * sizeof(T));
    for (size_t i = 0; i < other.taille; ++i) {
        new(&data[i]) T{other.data[i]};
    }
}

// ----------------------------------------------------------------------------
// DESTRUCTOR
template<typename T>
Pile<T>::~Pile<T>() {
    for (size_t i = 0; i < taille; ++i) {
        data[i].~T();
    }

    ::operator delete(data);
}

// ----------------------------------------------------------------------------
// OPERATORS
template<typename T>
Pile<T> &Pile<T>::operator=(const Pile<T> &other) {
    if (this == &other) {
        return *this;
    }

    if (other.taille > capacite) {
        Pile<T> tmp{other};
        swap(tmp);
        return *this;
    }

    // assign existing data with new data, deleting stale data if needed
    for (size_t i = 0; i < taille; ++i) {
        if (i >= other.taille) {
            data[i].~T();
            continue;
        }

        if (&data[i] != &other.data[i]) {
            data[i] = other.data[i];
        }
    }

    // copy new data into uninitialised data
    for (size_t i = taille; i < other.taille; ++i) {
        new(&data[i]) T{other.data[i]};
    }

    taille = other.taille;
    return *this;
}

// ----------------------------------------------------------------------------
// MEMBER FUNCTIONS
template<typename T>
void Pile<T>::push(T e) {
    if (full()) {
        throw std::out_of_range("push");
    }

    new(&data[taille]) T{std::move(e)};
    ++taille;
}

template<typename T>
void Pile<T>::pop() {
    if (empty()) {
        throw std::out_of_range("pop");
    }

    data[--taille].~T();
}

template<typename T>
const T &Pile<T>::top() const {
    if (empty()) {
        throw std::out_of_range("top");
    }

    return data[taille - 1];
}

template<typename T>
bool Pile<T>::empty() const noexcept {
    return !taille;
}

template<typename T>
bool Pile<T>::full() const noexcept {
    return taille == capacite;
}

template<typename T>
void Pile<T>::swap(Pile &other) noexcept {
    using std::swap;
    swap(capacite, other.capacite);
    swap(taille, other.taille);
    swap(data, other.data);
}

// ... FIN DE VOTRE CODE

#endif
