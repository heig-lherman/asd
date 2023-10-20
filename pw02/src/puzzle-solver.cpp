/*
  ---------------------------------------------------------------------------
  Fichier     : puzzle-solver.cpp
  Nom du labo : L2-Recursivite
  Auteur(s)   : [redacted]
  Date        : 17.03.2022
  But         : Implémentation de la fonction de résolution du puzzle
  Compilateur : gcc 11.2.0 (Solus)
  ---------------------------------------------------------------------------
*/

#include "puzzle-solver.h"
#include "puzzle-comparator.h"

using namespace std;

void doSolvePuzzle(const Puzzle &availablePieces, Puzzle &currentSolution, vector<Puzzle> &solutions) {
    ++callCounter;
    if (currentSolution.size() == PUZZLE_SIZE) {
        solutions.push_back(currentSolution);
        return;
    }

    Puzzle nextAvailablePieces = availablePieces;
    for (size_t i = availablePieces.size(); i > 0; --i) {
        PuzzlePiece piece = availablePieces[i - 1];
        for (char rot = 'a'; rot <= 'd'; ++rot) {
            piece.rotate(rot);

            if (isPieceCompatibleWithPuzzle(currentSolution, piece)) {
                // Add the piece to the current solution and ignore it for the next step
                currentSolution.push_back(piece);
                piece.removeFromPuzzle(nextAvailablePieces);

                // Solve the next part of the puzzle
                doSolvePuzzle(nextAvailablePieces, currentSolution, solutions);

                // Lookup other solutions from this point.
                currentSolution.pop_back();
                nextAvailablePieces.push_back(piece);
            }
        }
    }
}

std::vector<Puzzle> solvePuzzle(const Puzzle &referencePuzzle) {
    vector<Puzzle> solutions;
    Puzzle currentSolution;
    doSolvePuzzle(referencePuzzle, currentSolution, solutions);
    return solutions;
}
