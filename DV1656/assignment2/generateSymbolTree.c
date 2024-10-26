#include "Node.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "SymbolTable.h"
#include "StringUtils.h"
using namespace std;


void generateSymbolTree(Scope *currentScope, const Node *treeRoot)
{

    for (auto const &currentNode : treeRoot->children)
    {
        string const type = currentNode->type;
        if (type == "MainClass")
        {
           auto * newScope = new Scope();
           newScope->id = currentNode->value;
           newScope->parent = currentScope;
           currentScope->children.push_back(newScope);
            currentScope->table.push_back({currentNode->value, "ClassDeclaration"});
           generateSymbolTree(newScope, currentNode);
        }
        else if (type == "MainMethod")
        {
            auto * newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->parent = currentScope;
            auto * firstChild = currentNode->children.front();
            newScope->table.push_back({firstChild->value, firstChild->type});
            currentScope->children.push_back(newScope);
        }
        else if (type == "STRING ARRAY")
        {
            currentScope->table.push_back({currentNode->value, "STRING ARRAY"});
        }
        else if (type == "ClassDeclaration")
        {
            auto * newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->parent = currentScope;
            currentScope->children.push_back(newScope);
            currentScope->table.push_back({currentNode->value, currentNode->type});
            generateSymbolTree(newScope, currentNode);
        } else if (type == "INT ARRAY" || type == "BOOLEAN" || type == "INT")
        {
            currentScope->table.push_back({currentNode->value, type});
        } else if (type == "MethodDeclaration")
        {
            auto * newScope = new Scope();
            newScope->id = currentNode->value;
            newScope->parent = currentScope;
            auto * firstChild = currentNode->children.front();
            currentScope->children.push_back(newScope);
            std::string const methodType = StringUtils::split(currentNode->value, ":")[0];
            std::string const name = StringUtils::split(currentNode->value, ":")[1];
            currentScope->table.push_back({name, methodType});
            generateSymbolTree(newScope, currentNode);
        }
        else if (type == "VarDeclaration")
        {
            currentScope->table.push_back({currentNode->value, currentNode->children.front()->type});
        }
        else if (type == "ParameterList")
        {
            for (auto const &node : currentNode->children)
            {
                currentScope->table.push_back({node->value, node->type});
            }
        }
        else
        {
            cout << "Unknown node type: " << type << '\n';
            }
    }
};