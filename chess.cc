#include "board.h"
#include "piece.h"

#include <iostream>

int main() {
  std::cout << "Hello, World!\n";
  chess::Board b;
  std::cout << b << "\n";
  return 0;
}