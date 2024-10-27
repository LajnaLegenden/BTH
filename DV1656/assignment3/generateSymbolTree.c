#include "Node.h"
#include "StringUtils.h"
#include "SymbolTable.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;


void generateSymbolTree(Scope *currentScope, const Node *treeRoot)
{

    for (auto const &currentNode : treeRoot->children)
    {
        string const type = currentNode->type;
        if (type == "MainClass")
        {
            auto *newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->parent = currentScope;
            currentScope->children.push_back(newScope);
            currentScope->table.push_back({currentNode->value, currentNode->value, "Class"});
            newScope->source = currentNode;
            generateSymbolTree(newScope, currentNode);
        }
        else if (type == "void")
        {
            auto *newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->parent = currentScope;
            newScope->source = currentNode;

            auto *firstChild = currentNode->children.front();
            currentScope->table.push_back({currentNode->value, currentNode->type, "Method"});
            currentScope->children.push_back(newScope);
            generateSymbolTree(newScope, currentNode);
        }

        else if (type == "ClassDeclaration")
        {
            auto *newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->source = currentNode;

            newScope->parent = currentScope;
            currentScope->children.push_back(newScope);
            currentScope->table.push_back({currentNode->value, currentNode->value, "Class"});
            generateSymbolTree(newScope, currentNode);
        }
        else if (type == "int[]" || type == "bool" || type == "int" || type == "string[]")
        {
            currentScope->table.push_back({currentNode->value, type, "Variable"});
        }
        else if (type == "MethodDeclaration")
        {
            auto *newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->parent = currentScope;
            newScope->source = currentNode;

            currentScope->children.push_back(newScope);
            std::string const methodType = StringUtils::split(currentNode->value, ":")[0];
            std::string const name = StringUtils::split(currentNode->value, ":")[1];
            currentScope->table.push_back({name, methodType, "Method"});
            generateSymbolTree(newScope, currentNode);
        }
        else if (type == "VarDeclaration")
        {
            currentScope->table.push_back({currentNode->value, currentNode->children.front()->type, "Variable"});
        }
        else if (type == "ParameterList")
        {
            for (auto const &node : currentNode->children)
            {
                currentScope->table.push_back({node->value, node->type, "Variable"});
            }
        }
        else
        {
            //  cout << "Unknown node type: " << type << '\n';
        }
    }
};