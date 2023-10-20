#ifndef ASD1_LABS_2020_LSITERATOR_H
#define ASD1_LABS_2020_LSITERATOR_H

#include <iterator>

template <typename T> class ListeSimple;

template<typename T>
class LSConstIterator;

template<typename T>
class LSIterator
        : public std::iterator <std::forward_iterator_tag,T>
{
    friend class ListeSimple<T>;
    using Maillon = typename ListeSimple<T>::Maillon;

    friend class LSConstIterator<T>;

    Maillon* m;
    LSIterator(Maillon* _m) : m(_m) {}

public:
    LSIterator()
            : m(nullptr) {}

    LSIterator& operator++ () {
        m = m->suivant;
        return *this;
    }

    LSIterator operator++ (int) {
        auto tmp{*this};
        operator++();
        return tmp;
    }

    bool operator==(const LSIterator& i) {
        return m == i.m;
    }

    bool operator!=(const LSIterator& i) {
        return m != i.m;
    }

    T & operator*() {
        return m->valeur;
    }
};

template<typename T>
class LSConstIterator
        : public std::iterator<std::forward_iterator_tag,T>
{
    friend class ListeSimple<T>;
    using Maillon = typename ListeSimple<T>::Maillon;

    Maillon const * m;
    LSConstIterator(Maillon const * _m) : m(_m) {}

public:
    LSConstIterator()
            : m(nullptr) { }

    LSConstIterator(const LSIterator<T>& i)
            : m(i.m) { }

    LSConstIterator& operator++ () {
        m = m->suivant;
        return *this;
    }

    LSConstIterator operator++ (int) {
        auto tmp{*this};
        operator++();
        return tmp;
    }

    LSConstIterator& operator=(const LSIterator<T>& i) {
        m = i.m;
        return *this;
    }

    bool operator==(const LSConstIterator& i) {
        return m == i.m;
    }

    bool operator!=(const LSConstIterator& i) {
        return m != i.m;
    }

    T const & operator*() {
        return m->valeur;
    }
};

#endif //ASD1_LABS_2020_LSITERATOR_H
