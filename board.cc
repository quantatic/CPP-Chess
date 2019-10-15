#include "board.h"
#include "piece.h"

#include <vector>
#include <memory>
#include <exception>

namespace chess {

Board::Board() {

  for(int col = 0; col < kNumBoardCols; col++) {
    pieces_[1][col] = std::make_unique<const Piece>(PieceType::PAWN, PieceColor::WHITE);
    pieces_[6][col] = std::make_unique<const Piece>(PieceType::PAWN, PieceColor::BLACK);
  }

  pieces_[0][0] = std::make_unique<const Piece>(PieceType::ROOK, PieceColor::WHITE);
  pieces_[0][1] = std::make_unique<const Piece>(PieceType::KNIGHT, PieceColor::WHITE);
  pieces_[0][2] = std::make_unique<const Piece>(PieceType::BISHOP, PieceColor::WHITE);
  pieces_[0][3] = std::make_unique<const Piece>(PieceType::KING, PieceColor::WHITE);
  pieces_[0][4] = std::make_unique<const Piece>(PieceType::QUEEN, PieceColor::WHITE);
  pieces_[0][5] = std::make_unique<const Piece>(PieceType::BISHOP, PieceColor::WHITE);
  pieces_[0][6] = std::make_unique<const Piece>(PieceType::KNIGHT, PieceColor::WHITE);
  pieces_[0][7] = std::make_unique<const Piece>(PieceType::ROOK, PieceColor::WHITE);

  pieces_[7][0] = std::make_unique<const Piece>(PieceType::ROOK, PieceColor::BLACK);
  pieces_[7][1] = std::make_unique<const Piece>(PieceType::KNIGHT, PieceColor::BLACK);
  pieces_[7][2] = std::make_unique<const Piece>(PieceType::BISHOP, PieceColor::BLACK);
  pieces_[7][3] = std::make_unique<const Piece>(PieceType::KING, PieceColor::BLACK);
  pieces_[7][4] = std::make_unique<const Piece>(PieceType::QUEEN, PieceColor::BLACK);
  pieces_[7][5] = std::make_unique<const Piece>(PieceType::BISHOP, PieceColor::BLACK);
  pieces_[7][6] = std::make_unique<const Piece>(PieceType::KNIGHT, PieceColor::BLACK);
  pieces_[7][7] = std::make_unique<const Piece>(PieceType::ROOK, PieceColor::BLACK);
}

Board::Board(const Board& other) {
  // For every square, either copy over the nullptr, or create a deep copy of
  // the piece that resides there.
  for(int row = 1; row <= kNumBoardRows; row++) {
    for(int col = 1; col <= kNumBoardCols; col++) {
      const Piece* other_piece = GetPieceAt(row, col);
      if(other_piece != nullptr) {
        // Simply create a new unique_ptr at this location, utilizing the copy
        // constructor of the old piece.
        SetPieceAt(row, col, std::make_unique<const Piece>(*other_piece));
      } else {
        SetPieceAt(row, col, nullptr);
      }
    }
  }
}

/*std::ostream& operator<<(std::ostream& o, const chess::Board& b) {
  for(int row = kNumBoardRows; row > 0; row--) {
    for(int col = 1; col <= kNumBoardCols; col++) {

      const Piece* this_piece = b.GetPieceAt(row, col);
      if(this_piece == nullptr) {
        continue;
      }

      for(int render_row = kNumBoardRows; render_row > 0; render_row--) {
        o << render_row << " ";
        for(int render_col = 1; render_col <= kNumBoardCols; render_col++) {
          const Piece* p = b.GetPieceAt(render_row, render_col);
          if(p != nullptr) {
            if(p == this_piece || b.IsValidMove(row, col, render_row, render_col)) {
              o << "\033[42;1m" << *p << "\033[0m" << " ";
            } else {
              o << *p << " ";
            }
          } else {
            if(b.IsValidMove(row, col, render_row, render_col)) {
              o << "\033[42;1m" << "." << "\033[0m" << " ";
            } else {
              o << ". ";
            }
          }
        }

        o << "\n";
      }

      o << " ";
      for(int render_col = 1; render_col <= kNumBoardCols; render_col++) {
        o << " " << render_col;
      }

      o << "\n";

      o << "Taken Pieces: [";
      if(b.taken_pieces_.size() > 0) {
        o << *b.taken_pieces_[0];
      }

      for(auto i = b.taken_pieces_.begin() + 1; i < b.taken_pieces_.end(); i++) {
        o << ", " << **i;
      }

      o << "]";

      o << "\n";
    }
  }

  return o;
}*/

std::ostream& operator<<(std::ostream& o, const chess::Board& b) {
  for(int render_row = kNumBoardRows; render_row > 0; render_row--) {
    o << render_row << " ";
    for(int render_col = 1; render_col <= kNumBoardCols; render_col++) {
      const Piece* p = b.GetPieceAt(render_row, render_col);
      if(p != nullptr) {
        o << *p << " ";
      } else {
        o << ". ";
      }
    }

    o << "\n";
  }

  o << " ";
  for(int render_col = 1; render_col <= kNumBoardCols; render_col++) {
    o << " " << render_col;
  }

  o << "\n";

  o << "Taken Pieces: [";
  if(b.taken_pieces_.size() > 0) {
    o << *b.taken_pieces_[0];
  }

  for(auto i = b.taken_pieces_.begin() + 1; i < b.taken_pieces_.end(); i++) {
    o << ", " << **i;
  }

  o << "]\n";

  return o;
}

// TODO make this algorithm actually correct
bool Board::IsValidMoveForPawn(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  int move_direction;

  switch(start_piece->GetColor()) {
    case PieceColor::WHITE:
      move_direction = 1;
      break;
    case PieceColor::BLACK:
      move_direction = -1;
      break;
  }

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  return delta_row == move_direction && delta_col == 0
    && end_piece == nullptr;
}

bool Board::IsValidMoveForKing(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  return std::abs(delta_row) <= 1 && std::abs(delta_col) <= 1
      && (end_piece == nullptr
          || (end_piece->GetColor() != start_piece->GetColor()));
}

bool Board::IsValidMoveForQueen(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  // Valid moves for queens can be either a perfect diagonal,
  // or a case where number of rows/cols is changing by 0 (moving
  // in a perfectly straight line).
  if(std::abs(delta_row) != std::abs(delta_col)
      && delta_row != 0 && delta_col != 0) {
    return false;
  }
  
  //get "signum" -> we're gonna iterate square by square over the movement path
  int tmp_delta_row = delta_row == 0 ? 0 : delta_row / std::abs(delta_row);
  int tmp_delta_col = delta_col == 0 ? 0 : delta_col / std::abs(delta_col);

  int tmp_row = start_row + tmp_delta_row;
  int tmp_col = start_col + tmp_delta_col;

  while(tmp_row != end_row || tmp_col != end_col) {
    const Piece* found_piece = GetPieceAt(tmp_row, tmp_col);
    // If we run into any piece, can't be a valid move
    if(found_piece != nullptr) {
      return false;
    }

    tmp_row += tmp_delta_row;
    tmp_col += tmp_delta_col;
  }

  return (end_piece == nullptr
    || end_piece->GetColor() != start_piece->GetColor());
}

bool Board::IsValidMoveForBishop(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  // Must be moving the same amount in both rows and cols
  // (must be a perfect diagonal)
  if(std::abs(delta_row) != std::abs(delta_col)) {
    return false;
  }
  
  //get "signum" -> we're gonna iterate square by square over the movement path
  int tmp_delta_row = delta_row == 0 ? 0 : delta_row / std::abs(delta_row);
  int tmp_delta_col = delta_col == 0 ? 0 : delta_col / std::abs(delta_col);

  int tmp_row = start_row + tmp_delta_row;
  int tmp_col = start_col + tmp_delta_col;

  while(tmp_row != end_row || tmp_col != end_col) {
    const Piece* found_piece = GetPieceAt(tmp_row, tmp_col);
    // If we run into any piece, can't be a valid move
    if(found_piece != nullptr) {
      return false;
    }

    tmp_row += tmp_delta_row;
    tmp_col += tmp_delta_col;
  }

  return (end_piece == nullptr
    || end_piece->GetColor() != start_piece->GetColor());
}

bool Board::IsValidMoveForKnight(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  return ((std::abs(delta_row) == 2 && std::abs(delta_col) == 1)
            || (std::abs(delta_row) == 1 && std::abs(delta_col) == 2))
      && (end_piece == nullptr || end_piece->GetColor() != start_piece->GetColor());


  return false;
}

bool Board::IsValidMoveForRook(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  int delta_row = end_row - start_row;
  int delta_col = end_col - start_col;

  // Has to be going in a straight line. If this isn't the
  // case, can't be a valid move.
  if(delta_row != 0 && delta_col != 0) {
    return false;
  }

  //get "signum" -> we're gonna iterate square by square over the movement path
  int tmp_delta_row = delta_row == 0 ? 0 : delta_row / std::abs(delta_row);
  int tmp_delta_col = delta_col == 0 ? 0 : delta_col / std::abs(delta_col);

  int tmp_row = start_row + tmp_delta_row;
  int tmp_col = start_col + tmp_delta_col;

  while(tmp_row != end_row || tmp_col != end_col) {
    const Piece* found_piece = GetPieceAt(tmp_row, tmp_col);
    // If we run into any piece, can't be a valid move
    if(found_piece != nullptr) {
      return false;
    }

    tmp_row += tmp_delta_row;
    tmp_col += tmp_delta_col;
  }

  return (end_piece == nullptr
    || end_piece->GetColor() != start_piece->GetColor());
}


const Piece* Board::GetPieceAt(int row, int col) const {
  if(row < 1 || col < 1 || row > kNumBoardRows || col > kNumBoardCols) {
    throw std::logic_error("Given row or column is out of bounds");
  }

  return pieces_[row - 1][col - 1].get();
}

void Board::SetPieceAt(int row, int col, std::unique_ptr<const Piece> piece) {
  if(row < 1 || col < 1 || row > kNumBoardRows || col > kNumBoardCols) {
    throw std::logic_error("Given row or column is out of bounds");
  }

  pieces_[row - 1][col - 1] = std::move(piece);
}

bool Board::IsValidMove(int start_row, int start_col, int end_row, int end_col) const {
  const Piece* start_piece = GetPieceAt(start_row, start_col);
  const Piece* end_piece = GetPieceAt(end_row, end_col);

  if(start_piece == nullptr) {
    return false;
  }

  if(end_piece != nullptr
      && start_piece->GetColor() == end_piece->GetColor()) {
    return false;
  }

  switch(start_piece->GetType()) {
    case PieceType::KING:
      return IsValidMoveForKing(start_row, start_col, end_row, end_col);
    case PieceType::QUEEN:
      return IsValidMoveForQueen(start_row, start_col, end_row, end_col);
    case PieceType::BISHOP:
      return IsValidMoveForBishop(start_row, start_col, end_row, end_col);
    case PieceType::KNIGHT:
      return IsValidMoveForKnight(start_row, start_col, end_row, end_col);
    case PieceType::ROOK:
      return IsValidMoveForRook(start_row, start_col, end_row, end_col);
    case PieceType::PAWN:
      return IsValidMoveForPawn(start_row, start_col, end_row, end_col);
  }
  //NOTREACHED
  return false;
}

bool Board::MakeMove(int start_row, int start_col, int end_row, int end_col) {
  if(!Board::IsValidMove(start_row, start_col, end_row, end_col)) {
    return false;
  }

  const Piece* end_piece = GetPieceAt(end_row, end_col);

  // If we actually took a piece during this move, add the taken piece to the
  // taken piece list. This also has the effect of moving ownership of the taken
  // piece to the taken piece list.
  //
  // We have to get the piece manually from the piece array here, as we're
  // actually concerned with ownership now.
  if(end_piece != nullptr) {
    taken_pieces_.push_back(std::move(pieces_[end_row - 1][end_col - 1]));
  }

  SetPieceAt(end_row, end_col, std::move(pieces_[start_row - 1][start_col - 1]));

  return true;
}

void Board::PlayGame() {
  for(int i = 0; i < 5; i++) {
    for(int piece_row = 1; piece_row <= kNumBoardRows; piece_row++) {
      for(int piece_col = 1; piece_col <= kNumBoardCols; piece_col++) {
        for(int move_row = 1; move_row <= kNumBoardRows; move_row++) {
          for(int move_col = 1; move_col <= kNumBoardCols; move_col++) {
            if(MakeMove(piece_row, piece_col, move_row, move_col)) {
              std::cout << *this << "\n";
            }
          }
        }
      }
    }
  }
}

}  // namespace
