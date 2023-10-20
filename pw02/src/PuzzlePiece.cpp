/*
  ---------------------------------------------------------------------------
  Fichier     : PuzzlePiece.cpp
  Nom du labo : L2-Recursivite
  Auteur(s)   : [redacted]
  Date        : 10.03.2022
  But         : Implémentation de la class PuzzlePiece.cpp
  Compilateur : gcc 11.2.0 (Solus)
  ---------------------------------------------------------------------------
*/

#include "PuzzlePiece.h"
#include <cassert>
#include <vector>

using namespace std;

void PuzzlePiece::rotateTimes(unsigned rotations) {
    const size_t sidesSize = pieceData.size();
    Piece result;
    for (size_t i = rotations % sidesSize, j = 0; j < sidesSize; ++i, ++j) {
        result[j] = pieceData[i % sidesSize];
    }

    pieceData = result;
    puzzleRotation = char('a' + ((getPuzzleRotationAmount() + rotations) % sidesSize));
}

void PuzzlePiece::rotate(char rotation) {
    assert(rotation >= 'a' && rotation <= 'd');
    if (puzzleRotation < rotation) {
        rotateTimes(getRotationAmount(rotation) - getPuzzleRotationAmount());
        return;
    }

    rotateTimes(unsigned(pieceData.size()) - getPuzzleRotationAmount() + getRotationAmount(rotation));
}

Direction PuzzlePiece::findAttachementType(AttachementType attachementType) const {
    auto pieceIt = find(pieceData.begin(), pieceData.end(), attachementType);
    if (pieceIt == pieceData.end()) {
        return Direction::NONE;
    }

    return Direction(distance(pieceData.begin(), pieceIt));
}

void PuzzlePiece::removeFromPuzzle(Puzzle &puzzle) const {
    erase_if(puzzle, [this](const PuzzlePiece &piece) {
        return piece.puzzleIndex == this->puzzleIndex;
    });
}

bool PuzzlePiece::operator==(const PuzzlePiece &rhs) const {
    return pieceData == rhs.pieceData
           && puzzleRotation == rhs.puzzleRotation
           && puzzleIndex == rhs.puzzleIndex;
}

ostream &operator<<(ostream &os, const PuzzlePiece &rhs) {
    os << rhs.puzzleIndex << rhs.puzzleRotation;
    return os;
}

Puzzle PuzzlePiece::generatePuzzle() {
    Puzzle pieces;
    for (unsigned i = 0; i < PIECES.size(); i++) {
        pieces.emplace_back(PIECES[i], i + 1);
    }
    return pieces;
}
