#include "SnakeHead.hpp"
#include "SnakeBody.hpp"

SnakeHead::SnakeHead(int xPos, int yPos, int xSpeed, int ySpeed, char symbol) : SnakeBody(xPos, yPos, xSpeed, ySpeed, symbol)
{
}

SnakeHead::SnakeHead() : SnakeBody(0,0,1,1,'#')
{
}

void SnakeHead::update()
{
    this->setPosition(this->getPositionX() + this->getXSpeed(), this->getPositionY() + this->getYSpeed());
}