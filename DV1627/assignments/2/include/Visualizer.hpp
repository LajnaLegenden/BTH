#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <string>
#include <vector>

/** A utility class to visualize the progress in Connect four games*/
class Visualizer {
 public:
  /** Constructor that crates a default board of 7x7 */
  Visualizer();
  /** Constructor for custom board sizes */
  Visualizer(int columns, int rows);
  /** Use this method when the yellow player plays */
  void yellowPlays(int column);
  /** Use this method when the red player plays */
  void redPlays(int column);
  /** Returns a string showing the board and the status */
  std::string print();

 private:
  /** Connect four is usually played on 7x7 boards */
  static const int DEFAULT_SIZE = 7;

  /** Test whether placing a piece in a given column results in the piece
   * landing outside the board
   */
  bool outside(int column);
  /** 2d-vector that contains a representation of the game board */
  std::vector<std::vector<std::string>> board;
  /** Count how many pieces  that are stacked in each column */
  std::vector<int> cnt;
  /** Number of columns */
  int columns;
  /** Number of rows */
  int rows;
};

#endif  // VISUALIZER_HPP