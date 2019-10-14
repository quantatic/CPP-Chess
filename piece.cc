#include "piece.h"

namespace chess {

Piece::Piece(PieceType type, PieceColor color) :
  type_(type), color_(color)
{ };

std::ostream& operator<<(std::ostream& o, const Piece& p) {
  switch(p.color_) {
    case PieceColor::WHITE:
      o << "\033[37;1m";
      break;
    case PieceColor::BLACK:
      o << "\033[31;1m";
      break;
  }

  switch(p.type_) {
    case PieceType::PAWN:
      o << "p";
      break;
    case PieceType::KING:
      o << "K";
      break;
    case PieceType::QUEEN:
      o << "Q";      
      break;
    case PieceType::BISHOP:
      o << "B";
      break;
    case PieceType::KNIGHT:
      o << "N";
      break;
    case PieceType::ROOK:
      o << "R";
      break;
  }

  o << "\033[0m";

  return o;
}

PieceType Piece::GetType() const {
  return type_;
}

PieceColor Piece::GetColor() const {
  return color_;
}

}  // namespace chess
