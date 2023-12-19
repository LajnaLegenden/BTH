#include <string>
// Used for 'rendering' in the terminal
#include <ncurses.h>
// Used for generating random numbers
#include <stdlib.h> // srand, rand
// Used for measuring time
#include "include/Game.hpp"
int main()
{
	int rows = 0;
	int columns = 0;

	/*
		Initialize the screen/terminal
	*/

	// Begin the 'ncurses'-mode
	initscr();

	// Retrieve the current width and height of the terminal.
	getmaxyx(stdscr, rows, columns);

	// Makes it possible to continue running without any input
	// (cetch() do not halt the program)
	nodelay(stdscr, TRUE);
	cbreak(); // Input is one char at a time
	noecho(); // Input is not printed in terminal

	/*
		Show the welcome screen
	*/

	std::string welcomeText = "Press space to continue.";

	// Clear the terminal
	clear();

	// Write to the terminal, at given position
	// "%s" is written, %s is a string that is replaced with welcomeText.c_str()
	mvprintw(rows / 2, columns / 2 - welcomeText.size() / 2, "%s", welcomeText.c_str());

	// Also possible, but we need the width to center it.
	// mvprintw(rows/2, columns/2 - welcomeText.size()/2, "Press space to continue.");

	// Makes the cursor (the 'blinking' line/block in the terminal) invisible
	curs_set(0);

	char input;
	do
	{
		input = getch();
	} while (input != ' ');

	clear();

	/*
		Initialize the timer and randomizer
	*/

	// Make it possible to write 'Clock' instead of
	// 'std::chrono::high_resolution_clock' it is needed.

	// Set seed for random numbers based on the current time.
	// A seed is needed in order to generate different numbers
	// everytime the application is executed.
	srand(time(NULL));

	/*
		Initialize the scene
	*/
	Game game(rows, columns);
	game.start();
	game.runGame();
	// End the 'ncurses'-mode
	endwin();

	return 0;
}