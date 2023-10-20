/* -----------------------------------------------------------------------------------
 * File name     : OpCounterImpl.h
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Implémentations diverses de la classe OpCounter
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_OPCOUNTERIMPL_H
#define ASD2022_L1_COMPLEXITE_OPCOUNTERIMPL_H

template<typename T>
OpCounter<T>::OpCounter(const OpCounter<T> &rhs) {
    OpCounter<T>::copyCounter++;
    value = rhs.value;
}

template<typename T>
OpCounter<T> &OpCounter<T>::operator=(const OpCounter<T> &rhs) {
    OpCounter<T>::copyCounter++;
    value = rhs.value;
    return *this;
}

template<typename T>
OpCounter<T> &OpCounter<T>::operator=(T val) {
    value = val;
    return *this;
}

template<typename T>
bool OpCounter<T>::operator==(const OpCounter<T> &rhs) const {
    OpCounter<T>::comparisonCounter++;
    return value == rhs.value;
}

template<typename T>
bool OpCounter<T>::operator<(const OpCounter<T> &rhs) const {
    OpCounter<T>::comparisonCounter++;
    return value < rhs.value;
}

template<typename T>
void OpCounter<T>::resetCounters() {
    OpCounter::comparisonCounter = 0;
    OpCounter::copyCounter = 0;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const OpCounter<T> &rhs) {
    os << rhs.value;
    return os;
}

#endif //ASD2022_L1_COMPLEXITE_OPCOUNTERIMPL_H
