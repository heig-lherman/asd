/*
  ---------------------------------------------------------------------------
  Fichier     : puzzle-solver.h
  Nom du labo : L2-Recursivite
  Auteur(s)   : [redacted]
  Date        : 17.03.2022
  But         : Déclaration de la fonction de résolution du puzzle
  Compilateur : gcc 11.2.0 (Solus)
  ---------------------------------------------------------------------------
*/

#ifndef ASD2022_L2_RECURSIVITE_PUZZLE_SOLVER_H
#define ASD2022_L2_RECURSIVITE_PUZZLE_SOLVER_H

#include "PuzzlePiece.h"
#include <vector>

/**
 * Main function for solving the given reference puzzle.
 * @param referencePuzzle The puzzle pieces to use for computing the solutions
 * @return A list of solutions of the given puzzle
 */
std::vector<Puzzle> solvePuzzle(const Puzzle &referencePuzzle);

extern unsigned long long callCounter;

#endif //ASD2022_L2_RECURSIVITE_PUZZLE_SOLVER_H
