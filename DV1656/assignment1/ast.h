#ifndef AST_H
#define AST_H

#include <vector>
#include <string>

enum node_type {
  NT_PROGRAM,
  NT_CLASS_DECL,
  NT_VAR_DECL,
  NT_METHOD_DECL,
  NT_ARG_DECL,
  NT_BLOCK,
  NT_IF_ELSE,
  NT_IF,
  NT_WHILE,
  NT_SYSTEM_OUT_PRINTLN,
  NT_RETURN,
  NT_ASSIGN,
  NT_ARRAY_ACCESS,
  NT_METHOD_INVOCATION,
  NT_LENGTH,
  NT_NOT,
  NT_MINUS,
  NT_PLUS,
  NT_TIMES,
  NT_DIV,
  NT_MOD,
  NT_EQ,
  NT_NEQ,
  NT_LT,
  NT_LE,
  NT_GT,
  NT_GE,
  NT_AND,
  NT_OR,
  NT_INT_LITERAL,
  NT_BOOLEAN_LITERAL,
  NT_NEW_INT_ARRAY,
  NT_NEW_OBJECT,
  NT_THIS,
  NT_ID
};

struct node {
  node_type type;
};

struct program : node {
  std::vector<node *> classes;
};

struct class_decl : node {
  std::string id;
  std::vector<node *> members;
};

struct var_decl : node {
  std::string id;
  std::string type;
};

struct method_decl : node {
  std::string id;
  std::string type;
  std::vector<node *> args;
  std::vector<node *> statements;
};

struct arg_decl : node {
  std::string id;
  std::string type;
};

struct block : node {
  std::vector<node *> statements;
};

struct if_else : node {
  node *condition;
  node *if_statement;
  node *else_statement;
};

struct if_ : node {
  node *condition;
  node *statement;
};

struct while_ : node {
  node *condition;
  node *statement;
};

struct system_out_println : node {
  node *expression;
};

struct return_ : node {
  node *expression;
};

struct assign : node {
  std::string id;
  node *expression;
};

struct array_access : node {
  std::string id;
  node *expression;
};

struct method_invocation : node {
  std::string id;
  std::vector<node *> args;
};

struct length : node {
  std::string id;
};

struct not_ : node {
  node *expression;
};

struct minus : node {
  node *expression;
};

struct plus : node {
  node *left;
  node *right;
};
