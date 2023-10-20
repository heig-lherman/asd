/* --------------------------------------------------------------------------
 * File name     : main.cpp
 * Authors       : [redacted]
 * Creation date : 12.05.22
 *
 * Description   : Implémente les fonctions nearestValue, valBefore et valAfter.
 *                 Ajoute également une fonction main pour tester les fonctions.
 *
 * Compiler      : gcc version 11.3.0 (Solus)
 * -------------------------------------------------------------------------- */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

// -------------------------------------------------------------------------- //

/**
 * @brief Returns the absolute numerical difference of the two given values.
 * @tparam T Type of the values.
 * @param a First value.
 * @param b Second value.
 * @return The absolute numerical difference of the two given values.
 */
template<typename T>
T difference(T a, T b) {
    return a < b ? b - a : a - b;
}

/**
 * @brief Iterates over the \b sorted container from \b begin to \b end,
 *        and searches a value that is nearest to \b value. If there are
 *        multiple values that are equally close to \b value, the first one is
 *        returned. Search is performed in O(log n) time with a binary search.
 * @tparam ForwardIterator Type of the iterator.
 * @tparam T Type of the value.
 * @param begin Iterator to the first element of the container.
 * @param end Iterator to the end of the container.
 * @param value Value to search.
 * @return Iterator to the nearest value.
 */
template<typename ForwardIterator, typename T>
ForwardIterator
nearestValue(
        ForwardIterator begin,
        ForwardIterator end,
        const T &value
) {
    if (begin == end) {
        return end;
    }

    // O(1) if we have random_access_iterator, O(n) otherwise
    auto distance = std::distance(begin, end);
    if (distance == 1) {
        return begin;
    }

    // O(1) if we have random_access_iterator, O(n) otherwise
    ForwardIterator beforeMiddle = std::next(begin, distance / 2 - 1);
    ForwardIterator middle = std::next(beforeMiddle);

    if (*middle == value) {
        return middle;
    }

    if (value < *middle &&
        difference(*beforeMiddle, value) <= difference(*middle, value)) {
        return nearestValue(begin, middle, value);
    }

    return nearestValue(middle, end, value);
}

// -------------------------------------------------------------------------- //

/**
 * @brief Iterates over the \b sorted container from \b begin to \b value,
 *        and returns a list of the \b offset values before \b value.
 * @tparam ForwardIterator Type of the iterator.
 * @param begin Iterator to the first element of the container.
 * @param value Iterator to the value to search.
 * @param offset Number of values to return.
 * @return A list of the \b offset values before \b value.
 */
template<typename ForwardIterator>
std::vector<ForwardIterator>
valBefore(
        ForwardIterator begin,
        ForwardIterator value,
        unsigned offset = 5
) {
    std::vector<ForwardIterator> result;
    if (begin == value) {
        return result;
    }

    // O(1) if we have random_access_iterator, O(n) otherwise
    auto distance = std::distance(begin, value);
    for (auto i = std::max(0l, distance - offset); i < distance; ++i) {
        result.push_back(std::next(begin, i));
    }

    return result;
}

// -------------------------------------------------------------------------- //

/**
 * @brief Returns a vector of \b offset iterators after \b value, unless it
 *        gets to end before being done.
 * @tparam ForwardIterator Type of the iterator.
 * @param begin Iterator to the first element of the container.
 * @param value Iterator to the value to search.
 * @param offset Number of values to return.
 * @return A list of the \b offset values after \b value.
 */
template<typename ForwardIterator>
std::vector<ForwardIterator>
valAfter(
        ForwardIterator value,
        ForwardIterator end,
        unsigned offset = 5
) {
    std::vector<ForwardIterator> result;

    ForwardIterator it = value;
    for (size_t i = 0; it != end && i < offset; ++it, ++i) {
        result.push_back(it);
    }

    return result;
}

// -------------------------------------------------------------------------- //

/**
 * @brief Displays the values of the container.
 * @tparam ForwardIterator Type of the iterator.
 * @param os Output stream.
 * @param v Vector of values to display.
 * @return The output stream.
 */
template<typename ForwardIterator>
std::ostream &
operator<<(
        std::ostream &os,
        const std::vector<ForwardIterator> &v
) {
    if (v.empty()) {
        return os;
    }

    os << *v.front();
    for (auto it = std::next(v.begin()); it != v.end(); ++it) {
        os << ' ' << **it;
    }

    return os;
}

int main() {
    std::vector<unsigned> val(1000);

    // Initialize the vector with random values, then sorts it
    std::random_device generator;
    std::uniform_int_distribution<unsigned> distribution(1, 2000);
    std::generate(val.begin(), val.end(), [&distribution, &generator]() {
        return distribution(generator);
    });
    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());

    // setup search for random value
    unsigned search = distribution(generator);
    auto nearestIt = nearestValue(val.begin(), val.end(), search);

    // print the results
    std::cout << std::setw(9) << std::left << "search" << ": "
              << search << std::endl;
    std::cout << std::setw(9) << std::left << "3 before" << ": "
              << valBefore(val.begin(), nearestIt, 3) << std::endl;
    std::cout << std::setw(9) << std::left << "nearest" << ": "
              << *nearestIt << std::endl;
    std::cout << std::setw(9) << std::left << "3 after" << ": "
              << valAfter(std::next(nearestIt), val.end(), 3) << std::endl;

    return EXIT_SUCCESS;
}
