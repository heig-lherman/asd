/* -----------------------------------------------------------------------------------
 * File name     : tri_par_base.h
 * Authors       : [redacted]
 * Creation date : 25.03.2022
 *
 * Description   : Implémentation du tri par base et du tri comptage
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */
#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <algorithm>
#include <iterator>
#include <vector>

#include "some_bits.h"

/**
 * Sort a given input range using the counting sort algorithm.
 * @tparam Iterator Iterator type of the input range.
 * @tparam Fn Function type to compare two elements.
 * @param first First element of the input range.
 * @param last Last element of the input range.
 * @param output_first First element of the output range.
 * @param index_fn Function to get the index of an element.
 * @param N Number of different categories
 */
template<typename Iterator, typename Fn>
void tri_comptage(Iterator first, Iterator last, Iterator output_first, Fn index_fn, size_t N) {
    // T will be the type of the elements of the input sequence
    using T = typename Iterator::value_type;

    // Create the temporary count vector
    std::vector<unsigned long long> counters(N, 0);
    std::for_each(first, last, [&](const T &x) { ++counters[index_fn(x)]; });

    // Recreate count tab to set indexes rather than count
    size_t idx = 0;
    for (size_t i = 0; i < N; ++i) {
        size_t tmp = counters[i];
        counters[i] = (T) idx;
        idx += tmp;
    }

    // Build the output vector
    for (auto it = first; it != last; ++it) {
        auto &count = counters[index_fn(*it)];
        *std::next(output_first, (long long) count) = *it;
        ++count;
    }
}

/**
 * Sort a given input range using the radis sort algorithm.
 * @tparam Iterator Iterator type of the input range.
 * @tparam NBITS Number of bits used to represent the categories.
 * @param first First element of the input range.
 * @param last Last element of the input range.
 */
template<typename Iterator, size_t NBITS>
void tri_par_base(Iterator first, Iterator last) {
    using T = typename Iterator::value_type;
    static_assert(std::is_unsigned<T>::value);

    // Get the size of vector, assumed last > first
    auto size = (size_t) std::distance(first, last);
    // Temporary vector for countsort
    std::vector<T> countsortOutput(size, 0);
    // Max value from the vector to sort
    T maxValue = *std::max_element(first, last);

    size_t pos = 0;
    // number of categories for countsort
    const T keyNumber = maxValue + 1;

    // Apply the counting sort
    while (maxValue) {
        auto fn = SomeBits<unsigned long long>(NBITS, pos++);
        maxValue >>= NBITS;
        tri_comptage<>(first, last, countsortOutput.begin(), fn, keyNumber);
        std::swap_ranges(first, last, countsortOutput.begin());
    }
}

#endif