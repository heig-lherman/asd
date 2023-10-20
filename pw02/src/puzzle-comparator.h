/*
  ---------------------------------------------------------------------------
  Fichier     : puzzle-comparator.h
  Nom du labo : L2-Recursivite
  Auteur(s)   : [redacted]
  Date        : 10.03.2022
  But         : Fonctions de comparaisons de PuzzlePiece
  Compilateur : gcc 11.2.0 (Solus)
  ---------------------------------------------------------------------------
*/

#ifndef ASD2022_L2_RECURSIVITE_PUZZLE_COMPARATOR_H
#define ASD2022_L2_RECURSIVITE_PUZZLE_COMPARATOR_H

#include "PuzzlePiece.h"
#include <vector>

/**
 * Check if a new PuzzlePiece can be added to the current Puzzle solution
 * @param puzzle vector of PuzzlePiece, contains already checked and approved PuzzlePiece objects
 * @param piece a PuzzlePiece to check against the solution
 * @return \b true if newPiece fits in the puzzle, \b false otherwise
 */
bool isPieceCompatibleWithPuzzle(const Puzzle &puzzle, const PuzzlePiece &piece);

#endif //ASD2022_L2_RECURSIVITE_PUZZLE_COMPARATOR_H
