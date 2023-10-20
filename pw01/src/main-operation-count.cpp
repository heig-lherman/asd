/* -----------------------------------------------------------------------------------
 * File name     : main-operation-count.cpp
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Programme de génération de tableaux CSV avec le compte
 *                 des opérations en utilisant la classe OpCounter.
 *
 * Compiler      : gcc version 11.2.0 (Solus)
 * ----------------------------------------------------------------------------------- */

#include "vector-generator.h"
#include "bubble-sort.h"
#include "insertion-sort.h"
#include "selection-sort.h"
#include "OpCounter.h"
#include <array>
#include <functional>
#include <fstream>
#include <iostream>
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

using ValuesType = OpCounter<int>;
using SortingAlgorithm = function<void(vector<ValuesType>&)>;
using SortingAlgorithms = array<pair<SortingAlgorithm, string>, ALGORITHMS_AMOUNT>;

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
            outfile << "," << get<1>(algorithm) << "-assignments" << "," << get<1>(algorithm) << "-comparisons";
        }
        outfile << endl;


        for (size_t sampleSize: SAMPLE_SIZES) {
            cout << "Testing for sample size: " << sampleSize << endl;
            outfile << sampleSize;
            for (auto const &algorithm: algorithms) {
                vector<ValuesType> values = generateVector<ValuesType>(sampleSize, get<0>(sortingType), SEED);
                ValuesType::resetCounters();
                get<0>(algorithm)(values);
                outfile << "," << ValuesType::getCopyCounter() << "," << ValuesType::getComparisonCounter();
                ValuesType::resetCounters();
            }
            outfile << endl;
        }

        outfile.close();
    }
}

int main() {
    const SortingAlgorithms sortingAlgorithms = {
            make_pair([](vector<ValuesType> &values) { bubbleSort(values); }, "bubble-sort"),
            make_pair([](vector<ValuesType> &values) { insertionSort(values); }, "insertion-sort"),
            make_pair([](vector<ValuesType> &values) { selectionSort(values); }, "selection-sort"),
            make_pair([](vector<ValuesType> &values) { std::sort(values.begin(), values.end()); }, "stl-sort"),
            make_pair([](vector<ValuesType> &values) { std::stable_sort(values.begin(), values.end()); }, "stl-stable-sort")
    };

    runTests("../../rapport/csv/operation-count", sortingAlgorithms);
    return EXIT_SUCCESS;
}
