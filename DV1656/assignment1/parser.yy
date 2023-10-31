%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY true //change this macro to true if you want to isolate the lexer from the parser.
}
%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;
  
}
// definition of set of tokens. All tokens are of type string
%token <std::string>  PUBLIC CLASS VOID MAIN STRING INT BOOLEAN IF ELSE WHILE PRINT TRUE FALSE THIS NEW NOT AND OR LESS_THAN GREATER_THAN EQUAL ADD SUBTRACT MULTIPLY DIVIDE LENGTH LEFT_BRACE RIGHT_BRACE LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET RIGHT_BRACKET DOT COMMA SEMICOLON ASSIGN IDENTIFIER INTEGER_LITERAL COMMENT ERROR
%token END 0 "end of file"

//definition of operator precedence. See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl
%left PLUSOP MINUSOP
%left MULTOP

// definition of the production rules. All production rules are of type Node
%type <Node *> root expression factor
%{
#include <stdio.h>
%}

%%

Goal:
    MainClass: MainClass ClassDeclaration | EOF ;


MainClass:
    PUBLIC CLASS IDENTIFIER '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' IDENTIFIER ')' '{' Statement '}' '}' ;

ClassDeclaration:
    CLASS IDENTIFIER '{' VarDeclaration* MethDeclaration* '}' ;

VarDeclaration:
    Type IDENTIFIER ';' ;

MethDefinition : PUBLIC Type IDENTIFIER '(' ParamList ')' '{' VarStatements RETURN Expression ';' '}' ;

ParamList:
    /* empty */
    | Type IDENTIFIER ParamRest* ;

ParamRests : ParamRest ParamRests
           | /* empty */ ;
VarStatements : VarStatement VarStatements
              | /* empty */ ;

Type:
    INT '[' ']'
    | BOOLEAN
    | INT
    | IDENTIFIER ;

Statement:
    '{' Statement* '}'
    | IF '(' Expression ')' Statement ELSEopt
    | WHILE '(' Expression ')' Statement
    | SYSTEM_OUT_PRINTLN '(' Expression ')' ';'
    | IDENTIFIER '=' Expression ';'
    | IDENTIFIER '[' Expression ']' '=' Expression ';' ;

ELSEopt:
    /* empty */
    | ELSE Statement ;

Expression:
    Expression OP Expression
    | Expression '[' Expression ']'
    | Expression '.' LENGTH
    | Expression '.' IDENTIFIER '(' ExpList ')'
    | INTEGER_LITERAL
    | TRUE
    | FALSE
    | IDENTIFIER
    | THIS
    | NEW INT '[' Expression ']'
    | NEW IDENTIFIER '(' ')'
    | '!' Expression
    | '(' Expression ')' ;

OP:
    "&&"
    | "||"
    | "<"
    | ">"
    | "=="
    | "+"
    | "-"
    | "*"
    | "/" ;

ExpList:
    /* empty */
    | Expression ExpRest* ;

ExpRest:
    ',' Expression ;

%%