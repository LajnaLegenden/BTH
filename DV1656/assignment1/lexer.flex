%{
#include "parser.tab.hh"
#define YY_DECL yy::parser::symbol_type yylex()
#include "global.h"
int lexical_errors = 0;
%}

%option yylineno

%%
"//".*"\n"                        { /* Comment */ }
"/*"(.|"\n")*"*/"                 { /* Multiline Comment */ }
[ \t\r]                           { /* Ignore whitespace */ }
\n                                { /* Newline */ }
"public"          { return yy::parser::make_PUBLIC(yytext); }
"class"           { return yy::parser::make_CLASS(yytext); }
"static"          { return yy::parser::make_STATIC(yytext); }
"void"            { return yy::parser::make_VOID(yytext); }
"main"            { return yy::parser::make_MAIN(yytext); }
"String"          { return yy::parser::make_STRING(yytext); }
"return"          { return yy::parser::make_RETURN(yytext); }
"int"             { return yy::parser::make_INT(yytext); }
"extends"         { return yy::parser::make_EXTENDS(yytext); }
"boolean"         { return yy::parser::make_BOOLEAN(yytext); }
"if"              { return yy::parser::make_IF(yytext); }
"else"            { return yy::parser::make_ELSE(yytext); }
"while"           { return yy::parser::make_WHILE(yytext); }
"System.out.println" { return yy::parser::make_SYSTEM_OUT_PRINTLN(yytext); }
"length"          { return yy::parser::make_LENGTH(yytext); }
"true"            { return yy::parser::make_TRUE(yytext); }
"false"           { return yy::parser::make_FALSE(yytext); }
"this"            { return yy::parser::make_THIS(yytext); }
"new"             { return yy::parser::make_NEW(yytext); }
"&&"              { return yy::parser::make_AND(yytext); }
"||"              { return yy::parser::make_OR(yytext); }
"<"               { return yy::parser::make_LESS_THAN(yytext); }
">"               { return yy::parser::make_GREATER_THAN(yytext); }
"=="              { return yy::parser::make_EQUAL(yytext); }
"+"               { return yy::parser::make_ADD(yytext); }
"-"               { return yy::parser::make_SUBTRACT(yytext); }
"*"               { return yy::parser::make_MULTIPLY(yytext); }
"/"               { return yy::parser::make_DIVIDE(yytext); }
"!"               { return yy::parser::make_NOT(yytext); }
"="               { return yy::parser::make_ASSIGN(yytext); }
"."               { return yy::parser::make_DOT(yytext); }
","               { return yy::parser::make_COMMA(yytext); }
";"               { return yy::parser::make_SEMICOLON(yytext); }
"("               { return yy::parser::make_LEFT_PARENTHESIS(yytext); }
")"               { return yy::parser::make_RIGHT_PARENTHESIS(yytext); }
"["               { return yy::parser::make_LEFT_BRACKET(yytext); }
"]"               { return yy::parser::make_RIGHT_BRACKET(yytext); }
"{"               { return yy::parser::make_LEFT_BRACE(yytext); }
"}"               { return yy::parser::make_RIGHT_BRACE(yytext); }
[a-zA-Z][a-zA-Z0-9_]* { return yy::parser::make_IDENTIFIER(yytext); }
[0-9]+            { return yy::parser::make_INTEGER_LITERAL(yytext); }
.                 {
    fprintf(stderr, "Error: Unknown character '%c' (ASCII: %d) at line %d\n", yytext[0], (int)yytext[0], yylineno);
    lexical_errors++;
    return yy::parser::make_YYUNDEF();
}

%%

int yywrap() {
    return 1;
}