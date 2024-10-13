// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 14 "parser.yy"

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

#line 63 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 136 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
        value.YY_MOVE_OR_COPY< Node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_ExpressionList: // ExpressionList
        value.YY_MOVE_OR_COPY< std::list<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUBTRACT: // SUBTRACT
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_LEFT_BRACE: // LEFT_BRACE
      case symbol_kind::S_RIGHT_BRACE: // RIGHT_BRACE
      case symbol_kind::S_LEFT_PARENTHESIS: // LEFT_PARENTHESIS
      case symbol_kind::S_RIGHT_PARENTHESIS: // RIGHT_PARENTHESIS
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_COMMENT: // COMMENT
      case symbol_kind::S_ERROR: // ERROR
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
        value.move< Node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_ExpressionList: // ExpressionList
        value.move< std::list<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUBTRACT: // SUBTRACT
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_LEFT_BRACE: // LEFT_BRACE
      case symbol_kind::S_RIGHT_BRACE: // RIGHT_BRACE
      case symbol_kind::S_LEFT_PARENTHESIS: // LEFT_PARENTHESIS
      case symbol_kind::S_RIGHT_PARENTHESIS: // RIGHT_PARENTHESIS
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_COMMENT: // COMMENT
      case symbol_kind::S_ERROR: // ERROR
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
        value.copy< Node* > (that.value);
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_ExpressionList: // ExpressionList
        value.copy< std::list<Node*> > (that.value);
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUBTRACT: // SUBTRACT
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_LEFT_BRACE: // LEFT_BRACE
      case symbol_kind::S_RIGHT_BRACE: // RIGHT_BRACE
      case symbol_kind::S_LEFT_PARENTHESIS: // LEFT_PARENTHESIS
      case symbol_kind::S_RIGHT_PARENTHESIS: // RIGHT_PARENTHESIS
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_COMMENT: // COMMENT
      case symbol_kind::S_ERROR: // ERROR
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
        value.move< Node* > (that.value);
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_ExpressionList: // ExpressionList
        value.move< std::list<Node*> > (that.value);
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUBTRACT: // SUBTRACT
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_LEFT_BRACE: // LEFT_BRACE
      case symbol_kind::S_RIGHT_BRACE: // RIGHT_BRACE
      case symbol_kind::S_LEFT_PARENTHESIS: // LEFT_PARENTHESIS
      case symbol_kind::S_RIGHT_PARENTHESIS: // RIGHT_PARENTHESIS
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_COMMENT: // COMMENT
      case symbol_kind::S_ERROR: // ERROR
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
        yylhs.value.emplace< Node* > ();
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_ExpressionList: // ExpressionList
        yylhs.value.emplace< std::list<Node*> > ();
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUBTRACT: // SUBTRACT
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_LEFT_BRACE: // LEFT_BRACE
      case symbol_kind::S_RIGHT_BRACE: // RIGHT_BRACE
      case symbol_kind::S_LEFT_PARENTHESIS: // LEFT_PARENTHESIS
      case symbol_kind::S_RIGHT_PARENTHESIS: // RIGHT_PARENTHESIS
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_COMMENT: // COMMENT
      case symbol_kind::S_ERROR: // ERROR
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // Goal: MainClass ClassDeclarationList
#line 52 "parser.yy"
                                   { 
    yylhs.value.as < Node* > () = new Node("Goal", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[0].value.as < std::list<Node*> > ());
    root = yylhs.value.as < Node* > ();
  }
#line 872 "parser.tab.cc"
    break;

  case 3: // MainClass: PUBLIC CLASS Identifier LEFT_BRACE PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE Statement RIGHT_BRACE RIGHT_BRACE
#line 61 "parser.yy"
                                                                                                                                                                                            { 
    yylhs.value.as < Node* > () = new Node("MainClass", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[15].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[5].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 883 "parser.tab.cc"
    break;

  case 4: // ClassDeclarationList: ClassDeclaration ClassDeclarationList
#line 70 "parser.yy"
                                          { 
    yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
    yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
  }
#line 892 "parser.tab.cc"
    break;

  case 5: // ClassDeclarationList: %empty
#line 74 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 898 "parser.tab.cc"
    break;

  case 6: // ClassDeclaration: CLASS Identifier LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE
#line 78 "parser.yy"
                                                                                     {
    yylhs.value.as < Node* > () = new Node("ClassDeclaration", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[2].value.as < std::list<Node*> > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 909 "parser.tab.cc"
    break;

  case 7: // ClassDeclaration: CLASS Identifier EXTENDS Identifier LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE
#line 84 "parser.yy"
                                                                                                        {
    yylhs.value.as < Node* > () = new Node("ClassDeclaration", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[6].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[2].value.as < std::list<Node*> > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 921 "parser.tab.cc"
    break;

  case 8: // VarDeclarationList: VarDeclaration
#line 94 "parser.yy"
                   { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[0].value.as < Node* > ()}; }
#line 927 "parser.tab.cc"
    break;

  case 9: // VarDeclarationList: VarDeclarationList VarDeclaration
#line 95 "parser.yy"
                                      { yylhs.value.as < std::list<Node*> > () = yystack_[1].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node* > ()); }
#line 933 "parser.tab.cc"
    break;

  case 10: // VarDeclaration: Type Identifier SEMICOLON
#line 101 "parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("VarDeclaration", yystack_[1].value.as < Node* > ()->value, yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 943 "parser.tab.cc"
    break;

  case 11: // VarDeclaration: Type Identifier EQUAL Expression SEMICOLON
#line 106 "parser.yy"
                                               {
        yylhs.value.as < Node* > () = new Node("VarDeclaration", yystack_[3].value.as < Node* > ()->value, yylineno);
        add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
        add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
        add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
      }
#line 954 "parser.tab.cc"
    break;

  case 12: // MethodDeclarationList: MethodDeclaration MethodDeclarationList
#line 115 "parser.yy"
                                            { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ()); }
#line 960 "parser.tab.cc"
    break;

  case 13: // MethodDeclarationList: %empty
#line 116 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 966 "parser.tab.cc"
    break;

  case 14: // MethodDeclaration: PUBLIC Type Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE MethodBody RETURN Expression SEMICOLON RIGHT_BRACE
#line 120 "parser.yy"
                                                                                                                                          {
    yylhs.value.as < Node* > () = new Node("MethodDeclaration", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[10].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[9].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[7].value.as < std::list<Node*> > ());
    add_children(yylhs.value.as < Node* > (), yystack_[4].value.as < std::list<Node*> > ());  // Add all children from MethodBody
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());    // Add the return expression
  }
#line 979 "parser.tab.cc"
    break;

  case 15: // MethodBody: MethodBodyItem MethodBody
#line 131 "parser.yy"
                              {
    yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
    yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
  }
#line 988 "parser.tab.cc"
    break;

  case 16: // MethodBody: %empty
#line 135 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 994 "parser.tab.cc"
    break;

  case 17: // MethodBodyItem: VarDeclaration
#line 139 "parser.yy"
                   { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 1000 "parser.tab.cc"
    break;

  case 18: // MethodBodyItem: Statement
#line 140 "parser.yy"
              { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 1006 "parser.tab.cc"
    break;

  case 19: // ParameterList: Type Identifier
#line 145 "parser.yy"
                    { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[1].value.as < Node* > (), yystack_[0].value.as < Node* > ()}; }
#line 1012 "parser.tab.cc"
    break;

  case 20: // ParameterList: Type Identifier COMMA ParameterList
#line 146 "parser.yy"
                                        { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[2].value.as < Node* > ()); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[3].value.as < Node* > ()); }
#line 1018 "parser.tab.cc"
    break;

  case 21: // ParameterList: %empty
#line 147 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1024 "parser.tab.cc"
    break;

  case 22: // Type: INT LEFT_BRACKET RIGHT_BRACKET
#line 151 "parser.yy"
                                   { yylhs.value.as < Node* > () = new Node("Type", "Int[]", yylineno); }
#line 1030 "parser.tab.cc"
    break;

  case 23: // Type: BOOLEAN
#line 152 "parser.yy"
            { yylhs.value.as < Node* > () = new Node("Type", "Boolean", yylineno); }
#line 1036 "parser.tab.cc"
    break;

  case 24: // Type: INT
#line 153 "parser.yy"
        { yylhs.value.as < Node* > () = new Node("Type", "Int", yylineno); }
#line 1042 "parser.tab.cc"
    break;

  case 25: // Type: Identifier
#line 154 "parser.yy"
               { yylhs.value.as < Node* > () = new Node("Type", yystack_[0].value.as < Node* > ()->value, yylineno); }
#line 1048 "parser.tab.cc"
    break;

  case 26: // StatementList: Statement StatementList
#line 158 "parser.yy"
                            { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ()); }
#line 1054 "parser.tab.cc"
    break;

  case 27: // StatementList: %empty
#line 159 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1060 "parser.tab.cc"
    break;

  case 28: // Statement: LEFT_BRACE StatementList RIGHT_BRACE
#line 163 "parser.yy"
                                         {
    yylhs.value.as < Node* > () = new Node("Statement", "", yylineno);
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 1069 "parser.tab.cc"
    break;

  case 29: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement
#line 167 "parser.yy"
                                                                              {
    yylhs.value.as < Node* > () = new Node("Statement", "If", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1080 "parser.tab.cc"
    break;

  case 30: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 173 "parser.yy"
                                                               {
      yylhs.value.as < Node* > () = new Node("Statement", "If", yylineno);
      add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
      add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
    }
#line 1090 "parser.tab.cc"
    break;

  case 31: // Statement: WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 178 "parser.yy"
                                                                  {
    yylhs.value.as < Node* > () = new Node("Statement", "While", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1100 "parser.tab.cc"
    break;

  case 32: // Statement: SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON
#line 183 "parser.yy"
                                                                               {
    yylhs.value.as < Node* > () = new Node("Statement", "Println", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1109 "parser.tab.cc"
    break;

  case 33: // Statement: Identifier ASSIGN Expression SEMICOLON
#line 187 "parser.yy"
                                           {
    yylhs.value.as < Node* > () = new Node("Statement", "Assign", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1119 "parser.tab.cc"
    break;

  case 34: // Statement: Identifier LEFT_BRACKET Expression RIGHT_BRACKET ASSIGN Expression SEMICOLON
#line 192 "parser.yy"
                                                                                 {
    yylhs.value.as < Node* > () = new Node("Statement", "ArrayAssign", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[6].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1130 "parser.tab.cc"
    break;

  case 35: // ExpressionList: Expression
#line 201 "parser.yy"
               { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[0].value.as < Node* > ()}; }
#line 1136 "parser.tab.cc"
    break;

  case 36: // ExpressionList: Expression COMMA ExpressionList
#line 202 "parser.yy"
                                    { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[2].value.as < Node* > ()); }
#line 1142 "parser.tab.cc"
    break;

  case 37: // ExpressionList: %empty
#line 203 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1148 "parser.tab.cc"
    break;

  case 38: // Expression: Expression AND Expression
#line 207 "parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("Expression", "And", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1158 "parser.tab.cc"
    break;

  case 39: // Expression: Expression LESS_THAN Expression
#line 212 "parser.yy"
                                    {
    yylhs.value.as < Node* > () = new Node("Expression", "LessThan", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1168 "parser.tab.cc"
    break;

  case 40: // Expression: Expression ADD Expression
#line 217 "parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("Expression", "Add", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1178 "parser.tab.cc"
    break;

  case 41: // Expression: Expression SUBTRACT Expression
#line 222 "parser.yy"
                                   {
    yylhs.value.as < Node* > () = new Node("Expression", "Subtract", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1188 "parser.tab.cc"
    break;

  case 42: // Expression: Expression MULTIPLY Expression
#line 227 "parser.yy"
                                   {
    yylhs.value.as < Node* > () = new Node("Expression", "Multiply", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1198 "parser.tab.cc"
    break;

  case 43: // Expression: Expression LEFT_BRACKET Expression RIGHT_BRACKET
#line 232 "parser.yy"
                                                     {
    yylhs.value.as < Node* > () = new Node("Expression", "ArrayLookup", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1208 "parser.tab.cc"
    break;

  case 44: // Expression: Expression DOT LENGTH
#line 237 "parser.yy"
                          {
    yylhs.value.as < Node* > () = new Node("Expression", "ArrayLength", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1217 "parser.tab.cc"
    break;

  case 45: // Expression: Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS
#line 241 "parser.yy"
                                                                                {
    yylhs.value.as < Node* > () = new Node("Expression", "Call", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[5].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 1228 "parser.tab.cc"
    break;

  case 46: // Expression: INTEGER_LITERAL
#line 247 "parser.yy"
                    {
    yylhs.value.as < Node* > () = new Node("Expression", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1236 "parser.tab.cc"
    break;

  case 47: // Expression: TRUE
#line 250 "parser.yy"
         {
    yylhs.value.as < Node* > () = new Node("Expression", "True", yylineno);
  }
#line 1244 "parser.tab.cc"
    break;

  case 48: // Expression: FALSE
#line 253 "parser.yy"
          {
    yylhs.value.as < Node* > () = new Node("Expression", "False", yylineno);
  }
#line 1252 "parser.tab.cc"
    break;

  case 49: // Expression: Identifier
#line 256 "parser.yy"
               {
    yylhs.value.as < Node* > () = new Node("Expression", yystack_[0].value.as < Node* > ()->value, yylineno);
  }
#line 1260 "parser.tab.cc"
    break;

  case 50: // Expression: THIS
#line 259 "parser.yy"
         {
    yylhs.value.as < Node* > () = new Node("Expression", "This", yylineno);
  }
#line 1268 "parser.tab.cc"
    break;

  case 51: // Expression: NEW INT LEFT_BRACKET Expression RIGHT_BRACKET
#line 262 "parser.yy"
                                                  {
    yylhs.value.as < Node* > () = new Node("Expression", "NewArray", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1277 "parser.tab.cc"
    break;

  case 52: // Expression: NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS
#line 266 "parser.yy"
                                                      {
    yylhs.value.as < Node* > () = new Node("Expression", "NewObject", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1286 "parser.tab.cc"
    break;

  case 53: // Expression: NOT Expression
#line 270 "parser.yy"
                   {
    yylhs.value.as < Node* > () = new Node("Expression", "Not", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1295 "parser.tab.cc"
    break;

  case 54: // Expression: LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS
#line 274 "parser.yy"
                                                  {
    yylhs.value.as < Node* > () = yystack_[1].value.as < Node* > ();
  }
#line 1303 "parser.tab.cc"
    break;

  case 55: // Identifier: IDENTIFIER
#line 280 "parser.yy"
               {
    yylhs.value.as < Node* > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1311 "parser.tab.cc"
    break;


#line 1315 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -86;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       4,    12,    24,    28,    -6,   -86,    -6,   -86,    28,   -86,
      17,   -26,   -86,    44,    -3,    -6,     7,    23,   -86,    34,
     -86,    -6,   -86,    29,    58,    30,    -3,   -86,    36,    64,
      -9,    -3,    63,   -86,    -6,   -86,   -86,   103,   -86,    34,
      39,    41,   -86,   -86,   -86,     1,   103,   103,   -86,   125,
     -86,    46,    67,    -3,    54,    48,   292,   198,   103,   103,
     103,   103,   103,   103,   -20,   -86,   -86,    61,    66,    -6,
     103,    70,   -86,   292,   292,   292,   292,   292,    56,   -86,
      65,    69,    75,    59,   213,   -86,   -86,   103,    -6,   102,
      -3,   -86,    81,   185,    84,    68,    91,    49,    92,   -86,
      82,   102,   -86,   -13,   -86,   -86,   103,    98,   103,   103,
      99,    49,   -13,   103,   103,   -86,   103,   103,   -86,    49,
     230,   245,   -86,   -86,   260,   140,   275,   155,   100,    49,
      49,    96,   105,    90,   -86,   106,   126,   -86,   -86,   -86,
     103,   -86,    49,   170,   -86,   -86
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     5,     0,     1,     0,     2,     5,    55,
       0,     0,     4,     0,     0,     0,     0,    24,    23,    13,
       8,     0,    25,     0,     0,     0,     0,     9,     0,    13,
       0,     0,     0,    22,     0,     6,    12,     0,    10,    13,
       0,     0,    47,    48,    50,     0,     0,     0,    46,     0,
      49,     0,     0,    21,     0,     0,    53,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     7,     0,     0,     0,
       0,     0,    54,    38,    39,    40,    41,    42,     0,    44,
       0,     0,     0,    19,     0,    52,    43,    37,     0,    16,
      21,    51,     0,    35,     0,     0,     0,    27,     0,    17,
       0,    16,    18,    25,    20,    45,    37,     0,     0,     0,
       0,    27,     0,     0,     0,    15,     0,     0,    36,     0,
       0,     0,    28,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,    30,    31,    32,    14,
       0,     3,     0,     0,    29,    34
  };

  const short
  parser::yypgoto_[] =
  {
     -86,   -86,   -86,   131,   -86,   109,   -18,   -16,   -86,    47,
     -86,    57,   -22,    42,   -85,    50,    -8,    -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     7,     8,    19,    20,    28,    29,   100,
     101,    68,    21,   110,   102,    92,    93,    50
  };

  const unsigned char
  parser::yytable_[] =
  {
      10,    27,    11,    14,    34,    17,    18,     1,    79,    54,
      22,    23,   111,    36,    37,    22,     4,    30,    15,     9,
     116,    27,    22,    51,     5,   117,   111,    22,    38,    49,
      41,    69,     6,     9,   128,    22,     9,    26,    56,    57,
       9,    55,    17,    18,   136,   137,    13,    16,    24,    22,
      73,    74,    75,    76,    77,    78,    25,   144,    31,    95,
      80,    96,    84,    32,    33,    83,    35,    26,    69,    40,
      52,    99,    53,     9,    67,    58,    66,    59,    97,    71,
      60,    61,    62,    99,    94,   103,    22,    70,     9,    63,
      86,    64,    98,   112,    81,    90,    87,   103,    82,   108,
     120,   121,    85,    88,    89,   124,   125,   112,   126,   127,
      17,    18,    95,   105,    96,   112,   107,    42,    43,    44,
      45,    46,   109,   113,   114,   112,   112,   119,   140,   122,
     135,    97,   143,   138,    47,   139,   141,   142,   112,    12,
      39,     9,     9,    48,    58,    98,    59,   104,   115,    60,
      61,    62,     0,   123,     0,     0,   118,     0,    63,    58,
      64,    59,    65,     0,    60,    61,    62,     0,     0,     0,
       0,     0,     0,    63,    58,    64,    59,   132,     0,    60,
      61,    62,     0,     0,     0,     0,     0,     0,    63,    58,
      64,    59,   134,     0,    60,    61,    62,     0,     0,     0,
       0,     0,     0,    63,    58,    64,    59,   145,     0,    60,
      61,    62,     0,     0,     0,     0,     0,    58,    63,    59,
      64,   106,    60,    61,    62,     0,     0,     0,     0,     0,
      72,    63,    58,    64,    59,     0,     0,    60,    61,    62,
       0,     0,     0,     0,     0,     0,    63,    91,    64,    58,
       0,    59,     0,     0,    60,    61,    62,     0,     0,     0,
       0,     0,   129,    63,    58,    64,    59,     0,     0,    60,
      61,    62,     0,     0,     0,     0,     0,   130,    63,    58,
      64,    59,     0,     0,    60,    61,    62,     0,     0,     0,
       0,     0,   131,    63,    58,    64,    59,     0,     0,    60,
      61,    62,     0,     0,     0,     0,     0,     0,    63,   133,
      64,    58,     0,    59,     0,     0,    60,    61,    62,     0,
       0,     0,     0,     0,     0,    63,     0,    64
  };

  const short
  parser::yycheck_[] =
  {
       4,    19,     6,    29,    26,     8,     9,     3,    28,     8,
      14,    15,    97,    29,    23,    19,     4,    21,    44,    39,
      33,    39,    26,    39,     0,    38,   111,    31,    37,    37,
      34,    53,     4,    39,   119,    39,    39,     3,    46,    47,
      39,    45,     8,     9,   129,   130,    29,     3,    41,    53,
      58,    59,    60,    61,    62,    63,    33,   142,    29,    10,
      64,    12,    70,     5,    34,    69,    30,     3,    90,     6,
      31,    89,    31,    39,     7,    19,    30,    21,    29,    31,
      24,    25,    26,   101,    88,    89,    90,    33,    39,    33,
      34,    35,    43,    97,    33,    36,    31,   101,    32,    31,
     108,   109,    32,    34,    29,   113,   114,   111,   116,   117,
       8,     9,    10,    32,    12,   119,    32,    14,    15,    16,
      17,    18,    31,    31,    42,   129,   130,    29,    38,    30,
      30,    29,   140,    37,    31,    30,    30,    11,   142,     8,
      31,    39,    39,    40,    19,    43,    21,    90,   101,    24,
      25,    26,    -1,   111,    -1,    -1,   106,    -1,    33,    19,
      35,    21,    37,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    19,    35,    21,    37,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    19,
      35,    21,    37,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    19,    35,    21,    37,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    19,    33,    21,
      35,    36,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33,    19,    35,    21,    -1,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    19,
      -1,    21,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    19,    35,    21,    -1,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,    19,
      35,    21,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    19,    35,    21,    -1,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    19,    -1,    21,    -1,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    35
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,    48,    49,     4,     0,     4,    50,    51,    39,
      64,    64,    50,    29,    29,    44,     3,     8,     9,    52,
      53,    59,    64,    64,    41,    33,     3,    53,    54,    55,
      64,    29,     5,    34,    59,    30,    54,    23,    37,    52,
       6,    64,    14,    15,    16,    17,    18,    31,    40,    63,
      64,    54,    31,    31,     8,    64,    63,    63,    19,    21,
      24,    25,    26,    33,    35,    37,    30,     7,    58,    59,
      33,    31,    32,    63,    63,    63,    63,    63,    63,    28,
      64,    33,    32,    64,    63,    32,    34,    31,    34,    29,
      36,    34,    62,    63,    64,    10,    12,    29,    43,    53,
      56,    57,    61,    64,    58,    32,    36,    32,    31,    31,
      60,    61,    64,    31,    42,    56,    33,    38,    62,    29,
      63,    63,    30,    60,    63,    63,    63,    63,    61,    32,
      32,    32,    37,    34,    37,    30,    61,    61,    37,    30,
      38,    30,    11,    63,    61,    37
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    47,    48,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    58,    59,    59,    59,    59,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    64
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,    18,     2,     0,     6,     8,     1,     2,
       3,     5,     2,     0,    12,     2,     0,     1,     1,     2,
       4,     0,     3,     1,     1,     1,     2,     0,     3,     7,
       5,     5,     5,     4,     7,     1,     3,     0,     3,     3,
       3,     3,     3,     4,     3,     6,     1,     1,     1,     1,
       1,     5,     4,     2,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PUBLIC", "CLASS",
  "VOID", "MAIN", "STRING", "INT", "BOOLEAN", "IF", "ELSE", "WHILE",
  "PRINT", "TRUE", "FALSE", "THIS", "NEW", "NOT", "AND", "OR", "LESS_THAN",
  "GREATER_THAN", "EQUAL", "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE",
  "LENGTH", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_PARENTHESIS",
  "RIGHT_PARENTHESIS", "LEFT_BRACKET", "RIGHT_BRACKET", "DOT", "COMMA",
  "SEMICOLON", "ASSIGN", "IDENTIFIER", "INTEGER_LITERAL", "STATIC",
  "RETURN", "SYSTEM_OUT_PRINTLN", "EXTENDS", "COMMENT", "ERROR", "$accept",
  "Goal", "MainClass", "ClassDeclarationList", "ClassDeclaration",
  "VarDeclarationList", "VarDeclaration", "MethodDeclarationList",
  "MethodDeclaration", "MethodBody", "MethodBodyItem", "ParameterList",
  "Type", "StatementList", "Statement", "ExpressionList", "Expression",
  "Identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    52,    52,    61,    70,    74,    78,    84,    94,    95,
     101,   106,   115,   116,   120,   131,   135,   139,   140,   145,
     146,   147,   151,   152,   153,   154,   158,   159,   163,   167,
     173,   178,   183,   187,   192,   201,   202,   203,   207,   212,
     217,   222,   227,   232,   237,   241,   247,   250,   253,   256,
     259,   262,   266,   270,   274,   280
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1904 "parser.tab.cc"

#line 285 "parser.yy"


