#include <iostream>
#include <vector>
#include "PuzzlePiece.h"
#include "puzzle-solver.h"

using namespace std;

unsigned long long callCounter = 0;

int main() {
    Puzzle basePuzzle = PuzzlePiece::generatePuzzle();
    vector<Puzzle> solutions = solvePuzzle(basePuzzle);

    for (const auto &solution: solutions) {
        for (const PuzzlePiece &piece: solution) {
            cout << piece << " ";
        }
        cout << endl;
    }

    cout << "\nNombre d'appels de la fonction recursive : " << callCounter << endl;
    return EXIT_SUCCESS;
}


