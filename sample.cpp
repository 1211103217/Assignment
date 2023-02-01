#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
  int rows, columns, num_zombies;

  std::cout << "Enter the number of rows: "; std::cin >> rows;
  std::cout << "Enter the number of columns: "; std::cin >> columns;
  std::cout << "Enter the number of zombies: "; std::cin >> num_zombies;
  std::cout << std::endl;

  std::vector<std::vector<char>> board(rows, std::vector<char>(columns, ' '));

  std::cout << "***********************************" << std::endl;
  std::cout << "*                                 *" << std::endl;
  std::cout << "*        Aliens Vs Zombies        *" << std::endl;
  std::cout << "*                                 *" << std::endl;
  std::cout << "***********************************" << std::endl;
  std::cout << std::endl;

  // Add aliens to the center of the board
  board[rows/2][columns/2] = 'A';

  // Add zombies randomly to the board
  srand(time(NULL));
  int z_count = 0;
  while (z_count < num_zombies) {
    int i = rand() % rows;
    int j = rand() % columns;
    if (board[i][j] == ' ') {
      board[i][j] = 'Z';
      z_count++;
    }
  }

  std::cout << std::setw(1) << " ";
  for (int i = 1; i <= columns; i++) {
    std::cout << std::setw(5) << i;
  }
  std::cout << std::endl;
  for (int i = 0; i < rows; i++) {
    std::cout << "   +";
    for (int j = 0; j < columns; j++) {
      std::cout << "----+";
    }
    std::cout << std::endl;
    std::cout << std::setw(2) << i + 1 << " |";
    for (int j = 0; j < columns; j++) {
      std::cout << std::setw(2) << " " << board[i][j] << std::setw(2) << " |";
    }
    std::cout << std::endl;
  }
  std::cout << "   +";
  for (int j = 0; j < columns; j++) {
    std::cout << "----+";
  }
  std::cout << std::endl;
  return 0;
}
