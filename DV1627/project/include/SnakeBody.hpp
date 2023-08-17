#include "GameEntity.hpp"
#include <ncurses.h>
#include "vector"

#ifndef SNAKEBODY_HPP
#define SNAKEBODY_HPP
class SnakeBody : public GameEntity
{
private:
    int xSpeed;
    int ySpeed;

public:
    SnakeBody(int xPos, int yPos, int xSpeed, int ySpeed, char symbol);
    int getXSpeed();
    int getYSpeed();
    void update();
    void setSpeed(int xSpeed, int ySpeed);
};
#endif