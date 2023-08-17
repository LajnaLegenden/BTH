#include <iostream>
#include "../includes/ResultColumn.hpp"
int main()
{
    ResultColumn resultColumn("asd", 5);
    std::cout << resultColumn.toString() << std::endl;
}
