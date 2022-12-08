#include "Game.hpp"
#include <ncurses.h>
#include <chrono>
#include <iostream>

Game::Game(int row, int col)
{
    this->snake = SnakeHead(col / 2, row / 2, 1, '@');
    this->width = col;
    this->height = row;
    this->score = 0;
    this->highscore = 0;
    this->delta = std::chrono::milliseconds(500);
}

void Game::draw()
{
    snake.draw();
};

void Game::start()
{

    // Store the targeted duration between each frame.
    // This is used to NOT render a new frame each iteration,
    // but instead every 0.5 seconds. You can try to decrease it
    // for a faster game. :)

    // Used to store elapsed time between frames
    // Set to target delta to render first frame directly
    Clock::duration delta = TARGET_DELTA;
}

void Game::update()
{
    this->snake.update();
}

int Game::runGame()
{
    bool running = true;
    char input;
    /*
        The game loop
    */

    // This is the 'game loop', which should
    // 1. Handle any event (input)
    // 2. Update the game logic (if needed)
    // 3. Render a new frame (if needed)
    while (running)
    {
        Clock::time_point past = Clock::now();
        // Check if any input exist
        input = getch();
        if (input != ERR)
        {
            char next;
            while ((next = getch()) && next != ERR)
            {
                input = next;
            }

            if (input == 'q')
            {
                running = false;
            }
        }

        // calculate delta time
        Clock::time_point now = Clock::now();
        this->delta += now - past;
        past = now;
        if (delta >= TARGET_DELTA)
        {
            delta -= TARGET_DELTA;
            clear();
            this->update();
            this->draw();
        }
    }
    return 0;
};