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
%token <std::string> PUBLIC CLASS VOID MAIN STRING INT STATIC BOOLEAN IF ELSE WHILE PRINT TRUE FALSE THIS NEW NOT AND ERROR OR COMMA IDENTIFIER INTEGER_LITERAL COMMENT LESS_THAN GREATER_THAN EQUAL ADD SUBTRACT MULTIPLY DIVIDE LENGTH LEFT_BRACE RIGHT_BRACE LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET RIGHT_BRACKET DOT SEMICOLON ASSIGN
%token END 0 "end of file"

//definition of operator precedence. See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl
%left PLUSOP MINUSOP
%left MULTOP

// definition of the production rules. All production rules are of type Node
%type <Node *> root expression factor

%%
root:       expression {root = $1;};


expression: expression ADD expression {      /*
Create a subtree that corresponds to the AddExpression
The root of the subtree is AddExpression
The childs of the AddExpression subtree are the left hand side (expression accessed through $1) and right hand side of the expression (expression accessed through $3)
*/
$$ = new Node("AddExpression", "", yylineno);
$$->children.push_back($1);
$$->children.push_back($3);
/* printf("r1 "); */
}
| expression SUBTRACT expression {
$$ = new Node("SubExpression", "", yylineno);
$$->children.push_back($1);
$$->children.push_back($3);
/* printf("r2 "); */
}
| expression MULTIPLY expression {
$$ = new Node("MultExpression", "", yylineno);
$$->children.push_back($1);
$$->children.push_back($3);
/* printf("r3 "); */
}
| expression DIVIDE expression {
$$ = new Node("DevideExpression", "", yylineno);
$$->children.push_back($1);
$$->children.push_back($3);
/* printf("r4 "); */
}
| factor 
{$$ = $1; /* printf("r5 ");*/}
;

factor:INT{  $$ = new Node("Int", $1, yylineno); }| LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = $2; };

MainClass: PUBLIC CLASS IDENTIFIER LEFT_BRACE PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET IDENTIFIER RIGHT_PARENTHESIS LEFT_BRACE statement RIGHT_BRACE RIGHT_BRACE { $$ = new Node("MainClass", "", yylineno);
 $$->children.push_back($3);
  $$->children.push_back($11);
    $$->children.push_back($15); };

ClassDeclaration: 
    CLASS IDENTIFIER LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE { 
        /* Create a ClassDeclaration node */
        $$ = new Node("ClassDeclaration", "", yylineno);
        /* Add children nodes for Identifier, VarDeclarationList, and MethodDeclarationList */
        $$->children.push_back(new Node("Identifier", $2, yylineno));
        $$->children.push_back($4);
        $$->children.push_back($5);
    };

VarDeclarationList: 
    /* Empty */ { $$ = new Node("VarDeclarationList", "", yylineno); }
    | VarDeclarationList VarDeclaration { 
        $$ = $1;
        $$->children.push_back($2);
    };

method_declaration: 
  PUBLIC type IDENTIFIER LEFT_PARENTHESIS 
    (type IDENTIFIER (COMMA type IDENTIFIER)*)? 
  RIGHT_PARENTHESIS LEFT_BRACE 
    (var_declaration | statement)* 
    RETURN expression SEMICOLON RIGHT_BRACE 
  { 
    /*
      Create a subtree that corresponds to the MethodDeclaration
      The root of the subtree is MethodDeclaration
      The child nodes of the MethodDeclaration subtree are the various components of the method declaration such as its return type, identifier, parameter list, and the body of the method.
    */
    $$ = new Node("MethodDeclaration", "", yylineno);
    $$->children.push_back(new Node("ReturnType", $2, yylineno));
    $$->children.push_back(new Node("Identifier", $3, yylineno));
    $$->children.push_back($5);
    $$->children.push_back($9);
  };


goal: MAIN LEFT_PARENTHESIS CLASS RIGHT_PARENTHESIS LEFT_BRACE expression RIGHT_BRACE { $$ = $5; };