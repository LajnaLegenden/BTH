#include "Visualizer.hpp"

Visualizer::Visualizer() : Visualizer(DEFAULT_SIZE, DEFAULT_SIZE) {}

Visualizer::Visualizer(int columns, int rows) : columns(columns), rows(rows) {
  board.resize(rows + 2);
  for (int y = 0; y < rows + 2; ++y) {
    board[y].resize(columns + 2);
    for (int x = 0; x < columns + 2; ++x) {
      board[y][x] = ' ';
    }
  }
  for (int x = 0; x < columns + 2; x++) {
    board[0][x] = '-';
    board[rows + 1][x] = '-';
  }
  for (int y = 0; y < rows + 2; y++) {
    board[y][0] = '|';
    board[y][columns + 1] = '|';
  }
  board[0][0] = '+';
  board[0][columns + 1] = '+';
  board[rows + 1][0] = '+';
  board[rows + 1][columns + 1] = '+';
  cnt.resize(columns);
  for (int y = 0; y < columns; ++y) {
    cnt[y] = 0;
  }
}

void Visualizer::yellowPlays(int column) {
  if (!outside(columns)) {
    board[rows - cnt[column - 1]++][column] = "x";
  }
}

void Visualizer::redPlays(int column) {
  if (!outside(columns)) {
    board[rows - cnt[column - 1]++][column] = "o";
  }
}

std::string Visualizer::print() {
  std::string result;
  for (int y = 0; y < board.size(); ++y) {
    for (int x = 0; x < board[y].size(); ++x) {
      result += board[y][x];
    }
    result += '\n';
  }
  return result;
}

bool Visualizer::outside(int column) {
  return column < 1 || column > columns || cnt[column - 1] >= rows;
}