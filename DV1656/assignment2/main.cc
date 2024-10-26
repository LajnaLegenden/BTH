#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.tab.hh"
#include "global.h"
#include "generateSymbolTree.c"
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

void yy::parser::error(std::string const&err)
{
    std::cout << "Syntax errors found! See the logs below: \n";
    std::cerr << "@error at line " << yylineno << ". Cannot generate a syntax for this input: " << err << std::endl;

    if (yylineno > 0 && yylineno <= source_lines.size()) {
        std::cerr << "Line " << yylineno << ": " << source_lines[yylineno - 1] << std::endl;
        std::cerr << std::string(std::to_string(yylineno).length() + 2, ' ') << "^" << std::endl;
    }
}


int main(int argc, char **argv)
{
    if(argc > 1) {
        read_source_file(argv[1]);  // Read the entire source file
        if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }

    if(USE_LEX_ONLY)
        yylex();
    else {
        yy::parser parser;
        if(!parser.parse() && !lexical_errors) {
            std::cout << "\nThe compiler successfully generated a syntax tree for the given input! \n";
            std::cout << "\nPrint Tree: \n";
            //root->print_tree();
            //root->generate_tree();
            Scope scope;
            scope.id = "Main";
            generateSymbolTree(&scope, root);
            cout << "\n\nSymbol Table: \n";
            for (auto const &currentNode : scope.table)
            {
                cout << currentNode.id << " : " << currentNode.type << endl;
            }

            Viz::saveToFile(&scope, "symbol_table.dot");
            
        }
        else {
          return lexical_errors;
        }

    }
    return 0;
}
