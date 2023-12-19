#include "SnakeBody.hpp"

SnakeBody::SnakeBody(int xPos, int yPos, int xSpeed, int ySpeed, char symbol)
{
    this->setPosition(xPos, yPos);
    this->setSpeed(xSpeed, ySpeed);
    this->setIcon(symbol);
}

int SnakeBody::getXSpeed()
{
    return this->xSpeed;
}

int SnakeBody::getYSpeed()
{
    return this->ySpeed;
}
//
void SnakeBody::setSpeed(int xSpeed, int ySpeed)
{
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
}

void SnakeBody::update()
{
    this->setPosition(this->getPositionX() + this->getXSpeed(), this->getPositionY() + this->getYSpeed());
}

