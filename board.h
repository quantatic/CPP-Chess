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
	std::unique_ptr<const chess::Piece> pieces_[kNumBoardRows][kNumBoardCols];

	const Piece* GetPieceAt(int row, int col);

public:
	Board();
	bool IsValidMove(int start_row, int start_col, int end_row, int end_col);
	bool MakeMove(int start_row, int start_col, int end_row, int end_col);

	friend std::ostream& operator<<(std::ostream& o, const Board& b);
};

}  // namespace chess

#endif  // CHESS_BOARD_H
