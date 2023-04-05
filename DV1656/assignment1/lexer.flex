%top{
#include "parser.tab.hh"
#define YY_DECL yy::parser::symbol_type yylex()
#include "Node.h"
int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 
%%

"public"           {if(USE_LEX_ONLY) {printf("PUBLIC");} else {return yy::parser::make_PUBLIC(yytext);}}
"class"            {if(USE_LEX_ONLY) {printf("CLASS");} else {return yy::parser::make_CLASS(yytext);}}
"void"             {if(USE_LEX_ONLY) {printf("VOID");} else {return yy::parser::make_VOID(yytext);}}
"main"             {if(USE_LEX_ONLY) {printf("MAIN");} else {return yy::parser::make_MAIN(yytext);}}
"String"           {if(USE_LEX_ONLY) {printf("STRING");} else {return yy::parser::make_STRING(yytext);}}
"int"              {if(USE_LEX_ONLY) {printf("INT");} else {return yy::parser::make_INT(yytext);}}
"boolean"          {if(USE_LEX_ONLY) {printf("BOOLEAN");} else {return yy::parser::make_BOOLEAN(yytext);}}
"if"               {if(USE_LEX_ONLY) {printf("IF");} else {return yy::parser::make_IF(yytext);}}
"else"             {if(USE_LEX_ONLY) {printf("ELSE");} else {return yy::parser::make_ELSE(yytext);}}
"while"            {if(USE_LEX_ONLY) {printf("WHILE");} else {return yy::parser::make_WHILE(yytext);}}
"System.out.println" {if(USE_LEX_ONLY) {printf("PRINT");} else {return yy::parser::make_PRINT(yytext);}}
"true"             {if(USE_LEX_ONLY) {printf("TRUE");} else {return yy::parser::make_TRUE(yytext);}}
"false"            {if(USE_LEX_ONLY) {printf("FALSE");} else {return yy::parser::make_FALSE(yytext);}}
"this"             {if(USE_LEX_ONLY) {printf("THIS");} else {return yy::parser::make_THIS(yytext);}}
"new"              {if(USE_LEX_ONLY) {printf("NEW");} else {return yy::parser::make_NEW(yytext);}}
"!"                {if(USE_LEX_ONLY) {printf("NOT");} else {return yy::parser::make_NOT(yytext);}}
"&&"               {if(USE_LEX_ONLY) {printf("AND");} else {return yy::parser::make_AND(yytext);}}
"||"               {if(USE_LEX_ONLY) {printf("OR");} else {return yy::parser::make_OR(yytext);}}
"<"                {if(USE_LEX_ONLY) {printf("LESS_THAN");} else {return yy::parser::make_LESS_THAN(yytext);}}
">"                {if(USE_LEX_ONLY) {printf("GREATER_THAN");} else {return yy::parser::make_GREATER_THAN(yytext);}}
"=="               {if(USE_LEX_ONLY) {printf("EQUAL");} else {return yy::parser::make_EQUAL(yytext);}}
"+"                {if(USE_LEX_ONLY) {printf("ADD");} else {return yy::parser::make_ADD(yytext);}}
"-"                {if(USE_LEX_ONLY) {printf("SUBTRACT");} else {return yy::parser::make_SUBTRACT(yytext);}}
"*"                {if(USE_LEX_ONLY) {printf("MULTIPLY");} else {return yy::parser::make_MULTIPLY(yytext);}}
"/"                {if(USE_LEX_ONLY) {printf("DIVIDE");} else {return yy::parser::make_DIVIDE(yytext);}}
"length"           {if(USE_LEX_ONLY) {printf("LENGTH");} else {return yy::parser::make_LENGTH(yytext);}}

"{"                {if(USE_LEX_ONLY) {printf("LEFT_BRACE");} else {return yy::parser::make_LEFT_BRACE(yytext);}}
"}"                {if(USE_LEX_ONLY) {printf("RIGHT_BRACE");} else {return yy::parser::make_RIGHT_BRACE(yytext);}}
"("                {if(USE_LEX_ONLY) {printf("LEFT_PARENTHESIS");} else {return yy::parser::make_LEFT_PARENTHESIS(yytext);}}
")"                {if(USE_LEX_ONLY) {printf("RIGHT_PARENTHESIS");} else {return yy::parser::make_RIGHT_PARENTHESIS(yytext);}}
"["                {if(USE_LEX_ONLY) {printf("LEFT_BRACKET");} else {return yy::parser::make_LEFT_BRACKET(yytext);}}
"]"                {if(USE_LEX_ONLY) {printf("RIGHT_BRACKET");} else {return yy::parser::make_RIGHT_BRACKET(yytext);}}
"."                {if(USE_LEX_ONLY) {printf("DOT");} else {return yy::parser::make_DOT(yytext);}}
","                {if(USE_LEX_ONLY) {printf("COMMA");} else {return yy::parser::make_COMMA(yytext);}}
";"                {if(USE_LEX_ONLY) {printf("SEMICOLON");} else {return yy::parser::make_SEMICOLON(yytext);}}
"="                {if(USE_LEX_ONLY) {printf("ASSIGN");} else {return yy::parser::make_ASSIGN(yytext);}}

[a-zA-Z][a-zA-Z0-9_]* {if(USE_LEX_ONLY) {printf("IDENTIFIER");} else {return yy::parser::make_IDENTIFIER(yytext);}}
0|-?[1-9][0-9]* {if(USE_LEX_ONLY) {printf("INTEGER_LITERAL");} else {return yy::parser::make_INTEGER_LITERAL(yytext);}}

"//".*            {if(USE_LEX_ONLY) {printf("COMMENT");} else {return yy::parser::make_COMMENT(yytext);}}

[ \t\r\n]+         /* ignore whitespace */;
.                  {if(USE_LEX_ONLY) {printf("ERROR");} else {return yy::parser::make_ERROR(yytext);}}

<<EOF>>                 {if(USE_LEX_ONLY) {printf("EOF");} else {return yy::parser::make_END(yytext);}}
%%