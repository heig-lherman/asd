/* -----------------------------------------------------------------------------------
 * File name     : OpCounter.h
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Définition de la classe OpCounter pour compter les opérations
 *                 effectuées sur le type T.
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_OPCOUNTER_H
#define ASD2022_L1_COMPLEXITE_OPCOUNTER_H

#include <ostream>
#include <type_traits>

template<typename T> class OpCounter;
template<typename T> std::ostream &operator<<(std::ostream &os, const OpCounter<T> &rhs);

/**
 * Class that counts the operations applied to its internal value.
 * @tparam T Internal value type
 */
template<typename T>
class OpCounter {
    static_assert(std::is_integral<T>::value, "Only integral type can be used with this class");

public:
    explicit OpCounter(T value = 0) : value(value) {}
    OpCounter(const OpCounter<T> &rhs);

    OpCounter<T> &operator=(const OpCounter<T> &rhs);
    OpCounter<T> &operator=(T val);

    bool operator==(const OpCounter<T> &rhs) const;
    inline bool operator!=(const OpCounter<T> &rhs) const { return !(operator==(rhs)); }

    bool operator<(const OpCounter<T> &rhs) const;
    inline bool operator>(const OpCounter<T> &rhs) const { return rhs < *this; }
    inline bool operator<=(const OpCounter<T> &rhs) const { return !(operator>(rhs)); }
    inline bool operator>=(const OpCounter<T> &rhs) const { return !(operator<(rhs)); }

    friend std::ostream &operator<< <>(std::ostream &os, const OpCounter<T> &frac);

    /** Reset the counters held by this class */
    static void resetCounters();
    /** Get the copy operation counter */
    static unsigned long getCopyCounter() { return copyCounter; }
    /** Get the comparison operation counter */
    static unsigned long getComparisonCounter() { return comparisonCounter; }

private:
    T value;
    inline static unsigned long comparisonCounter = 0, copyCounter = 0;
};

#include "OpCounterImpl.h"

#endif //ASD2022_L1_COMPLEXITE_OPCOUNTER_H
