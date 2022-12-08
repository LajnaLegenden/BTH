#include "GameEntity.hpp"
#include "SnakeHead.hpp"
#include <chrono>
using Clock = std::chrono::high_resolution_clock;
#ifndef GAME_HPP
#define GAME_HPP
class Game
{

private:
    int score;
    int highscore;
    int width;
    int height;

    Clock::duration delta;
    const Clock::duration TARGET_DELTA = std::chrono::milliseconds(500);
    SnakeHead snake;

    void draw();
    void update();

public:
    void start();
    int runGame();
    Game(int row, int col);
};
#endif