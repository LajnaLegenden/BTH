#include "ConnectN.hpp"
#include "iostream"
using namespace std;
/*
  ! IMPORTANT !
  This file is allowed to be edited, and will be submitted to CodeGrade. 
*/

/**
 * All functions in this file should be replaced by your own! They are only
 * left here to make sure the project compiles!
 */

ConnectN::ConnectN(int columns, int rows, int numToConnect)
{
  this->columns = columns;
  this->rows = rows;
  this->numToConnect = numToConnect;
  this->state = GameStatuses::READY;
  boardPositions = new Colors *[rows];
  for (int i = 0; i < rows; i++)
  {
    this->boardPositions[i] = new Colors[columns];
    for (int j = 0; j < columns; j++)
    {
      this->boardPositions[i][j] = Colors::FREE;
    }
  }
}

ConnectN::~ConnectN()
{
  for (int i = 0; i < rows; i++)
  {
    delete[] this->boardPositions[i];
  }
  delete[] this->boardPositions;
}

bool ConnectN::yellowPlays(int col)
{
  return this->play(col, Colors::YELLOW);
}

bool ConnectN::redPlays(int col)
{
  return this->play(col, Colors::RED);
}

bool ConnectN::play(int col, Colors color)
{
  col = col - 1;
  if (state == GameStatuses::READY)
    state = GameStatuses::IN_GAME;
  else if (state == GameStatuses::YELLOW_WON || state == GameStatuses::RED_WON)
    return false;
  if (col < 0 || col >= columns)
  {
    return false;
  }
  for (int i = rows - 1; i >= 0; i--)
  {
    if (this->boardPositions[i][col] == Colors::FREE)
    {
      this->boardPositions[i][col] = color;
      (void)checkForWin(i, col, color);
      return true;
    }
  }
  return false;
}

GameStatuses ConnectN::getCurrentStatus() const
{
  return state;
}

Colors ConnectN::checkForWin(int row, int col, Colors player)
{
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->columns; j++)
    {
      Colors hasWin = this->checkForWinLoop(i, j, player);
      if (hasWin == Colors::RED)
      {
        this->state = GameStatuses::RED_WON;
        return Colors::RED;
      }
      else if (hasWin == Colors::YELLOW)
      {
        this->state = GameStatuses::YELLOW_WON;
        return Colors::YELLOW;
      }
    }
  }
  return Colors::FREE;
}

Colors ConnectN::checkForWinLoop(int row, int col, Colors player)
{
  bool exit = false;
  //Down
  for (int r = 0; r < numToConnect; r++)
  {
    if (r + row >= this->rows)
    {
      exit = true;
      break;
    }
    if (this->boardPositions[row + r][col] != player)
    {
      exit = true;
      break;
    }
  }

  if (exit == false)
    return player;
  //Left
  exit = false;
  for (int c = 0; c < numToConnect; c++)
  {
    if (c + col >= this->columns)
    {
      exit = true;
      break;
    }
    if (this->boardPositions[row][col + c] != player)
    {
      exit = true;
      break;
    }
  }
  if (exit == false)
    return player;
  //Dig down right
  exit = false;
  for (int i = 0; i < numToConnect; i++)
  {
    if (i + row >= this->rows || i + col >= this->columns)
    {
      exit = true;
      break;
    }
    if (this->boardPositions[row + i][col + i] != player)
    {
      exit = true;
      break;
    }
  }

  if (exit == false)
    return player;
  //Dig down left
  exit = false;
  for (int i = 0; i < numToConnect; i++)
  {
    if (row + i >= this->rows || col - i < 0)
    {
      exit = true;
      break;
    }
    if (this->boardPositions[row + i][col - i] != player)
    {
      exit = true;
      break;
    }
  }

  if (exit == false)
    return player;

  return Colors::FREE;
}
