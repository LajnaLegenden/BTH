%{
#include "parser.tab.hh"
#include <string>
#include "global.h"

int lexical_errors = 0;

static yy::location loc;

#define YY_DECL yy::parser::symbol_type yylex()

#define YY_USER_ACTION  loc.columns(yyleng);
%}

%option noyywrap nounput noinput batch debug yylineno

%{
  // Code run each time yylex is called.
  # define YY_USER_INIT  loc.initialize();
%}

%%
"//".*"\n"                        { /* Comment */ }
[ \t\r]                           { /* Ignore whitespace */ }
\n                                { loc.lines(); loc.step(); }
"public"          { return yy::parser::make_PUBLIC(yytext,loc); }
"class"           { return yy::parser::make_CLASS(yytext,loc); }
"static"          { return yy::parser::make_STATIC(yytext,loc); }
"void"            { return yy::parser::make_VOID(yytext,loc); }
"main"            { return yy::parser::make_MAIN(yytext,loc); }
"String"          { return yy::parser::make_STRING(yytext,loc); }
"return"          { return yy::parser::make_RETURN(yytext,loc); }
"int"             { return yy::parser::make_INT(yytext,loc); }
"extends"         { return yy::parser::make_EXTENDS(yytext,loc); }
"boolean"         { return yy::parser::make_BOOLEAN(yytext,loc); }
"if"              { return yy::parser::make_IF(yytext,loc); }
"else"            { return yy::parser::make_ELSE(yytext,loc); }
"while"           { return yy::parser::make_WHILE(yytext,loc); }
"System.out.println" { return yy::parser::make_SYSTEM_OUT_PRINTLN(yytext,loc); }
"length"          { return yy::parser::make_LENGTH(yytext,loc); }
"true"            { return yy::parser::make_TRUE(yytext,loc); }
"false"           { return yy::parser::make_FALSE(yytext,loc); }
"this"            { return yy::parser::make_THIS(yytext,loc); }
"new"             { return yy::parser::make_NEW(yytext,loc); }
"&&"              { return yy::parser::make_AND(yytext,loc); }
"||"              { return yy::parser::make_OR(yytext,loc); }
"<"               { return yy::parser::make_LESS_THAN(yytext,loc); }
">"               { return yy::parser::make_GREATER_THAN(yytext,loc); }
"=="              { return yy::parser::make_EQUAL(yytext,loc); }
"+"               { return yy::parser::make_ADD(yytext,loc); }
"-"               { return yy::parser::make_SUBTRACT(yytext,loc); }
"*"               { return yy::parser::make_MULTIPLY(yytext,loc); }
"/"               { return yy::parser::make_DIVIDE(yytext,loc); }
"!"               { return yy::parser::make_NOT(yytext,loc); }
"="               { return yy::parser::make_ASSIGN(yytext,loc); }
"."               { return yy::parser::make_DOT(yytext,loc); }
","               { return yy::parser::make_COMMA(yytext,loc); }
";"               { return yy::parser::make_SEMICOLON(yytext,loc); }
"("               { return yy::parser::make_LEFT_PARENTHESIS(yytext,loc); }
")"               { return yy::parser::make_RIGHT_PARENTHESIS(yytext,loc); }
"["               { return yy::parser::make_LEFT_BRACKET(yytext,loc); }
"]"               { return yy::parser::make_RIGHT_BRACKET(yytext,loc); }
"{"               { return yy::parser::make_LEFT_BRACE(yytext,loc); }
"}"               { return yy::parser::make_RIGHT_BRACE(yytext,loc); }
[a-zA-Z][a-zA-Z0-9_]* { return yy::parser::make_IDENTIFIER(yytext,loc); }
[0-9]+            { return yy::parser::make_INTEGER_LITERAL(yytext,loc); }
.                 {
    fprintf(stderr, "Error: Unknown character '%c' (ASCII: %d) at line %d\n", yytext[0], (int)yytext[0], yylineno);
    lexical_errors++;
    return yy::parser::make_YYUNDEF(loc);
}
<<EOF>>           { return yy::parser::make_END(loc); }
%%