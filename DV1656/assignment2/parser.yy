%skeleton "lalr1.cc"
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires {
  #include <string>
  #include <list>
  #include "Node.h"
  #include "StringUtils.h"
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
%token <std::string> PUBLIC CLASS VOID MAIN STRING INT BOOLEAN IF ELSE WHILE
%token <std::string> TRUE FALSE THIS NEW NOT AND OR LESS_THAN GREATER_THAN EQUAL
%token <std::string> ADD SUBTRACT MULTIPLY DIVIDE LENGTH LEFT_BRACE RIGHT_BRACE
%token <std::string> LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET RIGHT_BRACKET
%token <std::string> DOT COMMA SEMICOLON ASSIGN IDENTIFIER INTEGER_LITERAL
%token <std::string> STATIC RETURN SYSTEM_OUT_PRINTLN EXTENDS
%token END 0 "end of file"

// Non-terminal type definitions
%type <std::string> Type Identifier TypeOrIdentifier
%type <Node*> Goal MainClass ClassDeclaration VarDeclaration MethodDeclaration MethodBodyItem ClassBodyItem MainMethod
%type <Node*> Statement Expression Parameter
%type <std::list<Node*>> ClassDeclarationList
%type <std::list<Node*>> StatementList ExpressionList ParameterList MethodBody ClassBody

%left OR
%left AND
%nonassoc LESS_THAN GREATER_THAN
%left ADD SUBTRACT
%left MULTIPLY DIVIDE
%right NOT
%left DOT
%left LEFT_BRACKET
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
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
  : PUBLIC CLASS Identifier LEFT_BRACE ClassBody RIGHT_BRACE {
    $$ = new Node("MainClass", $3, yylineno);
   add_children($$, $5);
  }
;

MainMethod
  : PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE MethodBody RIGHT_BRACE {
    $$ = new Node("void", "main", yylineno);
    add_child($$, new Node("string[]", $9, yylineno));
    add_children($$, $12);  // $12 is MethodBody
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
  : CLASS Identifier LEFT_BRACE ClassBody RIGHT_BRACE {
    $$ = new Node("ClassDeclaration", $2, yylineno);
    add_children($$, $4);
  }
  ;



VarDeclaration
  : TypeOrIdentifier Identifier SEMICOLON {
    $$ = new Node("VarDeclaration", $2, yylineno);
    add_child($$, new Node($1, $2, yylineno));
  }
  | TypeOrIdentifier Identifier ASSIGN Expression SEMICOLON {
        $$ = new Node("VarDeclaration", $2, yylineno);
        add_child($$, new Node($1, $2, yylineno));
      }
 ;

TypeOrIdentifier
  : Type { $$ = $1; }
  | Identifier { $$ = $1; }

MethodDeclaration
  : PUBLIC TypeOrIdentifier Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE MethodBody RETURN Expression SEMICOLON RIGHT_BRACE {

    std::vector<std::string> typeName = {$2,$3};
    $$ = new Node("MethodDeclaration", StringUtils::join(typeName, ":"), yylineno);
    Node* params = new Node("ParameterList", $3, yylineno);
    add_children(params, $5);
    add_child($$, params);
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

ClassBody
  : ClassBodyItem ClassBody {
      $$ = $2;
      $$.push_front($1);
    }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

ClassBodyItem
  : VarDeclaration { $$ = $1;}

  | MethodDeclaration { $$ = $1; }

  | MainMethod { $$ = $1; }
  ;

ParameterList
  : Parameter { $$ = std::list<Node*>{$1}; }
  | Parameter COMMA ParameterList { $$ = $3; $$.push_front($1); }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

Parameter
    : Type Identifier {
    $$ = new Node($1,$2, yylineno);
    }
    | Identifier Identifier {
    $$ = new Node($1,$2, yylineno);
    }

Type
  : INT LEFT_BRACKET RIGHT_BRACKET { $$ = "int[]"; }
  | BOOLEAN { $$ = "bool"; }
  | INT { $$ = "int" ;}
  | STRING LEFT_BRACKET RIGHT_BRACKET  { $$ = "string[]"; }
  ;

StatementList
  : Statement StatementList { $$ = $2; $$.push_front($1); }
  | /* empty */ { $$ = std::list<Node*>(); }
  ;

Statement
  : LEFT_BRACE StatementList RIGHT_BRACE {
    $$ = new Node("BlockStatement", "Block", yylineno);
    add_children($$, $2);
  }
  | IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement {
    $$ = new Node("If", "TMP", yylineno);
    add_child($$, $3);
    add_child($$, $5);
  }
  | IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement {
    $$ = new Node("IfElse", "TMP", yylineno);
    add_child($$, $3);
    add_child($$, $5);
    add_child($$, $7);
  }
  | WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement {
    $$ = new Node("WhileLoop", "TMP", yylineno);
    add_child($$, $3);
    add_child($$, $5);
  }
  | SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON {
    $$ = new Node("PrintLn", "TMP", yylineno);
    add_child($$,$3);
  }
  | Identifier ASSIGN Expression SEMICOLON {
    $$ = new Node("Assignment", $1, yylineno);
    add_child($$, $3);
  }
  | Identifier LEFT_BRACKET Expression RIGHT_BRACKET ASSIGN Expression SEMICOLON {
    $$ = new Node("ArrayAssignment", $1, yylineno);
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
    $$ = new Node("Comparison", "And", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression OR Expression {
    $$ = new Node("Comparison", "Or", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression LESS_THAN Expression {
    $$ = new Node("Comparison", "LessThan", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression GREATER_THAN Expression {
    $$ = new Node("Comparison", "GreaterThan", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression ADD Expression {
    $$ = new Node("Operation", "Add", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression SUBTRACT Expression {
    $$ = new Node("Operation", "Subtract", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression MULTIPLY Expression {
    $$ = new Node("Operation", "Multiply", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression EQUAL Expression {
    $$ = new Node("Comparison", "Equal", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression DIVIDE Expression {
    $$ = new Node("Operation", "Devide", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression LEFT_BRACKET Expression RIGHT_BRACKET {
    $$ = new Node("Operation", "ArrayLookup", yylineno);
    add_child($$, $1);
    add_child($$, $3);
  }
  | Expression DOT LENGTH {
    $$ = new Node("Operation", "ArrayLength", yylineno);
    add_child($$, $1);
  }
  | Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS {
    $$ = new Node("Expression", $3, yylineno);
    add_child($$, $1);
    add_children($$, $5);
  }
  | INTEGER_LITERAL {
    $$ = new Node("Number", $1, yylineno);
  }
  | TRUE {
    $$ = new Node("TrueOrFalse", "True", yylineno);
  }
  | FALSE {
    $$ = new Node("TrueOrFalse", "False", yylineno);
  }
  | Identifier {
    $$ = new Node("Expression", $1, yylineno);
  }
  | THIS {
    $$ = new Node("This", $1, yylineno);
  }
  | NEW INT LEFT_BRACKET Expression RIGHT_BRACKET {
    $$ = new Node("NewIntArray", "TMP", yylineno);
    add_child($$, $4);
  }
  | NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS {
    $$ = new Node("NewInstance", $2, yylineno);
  }
  | NOT Expression {
    $$ = new Node("Not", "TMP", yylineno);
    add_child($$, $2);
  }
  | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS {
    $$ = $2;
  }
  ;

Identifier
  : IDENTIFIER {
    $$ = $1;
  }
  ;

%%

