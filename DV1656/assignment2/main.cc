#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.tab.hh"
#include "global.h"
#include "generateSymbolTree.c"
#include "syntaxChecker.c"
#include "Viz.h"
extern Node* root;
extern FILE* yyin;
extern int yylineno;
extern yy::parser::symbol_type yylex();

std::vector<std::string> source_lines;

void read_source_file(const char* filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        source_lines.push_back(line);
    }
}

void yy::parser::error(std::string const&msg)
{
    std::cout << "Syntax errors found! See the logs below: \n";
    std::cerr << "@error at line " << yylineno << ". Cannot generate a syntax for this input: " << msg << std::endl;

    if (yylineno > 0 && yylineno <= source_lines.size()) {
        std::cerr << "Line " << yylineno << ": " << source_lines[yylineno - 1] << std::endl;
        std::cerr << std::string(std::to_string(yylineno).length() + 2, ' ') << "^" << std::endl;
    }
}


int main(const int argc, char **argv)
{
    if(argc > 1) {
        read_source_file(argv[1]);  // Read the entire source file
        if((yyin = fopen(argv[1], "r")) == nullptr) {
            perror(argv[1]);
            return 1;
        }
    }

    if(USE_LEX_ONLY)
        yylex();
    else {
        yy::parser parser;
        if(!parser.parse() && (lexical_errors == 0)) {
            std::cout << "\nThe compiler successfully generated a syntax tree for the given input! \n";
            root->generate_tree();
            Scope scope;
            scope.source = root;
            scope.id = "root";
            generateSymbolTree(&scope, root);
            Viz::saveToFile(&scope, "symbol_table.dot");
            if (checkForDuplicateIdentifiers(&scope)) {
                exit(1);
            }
            if (checkForUnusedIdentifiers(&scope, &scope)) {
                exit(1);
            }

            exit(0);
        }
        else {
          return lexical_errors;
        }

    }
    return 0;
}
