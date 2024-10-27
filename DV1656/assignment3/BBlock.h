//
// Created by lajna on 2024-10-27.
//
#include "Tac.h"
#include <string>
#include <list>
#ifndef BBLOCK_H
#define BBLOCK_H

class BBlock {
public:
    std::string name;
    std::list<Tac> tacInstructions;  // Note: using tacInstructions instead of instructions
    std::string condition;           // Changed from Tac to string
    BBlock* trueBlock;
    BBlock* falseBlock;

    BBlock(const std::string& _name)
        : name(_name), trueBlock(nullptr), falseBlock(nullptr) {}
};



#endif //BBLOCK_H
