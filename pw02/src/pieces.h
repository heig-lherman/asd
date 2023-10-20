//
//  pieces.h
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#ifndef pieces_h
#define pieces_h

#include <array>
#include <vector>

enum AttachementType {
  FILLE_HAUT,
  FILLE_BAS,
  DAME_HAUT,
  DAME_BAS,
  ARROSOIR_GAUCHE,
  ARROSOIR_DROIT,
  GATEAU_GAUCHE,
  GATEAU_DROIT,
  ARROSOIR_INVERSE,
  NONE };

using Piece = std::array<AttachementType,4>;
using Pieces = std::vector<Piece>;

extern const Pieces PIECES;

#endif /* pieces_h */
