#ifndef SNAKEHEAD_HPP
#define SNAKEHEAD_HPP
#include "SnakeBody.hpp"
#include <ncurses.h>
#include "vector"
class SnakeHead : public SnakeBody
{
private:
    std::vector<SnakeBody> m_tail;

public:
    SnakeHead(int xPos, int yPos, int xSpeed, int ySpeed, char symbol = '@');
    SnakeHead();
    void update();
    void addTail();
};
#endif