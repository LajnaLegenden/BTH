#ifndef CONNECT_N_HPP
#define CONNECT_N_HPP

/*
  ! IMPORTANT !
  This file is allowed to be edited, and will be submitted to CodeGrade. 
*/

/*
  Example of how to access:

  Colors variable;
  variable = Colors::FREE;
  if (variable == Colors::RED)
*/
enum class Colors
{
  FREE,  // Used to represent a free slot
  RED,   // Used to represent a slot occupied by the red player
  YELLOW // Used to represent a slot occupied by the yellow player
};

/*
  Example of how to access:

  GameStatuses variable;
  variable = GameStatuses::RED_WON;
  if (variable == GameStatuses::READY)
*/
enum class GameStatuses
{
  READY,      // When the game is ready to start but has not started yet
  IN_GAME,    // When the game is currently playing
  RED_WON,    // When the red player has won
  YELLOW_WON, // When the yellow player has won
  FULL_BOARD  // When there is no more empty slots
};

/**
 * Main class for the game ConnectFour. This class keeps track of a board and
 * its status and lets two players play against each other.
 */
class ConnectN
{
public:
  /**
   * Constructor taking columns, rows and number of pieces to connect as
   * arguments
   */
  ConnectN(int columns, int rows, int numToConnect);

  /** Destructor */
  ~ConnectN();

  /**
   * Function used to place a piece for the yellow player. Returns true if the
   * yellow player can play on that column and false otherwise.
   */
  bool yellowPlays(int col);

  /**
   * Function used to place a piece for the red player. Returns true if the red
   * player can play on that column and false otherwise.
   */
  bool redPlays(int col);

  /**
   * can be used to check whether the game has not yet
   * started, if it is ongoing, whether someone has won and who in that case and
   * if the board is full and no more pieces can be placed.
   */
  GameStatuses getCurrentStatus() const;

  // Add your own public methods here

private:
  /**
   * double-pointer to be used as a 2D-array keeping track of each board
   * position and its status
   */
  Colors **boardPositions;

  // Add your own private methods and member variables here

  int rows;
  int columns;
  int numToConnect;
  bool play(int col, Colors color);
  Colors checkForWin(int row, int col, Colors player);
  Colors checkForWinLoop(int row, int col, Colors player);
  GameStatuses state;
};

#endif // CONNECT_N_HPP