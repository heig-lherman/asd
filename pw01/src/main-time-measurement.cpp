/* -----------------------------------------------------------------------------------
 * File name     : main-time-measurement.cpp
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Programme de génération de tableaux CSV avec le temps
 *                 d'exécution des différents algorithmes.
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#include "vector-generator.h"
#include "bubble-sort.h"
#include "insertion-sort.h"
#include "selection-sort.h"
#include <array>
#include <chrono>
#include <functional>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string_view>

using namespace std;

constexpr size_t ALGORITHMS_AMOUNT = 5;
constexpr unsigned SEED = 659258764;
constexpr array<size_t, 16> SAMPLE_SIZES = {0, 10, 25, 50, 100, 500, 1000, 2500, 5000, 7500, 10000, 15000, 20000, 25000, 35000, 50000};
constexpr array<pair<Sorting, string_view>, 4> SORTING_TYPES = {
        make_pair(Sorting::INCREASING, "increasing"),
        make_pair(Sorting::DECREASING, "decreasing"),
        make_pair(Sorting::RANDOM, "random"),
        make_pair(Sorting::ALMOST_SORTED, "almost-sorted")
};

using SortingAlgorithm = function<void(vector<int>&)>;
using SortingAlgorithms = array<pair<SortingAlgorithm, string>, ALGORITHMS_AMOUNT>;

double measureExecutionTime(const SortingAlgorithm &f, vector<int> &values) {
    auto startTime = chrono::steady_clock::now();
    f(values);
    auto endTime = chrono::steady_clock::now();
    chrono::duration<double, std::milli> timeMs = endTime - startTime;
    return timeMs.count();
}

string buildFilename(const string &baseFilename, const pair<Sorting, string_view> &sortingType) {
    string filename = baseFilename;
    filename.append("-");
    filename.append(get<1>(sortingType));
    filename.append(".csv");
    return filename;
}

void runTests(const string &baseFilename, const SortingAlgorithms &algorithms) {
    for (auto const &sortingType: SORTING_TYPES) {
        ofstream outfile(buildFilename(baseFilename, sortingType));
        if (!outfile.is_open()) {
            cerr << "Erreur d'ouverture du fichier de rapport en écriture" << endl;
            return;
        }

        cout << "Testing for sorting type: " << get<1>(sortingType) << endl;

        // Display header
        outfile << "n";
        for (auto const &algorithm: algorithms) {
            outfile << "," << get<1>(algorithm);
        }
        outfile << endl;


        for (size_t sampleSize: SAMPLE_SIZES) {
            cout << "Testing for sample size: " << sampleSize << endl;
            outfile << sampleSize;
            for (auto const &algorithm: algorithms) {
                vector<int> values = generateVector<int>(sampleSize, get<0>(sortingType), SEED);
                outfile << "," << fixed << setprecision(6) << measureExecutionTime(get<0>(algorithm), values);
            }
            outfile << endl;
        }

        outfile.close();
    }
}

int main() {
    const SortingAlgorithms sortingAlgorithms = {
            make_pair([](vector<int> &values) { bubbleSort(values); }, "bubble-sort"),
            make_pair([](vector<int> &values) { insertionSort(values); }, "insertion-sort"),
            make_pair([](vector<int> &values) { selectionSort(values); }, "selection-sort"),
            make_pair([](vector<int> &values) { std::sort(values.begin(), values.end()); }, "stl-sort"),
            make_pair([](vector<int> &values) { std::stable_sort(values.begin(), values.end()); }, "stl-stable-sort")
    };

    runTests("../../rapport/csv/time-measurement", sortingAlgorithms);
    return EXIT_SUCCESS;
}
