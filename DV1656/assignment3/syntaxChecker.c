#include "Node.h"
#include "StringUtils.h"
#include "SymbolTable.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <unordered_set>
using namespace std;

bool hasDuplicateIds(const vector<SymbolTableEntry> &symbols)
{
    unordered_set<string> seenIds;

    for (const auto &entry : symbols)
    {
        if (seenIds.find(entry.id) != seenIds.end())
        {
            return true; // Found a duplicate ID
        }
        seenIds.insert(entry.id);
    }
    return false;
}

bool checkForDuplicateIdentifiers(Scope *root)
{
    for (auto const &childScope : root->children)
    {
        if (checkForDuplicateIdentifiers(childScope))
        {
            return true;
        }
    }
    //Loop through all the variables in the current scope

    if (hasDuplicateIds(root->table))
    {
        cout << "Duplicate identifier found in scope: " << root->id << '\n';
        return true;
    }

    return false;
};


// Helper function to check excluded types
bool isExcludedType(const string &type)
{
    return type == "ClassDeclaration" || type == "void" || type == "MainClass" || type == "MethodDeclaration" ||
           type == "BlockStatement";
}

// Modified getAllChildren function
vector<Node *> getAllChildren(Node *node)
{
    vector<Node *> children;
    cout << "Getting all children for node: " << node->type << '\n';

    if (node->children.size() > 0)
    {
        for (auto child : node->children)
        {
            vector<Node *> grandChildren;
            // Only add child if it's not of excluded types
            if (!isExcludedType(child->type))
            {
                children.push_back(child);
                grandChildren = getAllChildren(child);
            }
            // cout << "Adding child: " << child->type << '\n';
            for (auto grandChild : grandChildren)
            {

                children.push_back(grandChild);
            }
        }
    }
    else if (!isExcludedType(node->type))
    {
        children.push_back(node);
    }

    return children;
}


vector<string> getUsedIdentifiers(Scope *root, const string &identifier)
{
    for (auto const &entry : root->children)
    {
        if (entry->id == identifier)
        {
            cout << "Found used identifier: " << identifier << '\n';
            //Return all valid identifiers as string vector
            vector<string> validIdentifiers;
            for (auto const &tableEntry : entry->table)
            {
                validIdentifiers.push_back(tableEntry.id);
            }
            return validIdentifiers;
        }
    }
}

bool checkForUnusedIdentifiers(Scope *root, Scope *top)
{
    for (auto const &childScope : root->children)
    {
        cout << "Checking scope: " << childScope->id << '\n';
        if (checkForUnusedIdentifiers(childScope, top))
        {
            return true;
        }
    }

    //Check all variables
    cout << "Checking variables in scope: " << root->id << '\n';
    auto source = root->source;
    if (source == nullptr)
    {
        cout << "No source code found for scope: " << root->id << '\n';
        return false;
    }

    //unique list of all new instaces
    vector<string> uniqueInstances;
    vector<string> validIdentifiers;

    Scope *i = root;
    while (i->parent != nullptr)
    {
        for (auto const &entry : i->table)
        {
            validIdentifiers.push_back(entry.id);
        }
        i = i->parent;
    }

    auto children = getAllChildren(source);
    for (auto const &child : children)
    {
        if (child->type == "NewInstance")
        {
            if (std::find(uniqueInstances.begin(), uniqueInstances.end(), child->value) == uniqueInstances.end())
            {
                cout << "Adding new instance: " << child->value << '\n';
                uniqueInstances.push_back(child->value);
                vector<string> newValidIdentifiers = getUsedIdentifiers(top, child->value);
                validIdentifiers.insert(validIdentifiers.end(), newValidIdentifiers.begin(), newValidIdentifiers.end());
            }
        }
    }

    for (auto const &child : children)
    {
        if (child->type == "Expression")
        {
            //  cout << "Checking expression: " << child->value << " with type " << child->type << '\n';
            //ensure that the child->value is in the valid identifiers, so it is declared
            if (std::find(validIdentifiers.begin(), validIdentifiers.end(), child->value) == validIdentifiers.end())
            {


                cout << "Expression is not declared: " << child->value << '\n';

                return true;
            }
        }
        if (child->type == "Assignment")
        {
            cout << "Checking expression: " << child->value << " with type " << child->type << '\n';
            //ensure that the child->value is in the valid identifiers, so it is declared
            if (std::find(validIdentifiers.begin(), validIdentifiers.end(), child->value) == validIdentifiers.end())
            {
                cout << "Expression is not declared: " << child->value << '\n';
                return true;
            }
        }
    }

    return false;
};
