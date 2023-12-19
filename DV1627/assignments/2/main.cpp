#include <iostream>
#include "ConnectN.hpp"

/*
    If you are working in Visual Studio (not code) on Windows want to check
    for memory leaks, include this at the top of this file

        #define _CRTDBG_MAP_ALLOC
        #include <crtdbg.h>

    and place this line at the beginning of the function main()

        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    If you are instead working on Linux, see the comments in CMakeLists.txt.

    Else, submit your code to CodeGrade as it will do the memory leak check
    for you. In the AutoTest section "Inga minnesläckor" in CodeGrade, press
    it's drop-down and check the information under "Errors".

    !! REMEMBER !!
    Leaks are only possible if the leaking code is executed. You have to
    create an object of your class in main() and call the function that
    causes allocates the memory of the leak in order to get the leak.
    CodeGrade will instead check the leak against the auto-tests.
*/

// This is the entry point to the program 'application'
// Replace the code in this file with code of your own.

int main()
{
  std::cout << "Hello, let's play some N-in-a-row!" << std::endl;
  {
    ConnectN game(7, 7, 4);
    game.yellowPlays(7);
    game.redPlays(6);
    game.yellowPlays(6);
    game.redPlays(5);
    game.yellowPlays(5);
    game.redPlays(4);
    game.yellowPlays(5);
    game.redPlays(4);
    game.yellowPlays(4);
    game.redPlays(2);
    game.yellowPlays(4);
  }
  std::cout << "Thank you for playing, goodbye!" << std::endl;

  return 0;
}