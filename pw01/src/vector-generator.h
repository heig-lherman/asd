/* -----------------------------------------------------------------------------------
 * File name     : vector-generator.h
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Génération de vecteurs selon certains paramètres spécifiques
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_VECTOR_GENERATOR_H
#define ASD2022_L1_COMPLEXITE_VECTOR_GENERATOR_H

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <iostream>

using namespace std;

enum class Sorting {
    INCREASING, DECREASING, RANDOM, ALMOST_SORTED
};

/**
 * Generate a vector ordered depending on the chosen type of sorting
 * @tparam T the type of the vector returned
 * @param size the size of the vector
 * @param sortingType the sorting type wanted
 * @param seed the seed for the shuffle
 * @return a vector sorted depending on the sortingType
 */
template<typename T>
std::vector<T> generateVector(std::size_t size, Sorting sortingType, unsigned seed = 0) {
    std::vector<T> result(size);
    iota(result.begin(), result.end(), 0);

    std::default_random_engine seededRandomDevice(seed);

    switch (sortingType) {
        default:
        case Sorting::INCREASING:
            return result;
        case Sorting::DECREASING:
            reverse(result.begin(), result.end());
            return result;
        case Sorting::RANDOM:
            shuffle(result.begin(), result.end(), seededRandomDevice);
            return result;
        case Sorting::ALMOST_SORTED: {
            vector<T> randomVector = generateVector<T>(size, Sorting::RANDOM, seed);
            transform(result.begin(), result.end(), randomVector.begin(), result.begin(),
                      [&seededRandomDevice](T a, T b) { return ((seededRandomDevice() % 100) < 40) ? b : a; });
            return result;
        }
    }
}


#endif //ASD2022_L1_COMPLEXITE_VECTOR_GENERATOR_H
