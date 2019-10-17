#include "board.h"
#include "piece.h"

#include <iostream>

int main() {
  std::cout << "Hello, World!\n";

  chess::Board b;
  chess::Board b2 = b;
  chess::Board b3 = std::move(b);
  std::cout << b << b2 << b3;

  return 0;
}
