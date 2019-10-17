#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "piece.h"

#include <array>
#include <memory>
#include <iostream>
#include <vector>

namespace chess {

const int kNumBoardCols = 8;
const int kNumBoardRows = 8;

class Board {
  // Access as pieces_[y][x] or pieces_[row][col]
  std::unique_ptr<const Piece> pieces_[kNumBoardRows][kNumBoardCols];
  std::vector<std::unique_ptr<const Piece>> taken_pieces_;

  const Piece* GetPieceAt(int row, int col) const;
  void SetPieceAt(int row, int col, std::unique_ptr<const Piece> piece);

  bool IsValidMoveForPawn(int start_row, int start_col, int end_row, int end_col) const;
  bool IsValidMoveForKing(int start_row, int start_col, int end_row, int end_col) const;
  bool IsValidMoveForQueen(int start_row, int start_col, int end_row, int end_col) const;
  bool IsValidMoveForBishop(int start_row, int start_col, int end_row, int end_col) const;
  bool IsValidMoveForKnight(int start_row, int start_col, int end_row, int end_col) const;
  bool IsValidMoveForRook(int start_row, int start_col, int end_row, int end_col) const;

public:
  // Create a chess board with the default configuration of chess pieces.
  Board();

  // Copy the pieces from the other board to this one. This performs a deep copy of all the pieces
  // on the other board/taken pieces and the ones on this board will be brand new pieces.
  Board(const Board& other);

  // Transfers all the pieces from the other board to this one, including pieces on the board and taken pieces.
  // After this operation completes, the other board will be a valid board, just empty of pieces.
  Board(Board&& other);

  Board& operator=(const Board& other) = delete;
  Board& operator=(Board&& other) = delete;

  bool IsValidMove(int start_row, int start_col, int end_row, int end_col) const;
  bool MakeMove(int start_row, int start_col, int end_row, int end_col);
  void PlayGame();

  friend std::ostream& operator<<(std::ostream& o, const Board& b);

  ~Board() = default;
};

}  // namespace chess

#endif  // CHESS_BOARD_H
