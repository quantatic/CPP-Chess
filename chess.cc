#include "board.h"
#include "piece.h"

#include <iostream>

int main() {
  std::cout << "Hello, World!\n";
  chess::Board b;

  
  std::cout << b << "\n";
  
  // This will error out, as it is un-implemented behavior, as of now.
  //b.MakeMove(1, 2, 3, 4);
  return 0;
}
