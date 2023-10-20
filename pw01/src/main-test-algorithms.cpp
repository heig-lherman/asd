/* -----------------------------------------------------------------------------------
 * File name     : main-test-algorithms.cpp
 * Authors       : [redacted]
 * Creation date : 24.02.2022
 *
 * Description   : Programme de test des différents algorithmes.
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
#include <iostream>
#include <string_view>
#include <utility>
#include <fstream>

using namespace std;

constexpr size_t ALGORITHMS_AMOUNT = 3;
constexpr unsigned SEED = 659258764;
constexpr size_t SAMPLE_SIZES = 100;

//Making pair between enum and string name
constexpr array<pair<Sorting, string_view>, 4> SORTING_TYPES = {
	make_pair(Sorting::INCREASING, "increasing"),
	make_pair(Sorting::DECREASING, "decreasing"),
	make_pair(Sorting::RANDOM, "random"),
	make_pair(Sorting::ALMOST_SORTED, "almost-sorted")
};

using SortingAlgorithm = function<bool(vector<int>)>;
using SortingAlgorithms = array<pair<SortingAlgorithm, string>, ALGORITHMS_AMOUNT>;

void runTests(const SortingAlgorithms& algorithms) {
	for (auto const& sortingType: SORTING_TYPES) {

		cout << "Testing for sorting type: " << get<1>(sortingType) << '\n';
		cout << "Testing for sample size: " << SAMPLE_SIZES << '\n';

		vector<int> values = generateVector<int>(SAMPLE_SIZES, get<0>(sortingType), SEED);

		for (size_t i = 0; i < ALGORITHMS_AMOUNT; i++) {
			auto algorithm = algorithms[i];
			//cout algorithm type and sort vector "falues", cout true if sorted and false if not
			cout << get<1>(algorithm) << " is sorted : " << boolalpha << invoke(get<0>(algorithm), values)
				  << '\n';
		}
		cout << "\n";
	}
}

void testVectorGenerator() {
	ofstream outfile(("../../rapport/csv/vectorGenerator.csv"));
	if (!outfile.is_open()) {
		cerr << "Erreur d'ouverture du fichier de rapport en écriture" << endl;
		return;
	}

	outfile<<"n,";
	//Create vector, reserve capacity and fill all vector with different generation type + write header in csv file
	vector<vector<int>> generatedVector;
	generatedVector.reserve(SORTING_TYPES.size());
	for (const auto& sortings: SORTING_TYPES) {
		generatedVector.push_back(generateVector<int>(SAMPLE_SIZES, get<0>(sortings), SEED));
		outfile << get<1>(sortings) << (sortings == SORTING_TYPES.back() ? "" : ",");
	}

	outfile<<'\n';

	//write result in csv
	for (size_t i = 0; i < SAMPLE_SIZES; i++) {
		outfile << i + 1 << ',';
		for (auto v: generatedVector)
			outfile << v[i] << (v == generatedVector.back() ? "" : ",");

		outfile << '\n';
	}
	outfile.close();
}

int main() {
	const SortingAlgorithms sortingAlgorithms = {
		// Intentionally taking copies so that we do not disturb the source data
		make_pair([](vector<int> values) {
			bubbleSort(values);
			return is_sorted(values.begin(), values.end());
		}, "bubble-sort"),

		make_pair([](vector<int> values) {
			insertionSort(values);
			return is_sorted(values.begin(), values.end());
		}, "insertion-sort"),

		make_pair([](vector<int> values) {
			selectionSort(values);
			return is_sorted(values.begin(), values.end());
		}, "selection-sort")

	};

	testVectorGenerator();
	runTests(sortingAlgorithms);
}