/* -----------------------------------------------------------------------------------
 * File name     : insertion-sort.h
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Tri par insertion avec données en vecteurs
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_INSERTION_SORT_H
#define ASD2022_L1_COMPLEXITE_INSERTION_SORT_H

#include <vector>

/**
 * Sort a vector using the insertion sort algorithm
 * @tparam T type of data of the vector
 * @param source a reference to the vector to sort
 */
template<typename T>
void insertionSort(std::vector<T> &source) {
    for (size_t i = 1; i < source.size(); i++) {
        for (size_t j = i; (j > 0) && (source[j - 1] > source[j]); j--) {
            std::swap(source[j - 1], source[j]);
        }
    }
}

#endif //ASD2022_L1_COMPLEXITE_INSERTION_SORT_H
