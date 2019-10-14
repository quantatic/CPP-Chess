#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <iostream>

namespace chess {
	enum class PieceType {
		KING,
		QUEEN,
		BISHOP,
		KNIGHT,
		ROOK,
		PAWN,
	};

	enum class PieceColor {
		WHITE,
		BLACK,
	};


class Piece {
	PieceType type_;
	PieceColor color_;

public:
	Piece(PieceType type, PieceColor color);
	PieceType GetType() const;
	PieceColor GetColor() const;

	friend std::ostream& operator<<(std::ostream& o, const Piece& p);
};

}  // namespace chess

#endif  // CHESS_PIECE_H
