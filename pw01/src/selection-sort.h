/* -----------------------------------------------------------------------------------
 * File name     : selection-sort.h
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Tri par sélection avec données en vecteurs
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_SELECTION_SORT_H
#define ASD2022_L1_COMPLEXITE_SELECTION_SORT_H

#include <algorithm>
#include <vector>

/**
 * Sort a vector using the selection sort algorithm
 * @tparam T type of data of the vector
 * @param source a reference to the vector to sort
 */
template<typename T>
void selectionSort(std::vector<T> &source) {
    for (auto it = source.begin(); it != source.end(); ++it) {
        std::swap(*it, *std::min_element(it, source.end()));
    }
}

#endif //ASD2022_L1_COMPLEXITE_SELECTION_SORT_H
