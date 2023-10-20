/*
  ---------------------------------------------------------------------------
  Fichier     : puzzle-comparator.cpp
  Nom du labo : L2-Recursivite
  Auteur(s)   : [redacted]
  Date        : 10.03.2022
  But         : Implémentation des fonctions de comparaison de PuzzlePieces
  Compilateur : gcc 11.2.0 (Solus)
  ---------------------------------------------------------------------------
*/

#include "puzzle-comparator.h"
#include "pieces.h"
#include <array>

using namespace std;

/**
 * Pairs of the matching attachement types for any given piece.
 */
constexpr array<pair<AttachementType, AttachementType>, 4> MATCHING_TYPES = {
        make_pair(FILLE_HAUT, FILLE_BAS),
        make_pair(DAME_HAUT, DAME_BAS),
        make_pair(ARROSOIR_GAUCHE, ARROSOIR_DROIT),
        make_pair(GATEAU_GAUCHE, GATEAU_DROIT),
};

/**
 * Searches the side of ARROSOIR_INVERSE in p and, given pos, handle if p can be added in the puzzle
 * @param piece A PuzzlePiece that contains the ARROSOIR_INVERSE in one of its side
 * @param puzzlePosition The position where p could be added in the puzzle
 * @return \b true if ARROSOIR_INVERSE does not create a conflict with a future PuzzlePiece and can be added to the puzzle,
 * \b false otherwise
 */
bool checkValidPositionForArrosoirInverse(const PuzzlePiece &piece, size_t puzzlePosition);

/**
 * Compare whether two attachement types of the sides of a puzzle piece matches.
 * @param newPiece A PuzzlePiece to add in the puzzle
 * @param newPieceSide corresponds to the side of the new piece to check
 * @param placedPiece A PuzzlePiece already in the puzzle
 * @param placedPieceSide corresponds to the side of the placed piece to check
 * @return true if the first attachement type matches with the second, false otherwise
 */
bool comparePuzzlePieces(
        const PuzzlePiece &newPiece,
        Direction newPieceSide,
        const PuzzlePiece &placedPiece,
        Direction placedPieceSide
);

/**
 * Compare whether two attachement types of the sides of a puzzle are of the same "category"
 * @param newPiece A PuzzlePiece to add in the puzzle
 * @param newPieceSide corresponds to the side of the new piece to check
 * @param placedPiece A PuzzlePiece already in the puzzle
 * @param placedPieceSide corresponds to the side of the placed piece to check
 * @return true if the first attachement type matches with the second, false otherwise
 */
bool comparePuzzlePieceCategories(
        const PuzzlePiece &newPiece,
        Direction newPieceSide,
        const PuzzlePiece &placedPiece,
        Direction placedPieceSide
);

bool isPieceCompatibleWithPuzzle(
        const vector<PuzzlePiece> &puzzle,
        const PuzzlePiece &piece
) {
    const size_t currentPosition = puzzle.size();
    // shortcut check for arrosoir inverse special case
    if (piece.containsArrosoirInverse() && !checkValidPositionForArrosoirInverse(piece, currentPosition)) {
        return false;
    }

    // empty puzzle, no checks required
    if (puzzle.empty()) {
        return true;
    }

    // first line => check left side only
    if (currentPosition < 3) {
        return comparePuzzlePieces(piece, Direction::LEFT, puzzle[currentPosition - 1], Direction::RIGHT);
    }

    // first and second column => check able to match with north-easternly piece
    if (currentPosition % 3 < 2 &&
        comparePuzzlePieceCategories(piece, Direction::RIGHT, puzzle[currentPosition - 2], Direction::DOWN)) {
        return false;
    }

    // first column => check up only
    if (currentPosition % 3 == 0) {
        return comparePuzzlePieces(piece, Direction::UP, puzzle[currentPosition - 3], Direction::DOWN);
    }

    // check up and left
    return comparePuzzlePieces(piece, Direction::UP, puzzle[currentPosition - 3], Direction::DOWN)
           && comparePuzzlePieces(piece, Direction::LEFT, puzzle[currentPosition - 1], Direction::RIGHT);
}

bool comparePuzzlePieces(
        const PuzzlePiece &newPiece,
        Direction newPieceSide,
        const PuzzlePiece &placedPiece,
        Direction placedPieceSide
) {
    const AttachementType testAttachment = newPiece.getPuzzleSide(newPieceSide);
    const AttachementType placedAttachment = placedPiece.getPuzzleSide(placedPieceSide);
    return std::any_of(MATCHING_TYPES.begin(), MATCHING_TYPES.end(), [=](auto &pair) {
        return (get<0>(pair) == testAttachment && get<1>(pair) == placedAttachment)
               || (get<1>(pair) == testAttachment && get<0>(pair) == placedAttachment);
    });
}

bool comparePuzzlePieceCategories(
        const PuzzlePiece &newPiece,
        Direction newPieceSide,
        const PuzzlePiece &placedPiece,
        Direction placedPieceSide
) {
    const AttachementType testAttachment = newPiece.getPuzzleSide(newPieceSide);
    const AttachementType placedAttachment = placedPiece.getPuzzleSide(placedPieceSide);
    return std::any_of(MATCHING_TYPES.begin(), MATCHING_TYPES.end(), [=](auto &pair) {
        return (get<0>(pair) == testAttachment && get<1>(pair) == placedAttachment)
               || (get<1>(pair) == testAttachment && get<0>(pair) == placedAttachment)
               || (get<0>(pair) == testAttachment && get<0>(pair) == placedAttachment)
               || (get<1>(pair) == testAttachment && get<1>(pair) == placedAttachment);
    });
}


bool checkValidPositionForArrosoirInverse(const PuzzlePiece &piece, size_t puzzlePosition) {
    if (!piece.containsArrosoirInverse()) {
        return true;
    }

    switch (piece.findAttachementType(ARROSOIR_INVERSE)) {
        case Direction::UP:
            // up -> 0 1 2 => first line
            return puzzlePosition <= 2;
        case Direction::RIGHT:
            // right -> 2 5 8 => last column
            return puzzlePosition % 3 == 2;
        case Direction::DOWN:
            // down -> 6 7 8 => last line
            return puzzlePosition >= 6;
        case Direction::LEFT:
            // left -> 0 3 6 => first column
            return puzzlePosition % 3 == 0;
        default:
            // unknown direction => invalid
            return false;
    }
}
