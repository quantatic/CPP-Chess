#include "board.h"
#include "piece.h"

#include <iostream>

int main() {
  std::cout << "Hello, World!\n";

  chess::Board b;
  b.PlayGame();

  return 0;
}
