/* -----------------------------------------------------------------------------------
 * File name     : tri_rapide.h
 * Authors       : [redacted]
 * Creation date : 25.03.2022
 *
 * Description   : Implémentation du tri rapide avec la gestion des partitions
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */
#ifndef TRI_RAPIDE
#define TRI_RAPIDE

#include <random>

extern const unsigned SEED;

/**
 * Returns the iterator at the position after the partition for quick sort.
 * It is supposed that the last element of the range is the pivot placed in the previous step.
 * @tparam Iterator the type of the iterator
 * @param first the iterator to the first element of the range
 * @param last the iterator to the last element of the range, assumed to be the pivot
 * @return the iterator at the position after the partition for quick sort
 */
template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
    Iterator i = std::prev(first);
    Iterator j = last;
    while (true) {
        do {
            std::advance(i, 1);
        } while (*i < *last);

        do {
            std::advance(j, -1);
        } while (j > first && *last < *j);

        if (i >= j) {
            break;
        }

        std::iter_swap(i, j);
    }

    std::iter_swap(i, last);
    return i;
}

/**
 * Chooses how to recurse and randomly chooses the pivot.
 * Should use the semi-recursive method, where the second partition is handled iteratively.
 * @tparam Iterator the type of the iterator
 * @param first the iterator to the first element of the range
 * @param last the iterator to the container end
 */
template<typename Iterator>
void tri_rapide(Iterator first, Iterator last) {
    // Shortcut when the range is empty or has only one element
    if (std::distance(first, last) <= 0) {
        return;
    }

    // Seed a new random generator to provide consistent results
    std::default_random_engine seededRandom(SEED);
    while (first < last) {
        // Randomly choose the pivot, and move it to the end
        Iterator pivot = std::next(first, ((long long) seededRandom()) % std::distance(first, last));
        std::iter_swap(std::prev(last), pivot);
        // Partition expects the pivot to be given as the last iterator
        Iterator i = partition(first, std::prev(last));

        if (std::distance(first, i) < std::distance(i, last)) {
            tri_rapide(first, i);
            first = std::next(i);
            continue;
        }

        tri_rapide(std::next(i), last);
        last = i;
    }
}

#endif