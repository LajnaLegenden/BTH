#include "GameEntity.hpp"
#include <ncurses.h>

void GameEntity::setPosition(int x, int y)
{
    this->m_positionX = x;
    this->m_positionY = y;
}

void GameEntity::setIcon(char symbol)
{
    this->m_symbol = symbol;
}

void GameEntity::draw()
{
    mvprintw(m_positionY, m_positionX, "%c", m_symbol);
}

GameEntity::GameEntity(char m_symbol)
{
    this->m_symbol = m_symbol;
}


int GameEntity::getPositionX()
{
    return m_positionX;
}

int GameEntity::getPositionY()
{
    return m_positionY;
}

char GameEntity::getSymbol()
{
    return m_symbol;
}