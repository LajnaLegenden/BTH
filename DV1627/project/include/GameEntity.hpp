#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP
class GameEntity
{
public:
    GameEntity(char m_symbol = ' ');
    void setPosition(int x, int y);
    int getPositionX();
    int getPositionY();
    void setIcon(char symbol);
    void draw();
    char getSymbol();

private:
    int m_positionX;
    int m_positionY;
    char m_symbol;
};
#endif
