#ifndef LISTE_H
#define LISTE_H

#include "LSIterator.h"
#include <utility> // std::swap;

template<typename T>
class ListeSimple {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;
    using iterator = LSIterator<value_type>;
    using const_iterator = LSConstIterator<value_type>;

    friend iterator;
    friend const_iterator;

private:
    struct Maillon {
        value_type valeur;
        Maillon *suivant;
    };

    Maillon beforeFirst;

public:
    ListeSimple() : beforeFirst{value_type{}, nullptr} {
    }

    ListeSimple(const ListeSimple<value_type> &ls) : beforeFirst{value_type{}, nullptr} {
        try {
            iterator last = before_begin();
            for (auto it = ls.begin(); it != ls.end(); ++it) {
                last = insert_after(last, *it);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    ListeSimple(const ListeSimple<value_type> &&other) noexcept: beforeFirst(other.beforeFirst) {
        other.beforeFirst = {value_type{}, nullptr};
    }

    /* ------------------------------------------------------------
    * Destructor
     * ------------------------------------------------------------ */

    ~ListeSimple() {
        clear();
    }

    /* ------------------------------------------------------------
     * Operators
     * ------------------------------------------------------------ */

    ListeSimple<value_type> &operator=(const ListeSimple<value_type> &rhs) {
        if (this == &rhs) {
            return *this;
        }

        ListeSimple<value_type> tmp{rhs};
        swap(tmp);
        return *this;
    }

    ListeSimple<value_type> &operator=(ListeSimple<value_type> &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }

        ListeSimple<value_type> tmp = std::move(rhs);
        swap(tmp);
        return *this;
    }

    /* ------------------------------------------------------------
     * Iterator definitions
     * ------------------------------------------------------------ */

    const_iterator cbegin() const noexcept { return const_iterator(beforeFirst.suivant); }
    iterator begin() noexcept { return iterator(beforeFirst.suivant); }
    const_iterator begin() const noexcept { return cbegin(); }

    const_iterator cend() const noexcept { return const_iterator(nullptr); }
    iterator end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept { return cend(); }

    const_iterator cbefore_begin() const noexcept { return const_iterator(&beforeFirst); }
    iterator before_begin() noexcept { return iterator(&beforeFirst); }
    const_iterator before_begin() const noexcept { return cbefore_begin(); }

    /* ------------------------------------------------------------
     * Positional element access
     * ------------------------------------------------------------ */

    reference front() noexcept { return beforeFirst.suivant->valeur; }
    const_reference front() const noexcept { return beforeFirst.suivant->valeur; }

    /* ------------------------------------------------------------
     * Capacity
     * ------------------------------------------------------------ */

    bool empty() const noexcept { return beforeFirst.suivant == nullptr; }

    /* ------------------------------------------------------------
     * Data insertion
     * ------------------------------------------------------------ */

    iterator insert_after(iterator position, const_reference value) {
        if (position == nullptr) {
            throw std::out_of_range("Invalid iterator");
        }

        auto *maillon = new Maillon{value, position.m->suivant};
        position.m->suivant = maillon;
        return iterator(maillon);
    }

    void push_front(const_reference value) {
        insert_after(before_begin(), value);
    }

    /* ------------------------------------------------------------
     * Data splicing
     * ------------------------------------------------------------ */

    void splice_after(iterator position, iterator first, iterator last) {
        if (position == nullptr || first == nullptr || last == nullptr) {
            throw std::out_of_range("Invalid iterator");
        }

        if (first == last) {
            return;
        }

        Maillon *tmp = last.m->suivant;
        last.m->suivant = position.m->suivant;
        position.m->suivant = first.m->suivant;
        first.m->suivant = tmp;
    }

    /* ------------------------------------------------------------
     * Data removal
     * ------------------------------------------------------------ */

    void erase_after(iterator position) {
        if (position == nullptr || !position->suivant) {
            throw std::out_of_range("Invalid iterator");
        }

        auto *maillon = position->suivant;
        position->suivant = maillon->suivant;
        delete maillon;
    }

    void pop_front() {
        erase_after(before_begin());
    }

    /* ------------------------------------------------------------
     * Data algorithms
     * ------------------------------------------------------------ */

    void sort() {
        if (empty() || beforeFirst.suivant->suivant == nullptr) {
            return;
        }

        Maillon *j = &beforeFirst;
        while (j && j->suivant) {
            Maillon *iMin = j;
            Maillon *i = j->suivant;
            while (i->suivant) {
                if (i->suivant->valeur < iMin->suivant->valeur) {
                    iMin = i;
                }

                i = i->suivant;
            }

            // swap des maillons après j et après imin using splice
            std::swap(j->suivant, iMin->suivant);
            std::swap(j->suivant->suivant, iMin->suivant->suivant);

            j = j->suivant;
        }
    }

    /* ------------------------------------------------------------
     * Utility
     * ------------------------------------------------------------ */

    void swap(ListeSimple<value_type> &other) noexcept {
        using std::swap;
        swap(beforeFirst, other.beforeFirst);
    }

    void clear() {
        Maillon *current = beforeFirst.suivant;
        while (current != nullptr) {
            Maillon *tmp = current;
            current = current->suivant;
            delete tmp;
        }
        beforeFirst.suivant = nullptr;
    }
};

#endif //LISTE_H
