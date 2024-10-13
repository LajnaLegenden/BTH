%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires {
  #include <string>
  #include <list>
  #include "Node.h"
  #define USE_LEX_ONLY false
}

%code {
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;
  int cnt = 0;

  void add_child(Node* parent, Node* child) {
    parent->children.push_back(child);
  }

  void add_children(Node* parent, const std::list<Node*>& children) {
    parent->children.insert(parent->children.end(), children.begin(), children.end());
  }
}

// Token definitions
%token <std::string> PUBLIC CLASS VOID MAIN STRING INT BOOLEAN IF ELSE WHILE PRINT
%token <std::string> TRUE FALSE THIS NEW NOT AND OR LESS_THAN GREATER_THAN EQUAL
%token <std::string> ADD SUBTRACT MULTIPLY DIVIDE LENGTH LEFT_BRACE RIGHT_BRACE
%token <std::string> LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET RIGHT_BRACKET
%token <std::string> DOT COMMA SEMICOLON ASSIGN IDENTIFIER INTEGER_LITERAL
%token <std::string> STATIC RETURN SYSTEM_OUT_PRINTLN EXTENDS
%token <std::string> COMMENT ERROR
%token END 0 "end of file"

// Non-terminal type definitions
%type <Node*> Goal MainClass ClassDeclaration VarDeclaration MethodDeclaration Type MethodBodyItem
%type <Node*> Statement Expression Identifier
%type <std::list<Node*>> ClassDeclarationList MethodDeclarationList VarDeclarationList
%type <std::list<Node*>> StatementList ExpressionList ParameterList MethodBody

%start Goal

%%

Goal
  : MainClass ClassDeclarationList { 
    $$ = new Node("Goal", "", yylineno);
    add_child($$, $1);
    add_children($$, $2);
    root = $$;
  }
  ;

MainClass
  : PUBLIC CLASS Identifier LEFT_BRACE PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE Statement RIGHT_BRACE RIGHT_BRACE { 
    $$ = new Node("MainClass", "", yylineno);
    add_child($$, $3);
    add_child($$, $13);
    add_child($$, $16);
  }
  ;

ClassDeclarationList
  : ClassDeclaration ClassDeclarationList { 
    $$ = $2;
    $$.push_front($1);
  }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

ClassDeclaration
  : CLASS Identifier LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE {
    $$ = new Node("ClassDeclaration", "", yylineno);
    add_child($$, $2);
    add_children($$, $4);
    add_children($$, $5);
  }
  | CLASS Identifier EXTENDS Identifier LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE {
    $$ = new Node("ClassDeclaration", "", yylineno);
    add_child($$, $2);
    add_child($$, $4);
    add_children($$, $6);
    add_children($$, $7);
  }
  ;

VarDeclarationList
  : VarDeclaration { $$ = std::list<Node*>{$1}; }
  | VarDeclarationList VarDeclaration { $$ = $1; $$.push_back($2); }
  ;



VarDeclaration
  : Type Identifier SEMICOLON {
    $$ = new Node("VarDeclaration", $2->value, yylineno);
    add_child($$, $1);
    add_child($$, $2);
  }
  | Type Identifier EQUAL Expression SEMICOLON {
        $$ = new Node("VarDeclaration", $2->value, yylineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $4);
      }
  ;

MethodDeclarationList
  : MethodDeclaration MethodDeclarationList { $$ = $2; $$.push_front($1); }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

MethodDeclaration
  : PUBLIC Type Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE MethodBody RETURN Expression SEMICOLON RIGHT_BRACE {
    $$ = new Node("MethodDeclaration", "", yylineno);
    add_child($$, $2);
    add_child($$, $3);
    add_children($$, $5);
    add_children($$, $8);  // Add all children from MethodBody
    add_child($$, $10);    // Add the return expression
  }
  ;

MethodBody
  : MethodBodyItem MethodBody {
    $$ = $2;
    $$.push_front($1);
  }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

MethodBodyItem
  : VarDeclaration { $$ = $1; }
  | Statement { $$ = $1; }
  ;


ParameterList
  : Type Identifier { $$ = std::list<Node*>{$1, $2}; }
  | Type Identifier COMMA ParameterList { $$ = $4; $$.push_front($2); $$.push_front($1); }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

Type
  : INT LEFT_BRACKET RIGHT_BRACKET { $$ = new Node("Type", "Int[]", yylineno); }
  | BOOLEAN { $$ = new Node("Type", "Boolean", yylineno); }
  | INT { $$ = new Node("Type", "Int", yylineno); }
  | Identifier { $$ = new Node("Type", $1->value, yylineno); }
  ;

StatementList
  : Statement StatementList { $$ = $2; $$.push_front($1); }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

Statement
  : LEFT_BRACE StatementList RIGHT_BRACE {
    $$ = new Node("Statement", "", yylineno);
    add_children($$, $2);
  }
  | IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement {
    $$ = new Node("Statement", "If", yylineno);
    add_child($$, $3);
    add_child($$, $5);
    add_child($$, $7);
  }
  | IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement {
      $$ = new Node("Statement", "If", yylineno);
      add_child($$, $3);
      add_child($$, $5);
    }
  | WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement {
    $$ = new Node("Statement", "While", yylineno);
    add_child($$, $3);
    add_child($$, $5);
  }
  | SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON {
    $$ = new Node("Statement", "Println", yylineno);
    add_child($$, $3);
  }
  | Identifier ASSIGN Expression SEMICOLON {
    $$ = new Node("Statement", "Assign", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Identifier LEFT_BRACKET Expression RIGHT_BRACKET ASSIGN Expression SEMICOLON {
    $$ = new Node("Statement", "ArrayAssign", yylineno);
    add_child($$, $1);
    add_child($$, $3);
    add_child($$, $6);
  }
  ;

ExpressionList
  : Expression { $$ = std::list<Node*>{$1}; }
  | Expression COMMA ExpressionList { $$ = $3; $$.push_front($1); }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

Expression
  : Expression AND Expression {
    $$ = new Node("Expression", "And", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression LESS_THAN Expression {
    $$ = new Node("Expression", "LessThan", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression ADD Expression {
    $$ = new Node("Expression", "Add", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression SUBTRACT Expression {
    $$ = new Node("Expression", "Subtract", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression MULTIPLY Expression {
    $$ = new Node("Expression", "Multiply", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression LEFT_BRACKET Expression RIGHT_BRACKET {
    $$ = new Node("Expression", "ArrayLookup", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression DOT LENGTH {
    $$ = new Node("Expression", "ArrayLength", yylineno);
    add_child($$, $1);
  }
  | Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS {
    $$ = new Node("Expression", "Call", yylineno);
    add_child($$, $1);
    add_child($$, $3);
    add_children($$, $5);
  }
  | INTEGER_LITERAL {
    $$ = new Node("Expression", $1, yylineno);
  }
  | TRUE {
    $$ = new Node("Expression", "True", yylineno);
  }
  | FALSE {
    $$ = new Node("Expression", "False", yylineno);
  }
  | Identifier {
    $$ = new Node("Expression", $1->value, yylineno);
  }
  | THIS {
    $$ = new Node("Expression", "This", yylineno);
  }
  | NEW INT LEFT_BRACKET Expression RIGHT_BRACKET {
    $$ = new Node("Expression", "NewArray", yylineno);
    add_child($$, $4);
  }
  | NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS {
    $$ = new Node("Expression", "NewObject", yylineno);
    add_child($$, $2);
  }
  | NOT Expression {
    $$ = new Node("Expression", "Not", yylineno);
    add_child($$, $2);
  }
  | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS {
    $$ = $2;
  }
  ;

Identifier
  : IDENTIFIER {
    $$ = new Node("Identifier", $1, yylineno);
  }
  ;

%%

