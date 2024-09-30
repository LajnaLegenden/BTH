%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
}

%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;
}

%token <std::string> PUBLIC CLASS VOID MAIN STRING INT BOOLEAN IF ELSE WHILE PRINT
%token <std::string> TRUE FALSE THIS NEW NOT AND OR LESS_THAN GREATER_THAN EQUAL
%token <std::string> ADD SUBTRACT MULTIPLY DIVIDE LENGTH LEFT_BRACE RIGHT_BRACE
%token <std::string> LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET RIGHT_BRACKET
%token <std::string> DOT COMMA SEMICOLON ASSIGN IDENTIFIER INTEGER_LITERAL
%token <std::string> STATIC RETURN SYSTEM_OUT_PRINTLN
%token <std::string> COMMENT ERROR
%token END 0 "end of file"

%type <Node *> Goal MainClass ClassDeclarationList ClassDeclaration VarDeclarationList MethodDeclarationList
%type <Node *> VarDeclaration MethodDeclaration Type Statement StatementList Expression ExpressionList
%type <Node *> Identifier ParameterList Parameter

%start Goal

%%

Goal
    : MainClass ClassDeclarationList END { $$ = new Node("Goal", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); root = $$; }
    ;

MainClass
    : PUBLIC CLASS Identifier LEFT_BRACE PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE StatementList RIGHT_BRACE RIGHT_BRACE
    { $$ = new Node("MainClass", "", yylineno); $$->children.push_back($3); $$->children.push_back($13); $$->children.push_back($16); }
    ;

ClassDeclarationList
    : ClassDeclaration ClassDeclarationList { $$ = new Node("ClassDeclarationList", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); }
    | /* empty */ { $$ = new Node("ClassDeclarationList", "Empty", yylineno); }
    ;

ClassDeclaration
    : CLASS Identifier LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE
    { $$ = new Node("ClassDeclaration", "", yylineno); $$->children.push_back($2); $$->children.push_back($4); $$->children.push_back($5); }
    ;

VarDeclarationList
    : VarDeclaration VarDeclarationList { $$ = new Node("VarDeclarationList", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); }
    | /* empty */ { $$ = new Node("VarDeclarationList", "Empty", yylineno); }
    ;

MethodDeclarationList
    : MethodDeclaration MethodDeclarationList { $$ = new Node("MethodDeclarationList", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); }
    | /* empty */ { $$ = new Node("MethodDeclarationList", "Empty", yylineno); }
    ;

VarDeclaration
    : Type Identifier SEMICOLON { $$ = new Node("VarDeclaration", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); }
    ;

MethodDeclaration
    : PUBLIC Type Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE VarDeclarationList StatementList RETURN Expression SEMICOLON RIGHT_BRACE
    { $$ = new Node("MethodDeclaration", "", yylineno); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); $$->children.push_back($9); $$->children.push_back($11); }
    ;

Type
    : INT LEFT_BRACKET RIGHT_BRACKET { $$ = new Node("Type", "int[]", yylineno); }
    | BOOLEAN { $$ = new Node("Type", "boolean", yylineno); }
    | INT { $$ = new Node("Type", "int", yylineno); }
    | Identifier { $$ = $1; }
    ;

ParameterList
    : Type Identifier Parameter { $$ = new Node("ParameterList", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); $$->children.push_back($3); }
    | /* empty */ { $$ = new Node("ParameterList", "Empty", yylineno); }
    ;

Parameter
    : COMMA Type Identifier Parameter { $$ = new Node("Parameter", "", yylineno); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($4); }
    | /* empty */ { $$ = new Node("Parameter", "Empty", yylineno); }
    ;

StatementList
    : Statement StatementList { $$ = new Node("StatementList", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); }
    | /* empty */ { $$ = new Node("StatementList", "Empty", yylineno); }
    ;

Statement
    : LEFT_BRACE StatementList RIGHT_BRACE { $$ = $2; }
    | IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement
    { $$ = new Node("IfStatement", "", yylineno); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($7); }
    | IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
    { $$ = new Node("IfStatement", "", yylineno); $$->children.push_back($3); $$->children.push_back($5); }
    | WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
    { $$ = new Node("WhileStatement", "", yylineno); $$->children.push_back($3); $$->children.push_back($5); }
    | SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON
    { $$ = new Node("PrintStatement", "", yylineno); $$->children.push_back($3); }
    | Identifier ASSIGN Expression SEMICOLON
    { $$ = new Node("AssignStatement", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Identifier LEFT_BRACKET Expression RIGHT_BRACKET ASSIGN Expression SEMICOLON
    { $$ = new Node("ArrayAssignStatement", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($6); }
    ;

Expression
    : Expression AND Expression { $$ = new Node("AndExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression OR Expression { $$ = new Node("OrExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression LESS_THAN Expression { $$ = new Node("LessThanExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression GREATER_THAN Expression { $$ = new Node("GreaterThanExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression EQUAL Expression { $$ = new Node("EqualExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression ADD Expression { $$ = new Node("AddExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression SUBTRACT Expression { $$ = new Node("SubtractExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression MULTIPLY Expression { $$ = new Node("MultiplyExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression DIVIDE Expression { $$ = new Node("DivideExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression LEFT_BRACKET Expression RIGHT_BRACKET { $$ = new Node("ArrayAccessExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); }
    | Expression DOT LENGTH { $$ = new Node("ArrayLengthExpression", "", yylineno); $$->children.push_back($1); }
    | Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS { $$ = new Node("MethodCallExpression", "", yylineno); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($5); }
    | INTEGER_LITERAL { $$ = new Node("IntegerLiteral", $1, yylineno); }
    | TRUE { $$ = new Node("BooleanLiteral", "true", yylineno); }
    | FALSE { $$ = new Node("BooleanLiteral", "false", yylineno); }
    | Identifier { $$ = $1; }
    | THIS { $$ = new Node("ThisExpression", "", yylineno); }
    | NEW INT LEFT_BRACKET Expression RIGHT_BRACKET { $$ = new Node("NewIntArrayExpression", "", yylineno); $$->children.push_back($4); }
    | NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS { $$ = new Node("NewObjectExpression", "", yylineno); $$->children.push_back($2); }
    | NOT Expression { $$ = new Node("NotExpression", "", yylineno); $$->children.push_back($2); }
    | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS { $$ = $2; }
    ;

ExpressionList
    : Expression ExpressionList { $$ = new Node("ExpressionList", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); }
    | COMMA Expression ExpressionList { $$ = new Node("ExpressionList", "", yylineno); $$->children.push_back($2); $$->children.push_back($3); }
    | /* empty */ { $$ = new Node("ExpressionList", "Empty", yylineno); }
    ;

Identifier
    : IDENTIFIER { $$ = new Node("Identifier", $1, yylineno); }
    ;

%%
