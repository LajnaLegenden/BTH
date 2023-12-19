#include <iostream>
#include "Vector.hpp"

/**
 *  Disclamer:
 *  This file will not be submitted for the assignment. Feel free to
 *  test your own Vector through this file and compile the target
 *  'application'.
 */

/**
 *  If you are working in Visual Studio (not code) on Windows want to check
 *  for memory leaks, include this at the top of this file
 *
 *      #define _CRTDBG_MAP_ALLOC
 *      #include <crtdbg.h>
 *
 *  and place this line at the beginning of the function main()
 *
 *      _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 *
 *  If you are instead working on Linux, see the comments in CMakeLists.txt.
 *  Else, submit your code to CodeGrade as it will do the memory leak check
 *  for you. In the AutoTest section "Inga minnesläckor" in CodeGrade, press
 *  it's drop-down and check the information under "Errors".
 *
 *  !! REMEMBER !!
 *  Leaks are only possible if the leaking code is executed. You have to
 *  create an object of your class in main() and call the function that
 *  causes allocates the memory of the leak in order to get the leak.
 *  CodeGrade will instead check the leak against the auto-tests.
 */

int main()
{
    std::cout << "Hello assignment!" << std::endl;

    // ---------------------------------------- //
    // ------- Example: Push and insert ------- //
    // ---------------------------------------- //

    Vector<int> vec;

    static constexpr int start_number = 1000;
    static constexpr int end_number = start_number + 100;

    for (int i = start_number; i < end_number; i++)
    {
        vec.push_back(i);
    }
    std::cout << "vec.size() = " << vec.size() << std::endl;
    // ---------------------------------------- //
    // ----- Example: Using custom struct ----- //
    // ---------------------------------------- //

    // {
    //     struct TextEditor
    //     {
    //         std::string Name;
    //         int Grade;
    //     }

    //     Vector<TextEditor> myVector;

    //     myVector.push_back({"Notepad++", 5});
    //     myVector.push_back({"VS Code", 8});
    //     myVector.push_back({"VIM", 10});

    //     for (int i = 0; i < myVector.size(); i++) {
    //         TextEditor& editor = myVector[i];
    //         std::cout << "Editor:\t" << editor.Name << "\t"
    //             << editor.Grade << "/10" << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    // ---------------------------------------- //
    // ---------- Example: 2D vector ---------- //
    // ---------------------------------------- //

    // {
    //     Vector<Vector<int>> nestedVector;

    //     for (int i = 10; i < 20; i++)
    //     {
    //         Vector<float> subVector;
    //         for (int j = 0; j < 10; j++)
    //         {
    //             subVector.push_back(i + j);
    //         }

    //         nestedVector.push_back(subVector);
    //     }
    // }

    return 0;
}