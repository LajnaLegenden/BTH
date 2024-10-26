#include "Node.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

// Define symbol classes
class Symbol {
public:
    string name;
    string type;
    int lineNumber;

    Symbol(string name, string type, int lineNumber) : name(name), type(type), lineNumber(lineNumber) {}

    virtual void printSymbol() {
        cout << "  " << type << ": " << name << " (declared at line " << lineNumber << ")" << endl;
    }
};

class ClassSymbol : public Symbol {
public:
    map<string, Symbol*> variables;
    map<string, Symbol*> methods;

    ClassSymbol(string name, int lineNumber) : Symbol(name, "class", lineNumber) {}

    void printSymbol() override {
        cout << type << ": " << name << " (declared at line " << lineNumber << ")" << endl;
        for (auto const& x : variables) {
            x.second->printSymbol();
        }
        for (auto const& x : methods) {
            x.second->printSymbol();
        }
    }
};

class MethodSymbol : public Symbol {
public:
    string returnType;
    vector<Symbol*> parameters;

    MethodSymbol(string name, string returnType, int lineNumber) :
        Symbol(name, "method", lineNumber), returnType(returnType) {}

    void printSymbol() override {
        cout << "  " << type << ": " << name << " : " << returnType << " (declared at line " << lineNumber << ")" << endl;
        for (auto const& param : parameters) {
            param->printSymbol();
        }
    }
};

class VariableSymbol : public Symbol {
public:
    VariableSymbol(string name, string type, int lineNumber) : Symbol(name, type, lineNumber) {}
};


class SymbolTable {
public:
    vector<map<string, Symbol*>> scopes;

    void enterScope() {
        scopes.push_back(map<string, Symbol*>());
    }

    void exitScope() {
        scopes.pop_back();
    }

    void addSymbol(Symbol* symbol) {
        scopes.back()[symbol->name] = symbol;
    }

    Symbol* lookupSymbol(string name) {
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].find(name) != scopes[i].end()) {
                return scopes[i][name];
            }
        }
        return nullptr;
    }

    void printSymbolTable() {
        for (int i = 0; i < scopes.size(); i++) {
            cout << "Scope " << i << ":" << endl;
            for (auto const& x : scopes[i]) {
                x.second->printSymbol();
            }
        }
    }

    void generateSymbolTableGraph() {
        ofstream outStream;
        char* filename = "symbol_table.dot";
        outStream.open(filename);
        outStream << "digraph {" << endl;
        outStream << "  rankdir=LR;" << endl; // Arrange nodes from left to right
        int clusterId = 0;

        for (const auto& scope : scopes) {
            outStream << "  subgraph cluster_" << clusterId++ << " {" << endl;
            outStream << "    label = \"Scope " << clusterId - 1 << "\";" << endl;
            for (const auto& symbol : scope) {
                string symbolLabel = symbol.second->type + "\\n" + symbol.second->name;
                outStream << "    \"" << symbolLabel << "\" [shape=record];" << endl;
            }
            outStream << "  }" << endl;
        }
        outStream << "}" << endl;
        outStream.close();
    }
};


void buildSymbolTable(Node* node, SymbolTable* symbolTable) {
    if (node == nullptr) {
        return;
    }

    if (node->type == "program") {
        symbolTable->enterScope(); // Enter the global scope
    }
    else if (node->type == "main_class") {
        auto* classSymbol = new ClassSymbol(node->children.front()->value, node->children.front()->lineno);
        symbolTable->addSymbol(classSymbol);
        symbolTable->enterScope(); // Enter the class scope

        // Assuming the second child is the "main" method:
        Node* mainMethodNode = node->children.back();
        auto* methodSymbol = new MethodSymbol("main", "void", mainMethodNode->lineno);
        classSymbol->methods["main"] = methodSymbol;
        symbolTable->enterScope(); // Enter the method scope

        // Process statements within the main method if needed
        for (Node* child : mainMethodNode->children) {
            buildSymbolTable(child, symbolTable);
        }

        symbolTable->exitScope(); // Exit the method scope
        symbolTable->exitScope(); // Exit the class scope
    }
    else if (node->type == "class_declaration") {
        auto* classSymbol = new ClassSymbol(node->children.front()->value, node->children.front()->lineno);
        symbolTable->addSymbol(classSymbol);
        symbolTable->enterScope(); // Enter the class scope

        // Process class members (variables and methods)
        for (auto it = next(node->children.begin()); it != node->children.end(); ++it) {
            buildSymbolTable(*it, symbolTable);
        }

        symbolTable->exitScope(); // Exit the class scope
    }
    else if (node->type == "var_declaration") {
        string varType = node->children.front()->type;
        string varName = node->children.back()->value;
        auto* varSymbol = new VariableSymbol(varName, varType, node->lineno);
        symbolTable->addSymbol(varSymbol);
    }
    else if (node->type == "method_declaration") {
        string returnType = node->children[0]->type;
        string methodName = node->children[1]->value;
        auto* methodSymbol = new MethodSymbol(methodName, returnType, node->lineno);

        // Assuming the third child is the parameter list:
        if (node->children.size() > 2) {
            Node* paramListNode = node->children[2];
            for (Node* paramNode : paramListNode->children) {
                string paramType = paramNode->children.front()->type;
                string paramName = paramNode->children.back()->value;
                auto* paramSymbol = new VariableSymbol(paramName, paramType, paramNode->lineno);
                methodSymbol->parameters.push_back(paramSymbol);
            }
        }

        symbolTable->addSymbol(methodSymbol);
        symbolTable->enterScope(); // Enter the method scope
        // Process method body (statements)
        if (node->children.size() > 3) {
            Node* methodBodyNode = *next(node->children.begin(), 3);
            for (Node* statementNode : methodBodyNode->children) {
                buildSymbolTable(statementNode, symbolTable);
            }
        }
        symbolTable->exitScope(); // Exit the method scope
    }

    // Recursively process children
    for (Node* child : node->children) {
        buildSymbolTable(child, symbolTable);
    }
}
