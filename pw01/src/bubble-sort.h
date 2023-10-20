/* -----------------------------------------------------------------------------------
 * File name     : bubble-sort.h
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Tri par bulle avec données en vecteurs
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_BUBBLE_SORT_H
#define ASD2022_L1_COMPLEXITE_BUBBLE_SORT_H

#include <vector>

/**
 * Sort a vector using the bubble sort algorithm
 * @tparam T type of data of the vector
 * @param source a reference to the vector to sort
 */
template<typename T>
void bubbleSort(std::vector<T> &source) {
    bool terminate = false;
    size_t i = source.size();
    while (!terminate) {
        terminate = true;
        for (size_t j = 1; j < i; j++) {
            if (source[j] < source[j - 1]) {
                std::swap(source[j], source[j - 1]);
                terminate = false;
            }
        }
        i--;
    }
}

#endif //ASD2022_L1_COMPLEXITE_BUBBLE_SORT_H
