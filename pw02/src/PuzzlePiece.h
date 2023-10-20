/*
  ---------------------------------------------------------------------------
  Fichier     : PuzzlePiece.h
  Nom du labo : L2-Recursivite
  Auteur(s)   : [redacted]
  Date        : 10.03.2022
  But         : Classe contenant une pièce de puzzle ainsi
                que quelques propriétés utiles
  Compilateur : gcc 11.2.0 (Solus)
  ---------------------------------------------------------------------------
*/

#ifndef ASD2022_L2_RECURSIVITE_PUZZLEPIECE_H
#define ASD2022_L2_RECURSIVITE_PUZZLEPIECE_H

#include "pieces.h"
#include <array>
#include <ostream>
#include <vector>

enum class Direction {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    NONE = -1
};

class PuzzlePiece;

constexpr size_t PUZZLE_SIZE = 9;
using Puzzle = std::vector<PuzzlePiece>;

class PuzzlePiece {
public:
    explicit PuzzlePiece(
            const Piece &sourcePiece,
            unsigned index,
            char rotation = 'a'
    ) : pieceData(sourcePiece),
        puzzleIndex(index),
        puzzleRotation(rotation) {

        hasArrosoirInverse = std::any_of(sourcePiece.begin(), sourcePiece.end(),
                                         [](auto &piece) { return piece == ARROSOIR_INVERSE; });
    }

    /**
     * @return a vector of PuzzlePiece with the 9 standard pieces in the standard order
     */
    static Puzzle generatePuzzle();

    /**
     * Converts a rotation identifier (a to d) to an unsigned amount of rotations
     * @param rotation The rotation identifier to convert
     * @return an unsigned integer with the number of rotations of the puzzle
     */
    static unsigned getRotationAmount(char rotation) { return (unsigned) (rotation - 'a'); }

    /**
     * @return get the number of times the puzzle has been rotated from its original rotation
     */
    unsigned getPuzzleRotationAmount() const { return getRotationAmount(puzzleRotation); }

    /**
     * Gets the puzzle attachement type for the given direction
     * @param side a direction to fetch
     * @return The attachement type for the corresponding puzzle side
     */
    AttachementType getPuzzleSide(Direction side = Direction::UP) const { return pieceData.at(unsigned(side)); }

    /**
     * @return Whether the piece contains the special Arrosoir Inverse piece
     */
    bool containsArrosoirInverse() const { return hasArrosoirInverse; };

    /**
     * Finds the given attachement type in the puzzle, if not returns Direction::NONE
     * @param attachementType The attachement type to search
     * @return The directio if found, else Direction::UP
     */
    Direction findAttachementType(AttachementType attachementType) const;

    /**
     * Helper function to find this piece in a puzzle based on the puzzle index then
     * erases it.
     * @param puzzle The puzzle to search in.
     */
    void removeFromPuzzle(Puzzle &puzzle) const;

    /**
     * Rotates the piece n times
     * @param rotations Number of times to rotate
     */
    void rotateTimes(unsigned rotations);

    /**
     * Rotates a puzzle piece counter-clockwise for the given
     * rotation identifier: a = 0 ccw rotations, d = 4 ccw rotations
     * @param rotation Identifier, between 'a' and 'd'
     */
    void rotate(char rotation);

    bool operator==(const PuzzlePiece &rhs) const;
    inline bool operator!=(const PuzzlePiece &rhs) const { return !(rhs == *this); }

    friend std::ostream &operator<<(std::ostream &os, const PuzzlePiece &rhs);

private:
    Piece pieceData;
    unsigned puzzleIndex;
    char puzzleRotation;
    bool hasArrosoirInverse;
};

#endif //ASD2022_L2_RECURSIVITE_PUZZLEPIECE_H
