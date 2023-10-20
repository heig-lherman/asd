/* -----------------------------------------------------------------------------------
 * File name     : main_test.cpp
 * Authors       : [redacted]
 * Creation date : 25.03.2022
 *
 * Description   : Programmes de tests pour les différents programmes de tris
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */
#include "tri_par_base.h"
#include "tri_rapide.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

const unsigned SEED = 3735928559;

int main() {
    std::default_random_engine seededRandom(SEED);

    size_t N = 10000;

    // Create a new vector and fill it with random values
    vector<unsigned> initialVector(N);
    generate(initialVector.begin(), initialVector.end(), [&]() { return seededRandom() % 100; });

    vector<unsigned> sortedVector(initialVector);
    sort(sortedVector.begin(), sortedVector.end());

    // Display the size
    cout << "Sorting vectors of size " << N << endl;

    // Sort using tri_comptage
    vector<unsigned> v2(N);
    tri_comptage(initialVector.begin(), initialVector.end(), v2.begin(), [](unsigned a) { return a; }, 100);
    cout << "tri_comptage : " << boolalpha << (v2 == sortedVector) << endl;

    // Sort using tri_par_base (1)
    vector<unsigned> tmp(initialVector);
    tri_par_base<vector<unsigned>::iterator, 1>(tmp.begin(), tmp.end());
    cout << "tri_par_base (1): " << boolalpha << (tmp == sortedVector) << endl;

    // Sort using tri_par_base (2)
    tmp = initialVector;
    tri_par_base<vector<unsigned>::iterator, 2>(tmp.begin(), tmp.end());
    cout << "tri_par_base (2): " << boolalpha << (tmp == sortedVector) << endl;

    // Sort using tri_par_base (4)
    tmp = initialVector;
    tri_par_base<vector<unsigned>::iterator, 4>(tmp.begin(), tmp.end());
    cout << "tri_par_base (4): " << boolalpha << (tmp == sortedVector) << endl;

    // Sort using tri_par_base (8)
    tmp = initialVector;
    tri_par_base<vector<unsigned>::iterator, 8>(tmp.begin(), tmp.end());
    cout << "tri_par_base (8): " << boolalpha << (tmp == sortedVector) << endl;

    // Sort using tri_par_base (16)
    tmp = initialVector;
    tri_par_base<vector<unsigned>::iterator, 16>(tmp.begin(), tmp.end());
    cout << "tri_par_base (16): " << boolalpha << (tmp == sortedVector) << endl;

    // Sort using tri_rapide
    tmp = initialVector;
    tri_rapide(tmp.begin(), tmp.end());
    cout << "tri_rapide : " << boolalpha << (tmp == sortedVector) << endl;

    return EXIT_SUCCESS;
}

