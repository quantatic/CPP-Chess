#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "piece.h"

#include <array>
#include <memory>
#include <iostream>

namespace chess {

const int kNumBoardCols = 8;
const int kNumBoardRows = 8;

class Board {
	// Access as pieces_[y][x] or pieces_[row][col]
	const Piece* pieces_[kNumBoardRows][kNumBoardCols];

	const Piece* GetPieceAt(int row, int col) const;
	bool IsValidMoveForPawn(int start_row, int start_col, int end_row, int end_col) const;
	bool IsValidMoveForKing(int start_row, int start_col, int end_row, int end_col) const;
	bool IsValidMoveForQueen(int start_row, int start_col, int end_row, int end_col) const;
	bool IsValidMoveForBishop(int start_row, int start_col, int end_row, int end_col) const;
	bool IsValidMoveForKnight(int start_row, int start_col, int end_row, int end_col) const;
	bool IsValidMoveForRook(int start_row, int start_col, int end_row, int end_col) const;

public:
	Board();
	Board(const Board& other);

	bool IsValidMove(int start_row, int start_col, int end_row, int end_col) const;
	bool MakeMove(int start_row, int start_col, int end_row, int end_col);

	friend std::ostream& operator<<(std::ostream& o, const Board& b);

	~Board();
};

}  // namespace chess

#endif  // CHESS_BOARD_H
