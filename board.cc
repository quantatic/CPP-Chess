#include "board.h"
#include "piece.h"

#include <vector>
#include <memory>
#include <exception>

namespace chess {

Board::Board() {
  for(int col = 0; col < kNumBoardCols; col++) {
    pieces_[1][col] = std::make_unique<Piece>(PieceType::PAWN, PieceColor::WHITE);
    pieces_[6][col] = std::make_unique<Piece>(PieceType::PAWN, PieceColor::BLACK);
  }

  pieces_[0][0] = std::make_unique<Piece>(PieceType::ROOK, PieceColor::WHITE);
  pieces_[0][1] = std::make_unique<Piece>(PieceType::KNIGHT, PieceColor::WHITE);
  pieces_[0][2] = std::make_unique<Piece>(PieceType::BISHOP, PieceColor::WHITE);
  pieces_[0][3] = std::make_unique<Piece>(PieceType::KING, PieceColor::WHITE);
  pieces_[0][4] = std::make_unique<Piece>(PieceType::QUEEN, PieceColor::WHITE);
  pieces_[0][5] = std::make_unique<Piece>(PieceType::BISHOP, PieceColor::WHITE);
  pieces_[0][6] = std::make_unique<Piece>(PieceType::KNIGHT, PieceColor::WHITE);
  pieces_[0][7] = std::make_unique<Piece>(PieceType::ROOK, PieceColor::WHITE);

  pieces_[7][0] = std::make_unique<Piece>(PieceType::ROOK, PieceColor::BLACK);
  pieces_[7][1] = std::make_unique<Piece>(PieceType::KNIGHT, PieceColor::BLACK);
  pieces_[7][2] = std::make_unique<Piece>(PieceType::BISHOP, PieceColor::BLACK);
  pieces_[7][3] = std::make_unique<Piece>(PieceType::KING, PieceColor::BLACK);
  pieces_[7][4] = std::make_unique<Piece>(PieceType::QUEEN, PieceColor::BLACK);
  pieces_[7][5] = std::make_unique<Piece>(PieceType::BISHOP, PieceColor::BLACK);
  pieces_[7][6] = std::make_unique<Piece>(PieceType::KNIGHT, PieceColor::BLACK);
  pieces_[7][7] = std::make_unique<Piece>(PieceType::ROOK, PieceColor::BLACK);
}

std::ostream& operator<<(std::ostream& o, const chess::Board& b) {
  for(int row = kNumBoardRows - 1; row >= 0; row--) {
    for(int col = 0; col < kNumBoardCols; col++) {
      const Piece* p = b.pieces_[row][col].get();
      if(p != nullptr) {
        o << *p << " ";
      } else {
        o << ". ";
      }
    }

    o << "\n";
  }

  return o;
}

const Piece* Board::GetPieceAt(int row, int col) {
  if(row < 1 || col < 1 || row > kNumBoardRows || col > kNumBoardCols) {
    throw std::logic_error("Given row or column is out of bounds");
  }

  return pieces_[row - 1][col - 1].get();
}

bool Board::IsValidMove(int start_row, int start_col, int end_row, int end_col) {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  if(start_piece == nullptr) {
    return false;
  }

  if(start_piece->GetColor() == end_piece->GetColor()) {
    return false;
  }

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  switch(start_piece->GetType()) {
    case PieceType::KING:
      return std::abs(delta_row) <= 1 && std::abs(delta_col) <= 1
          && (end_piece == nullptr
              || (end_piece->GetColor() != start_piece->GetColor()));
    case PieceType::QUEEN:
      return false;
    case PieceType::BISHOP:
      return false;
    case PieceType::KNIGHT:
      return false;
    case PieceType::ROOK:
      return false;
    case PieceType::PAWN:
      return false;
  }

  return false;
}

}  // namespace

int main() {
  chess::Board b;
  std::cout << b << "\n";
}
