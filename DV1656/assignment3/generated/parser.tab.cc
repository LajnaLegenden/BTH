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
#line 15 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"

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

#line 63 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


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
#line 155 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"

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
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainMethod: // MainMethod
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
        value.YY_MOVE_OR_COPY< Node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ClassBody: // ClassBody
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
      case symbol_kind::S_TypeOrIdentifier: // TypeOrIdentifier
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Identifier: // Identifier
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
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainMethod: // MainMethod
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
        value.move< Node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ClassBody: // ClassBody
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
      case symbol_kind::S_TypeOrIdentifier: // TypeOrIdentifier
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Identifier: // Identifier
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
      case symbol_kind::S_MainMethod: // MainMethod
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
        value.copy< Node* > (that.value);
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ClassBody: // ClassBody
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
      case symbol_kind::S_TypeOrIdentifier: // TypeOrIdentifier
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Identifier: // Identifier
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
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
      case symbol_kind::S_MainMethod: // MainMethod
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
        value.move< Node* > (that.value);
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ClassBody: // ClassBody
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
      case symbol_kind::S_TypeOrIdentifier: // TypeOrIdentifier
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Identifier: // Identifier
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
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
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

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
      case symbol_kind::S_MainMethod: // MainMethod
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodBodyItem: // MethodBodyItem
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
        yylhs.value.emplace< Node* > ();
        break;

      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodBody: // MethodBody
      case symbol_kind::S_ClassBody: // ClassBody
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
      case symbol_kind::S_TypeOrIdentifier: // TypeOrIdentifier
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Identifier: // Identifier
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
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
#line 63 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                   {
    yylhs.value.as < Node* > () = new Node("Goal", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[0].value.as < std::list<Node*> > ());
    root = yylhs.value.as < Node* > ();
  }
#line 903 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 3: // MainClass: PUBLIC CLASS Identifier LEFT_BRACE ClassBody RIGHT_BRACE
#line 72 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                             {
    yylhs.value.as < Node* > () = new Node("MainClass", yystack_[3].value.as < std::string > (), yylineno);
   add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 912 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 4: // MainMethod: PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE MethodBody RIGHT_BRACE
#line 79 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                                                                                                              {
    yylhs.value.as < Node* > () = new Node("void", "main", yylineno);
    add_child(yylhs.value.as < Node* > (), new Node("string[]", yystack_[4].value.as < std::string > (), yylineno));
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());  // $12 is MethodBody
  }
#line 922 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 5: // ClassDeclarationList: ClassDeclaration ClassDeclarationList
#line 89 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                          {
    yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
    yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
  }
#line 931 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 6: // ClassDeclarationList: %empty
#line 93 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 937 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 7: // ClassDeclaration: CLASS Identifier LEFT_BRACE ClassBody RIGHT_BRACE
#line 97 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                      {
    yylhs.value.as < Node* > () = new Node("ClassDeclaration", yystack_[3].value.as < std::string > (), yylineno);
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 946 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 8: // VarDeclaration: TypeOrIdentifier Identifier SEMICOLON
#line 106 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                          {
    yylhs.value.as < Node* > () = new Node("VarDeclaration", yystack_[1].value.as < std::string > (), yylineno);
    add_child(yylhs.value.as < Node* > (), new Node(yystack_[2].value.as < std::string > (), yystack_[1].value.as < std::string > (), yylineno));
  }
#line 955 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 9: // VarDeclaration: TypeOrIdentifier Identifier ASSIGN Expression SEMICOLON
#line 110 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                            {
        yylhs.value.as < Node* > () = new Node("VarDeclaration", yystack_[3].value.as < std::string > (), yylineno);
        add_child(yylhs.value.as < Node* > (), new Node(yystack_[4].value.as < std::string > (), yystack_[3].value.as < std::string > (), yylineno));
      }
#line 964 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 10: // TypeOrIdentifier: Type
#line 117 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
         { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 970 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 11: // TypeOrIdentifier: Identifier
#line 118 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 976 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 12: // MethodDeclaration: PUBLIC TypeOrIdentifier Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE MethodBody RETURN Expression SEMICOLON RIGHT_BRACE
#line 121 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                                                                                                                      {
    std::vector<std::string> typeName = {yystack_[10].value.as < std::string > (),yystack_[9].value.as < std::string > ()};
    yylhs.value.as < Node* > () = new Node("MethodDeclaration", StringUtils::join(typeName, ":"), yylineno);
    Node* params = new Node("ParameterList", yystack_[9].value.as < std::string > (), yylineno);
    add_children(params, yystack_[7].value.as < std::list<Node*> > ());
    add_child(yylhs.value.as < Node* > (), params);
    add_children(yylhs.value.as < Node* > (), yystack_[4].value.as < std::list<Node*> > ());  // Add all children from MethodBody
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());    // Add the return expression
  }
#line 990 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 13: // MethodBody: MethodBodyItem MethodBody
#line 133 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                              {
    yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
    yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
  }
#line 999 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 14: // MethodBody: %empty
#line 137 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1005 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 15: // MethodBodyItem: VarDeclaration
#line 141 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                   { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 1011 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 16: // MethodBodyItem: Statement
#line 142 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
              { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 1017 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 17: // ClassBody: ClassBodyItem ClassBody
#line 146 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                            {
      yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
      yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
    }
#line 1026 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 18: // ClassBody: %empty
#line 150 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1032 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 19: // ClassBodyItem: VarDeclaration
#line 154 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                   { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > ();}
#line 1038 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 20: // ClassBodyItem: MethodDeclaration
#line 156 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                      { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 1044 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 21: // ClassBodyItem: MainMethod
#line 158 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
               { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 1050 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 22: // ParameterList: Parameter
#line 162 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
              { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[0].value.as < Node* > ()}; }
#line 1056 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 23: // ParameterList: Parameter COMMA ParameterList
#line 163 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                  { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[2].value.as < Node* > ()); }
#line 1062 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 24: // ParameterList: %empty
#line 164 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1068 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 25: // Parameter: Type Identifier
#line 168 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                      {
    yylhs.value.as < Node* > () = new Node(yystack_[1].value.as < std::string > (),yystack_[0].value.as < std::string > (), yylineno);
    }
#line 1076 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 26: // Parameter: Identifier Identifier
#line 171 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                            {
    yylhs.value.as < Node* > () = new Node(yystack_[1].value.as < std::string > (),yystack_[0].value.as < std::string > (), yylineno);
    }
#line 1084 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 27: // Type: INT LEFT_BRACKET RIGHT_BRACKET
#line 176 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                   { yylhs.value.as < std::string > () = "int[]"; }
#line 1090 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 28: // Type: BOOLEAN
#line 177 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
            { yylhs.value.as < std::string > () = "bool"; }
#line 1096 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 29: // Type: INT
#line 178 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
        { yylhs.value.as < std::string > () = "int" ;}
#line 1102 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 30: // Type: STRING LEFT_BRACKET RIGHT_BRACKET
#line 179 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                       { yylhs.value.as < std::string > () = "string[]"; }
#line 1108 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 31: // StatementList: Statement StatementList
#line 183 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                            { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ()); }
#line 1114 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 32: // StatementList: %empty
#line 184 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1120 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 33: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 188 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
    {
        yylhs.value.as < Node* > () = new IfStatement("If", "if", yylhs.location.begin.line);
        yylhs.value.as < Node* > ()->children.push_back(yystack_[2].value.as < Node* > ());  // condition
        yylhs.value.as < Node* > ()->children.push_back(yystack_[0].value.as < Node* > ());  // then part
    }
#line 1130 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 34: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement
#line 194 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
    {
        yylhs.value.as < Node* > () = new IfStatement("IfElse", "if-else", yylhs.location.begin.line);
        yylhs.value.as < Node* > ()->children.push_back(yystack_[4].value.as < Node* > ());  // condition
        yylhs.value.as < Node* > ()->children.push_back(yystack_[2].value.as < Node* > ());  // then part
        yylhs.value.as < Node* > ()->children.push_back(yystack_[0].value.as < Node* > ());  // else part
    }
#line 1141 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 35: // Statement: WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 201 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
    {
        yylhs.value.as < Node* > () = new WhileStatement("While", "while", yylhs.location.begin.line);
        yylhs.value.as < Node* > ()->children.push_back(yystack_[2].value.as < Node* > ());  // condition
        yylhs.value.as < Node* > ()->children.push_back(yystack_[0].value.as < Node* > ());  // body
    }
#line 1151 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 36: // Statement: SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON
#line 207 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
    {
        yylhs.value.as < Node* > () = new PrintStatement("Print", "println", yylhs.location.begin.line);
        yylhs.value.as < Node* > ()->children.push_back(yystack_[2].value.as < Node* > ());
    }
#line 1160 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 37: // Statement: IDENTIFIER ASSIGN Expression SEMICOLON
#line 212 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
    {
        yylhs.value.as < Node* > () = new AssignmentStatement("Assignment", yystack_[3].value.as < std::string > (), yylhs.location.begin.line);
        Node* id = new IdentifierExpression("Identifier", yystack_[3].value.as < std::string > (), yylhs.location.begin.line);
        yylhs.value.as < Node* > ()->children.push_back(id);
        yylhs.value.as < Node* > ()->children.push_back(yystack_[1].value.as < Node* > ());
    }
#line 1171 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 38: // Statement: LEFT_BRACE StatementList RIGHT_BRACE
#line 219 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
    {
        yylhs.value.as < Node* > () = new BlockStatement("Block", "block", yylhs.location.begin.line);
        // Add all statements in the block
        for (auto stmt : yystack_[1].value.as < std::list<Node*> > ()) {
            yylhs.value.as < Node* > ()->children.push_back(stmt);
        }
    }
#line 1183 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 39: // ExpressionList: Expression
#line 229 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
               { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[0].value.as < Node* > ()}; }
#line 1189 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 40: // ExpressionList: Expression COMMA ExpressionList
#line 230 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                    { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[2].value.as < Node* > ()); }
#line 1195 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 41: // ExpressionList: %empty
#line 231 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1201 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 42: // Expression: Expression AND Expression
#line 235 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("Comparison", "And", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1211 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 43: // Expression: Expression OR Expression
#line 240 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                             {
    yylhs.value.as < Node* > () = new Node("Comparison", "Or", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1221 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 44: // Expression: Expression LESS_THAN Expression
#line 245 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                    {
    yylhs.value.as < Node* > () = new Node("Comparison", "LessThan", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1231 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 45: // Expression: Expression GREATER_THAN Expression
#line 250 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                       {
    yylhs.value.as < Node* > () = new Node("Comparison", "GreaterThan", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1241 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 46: // Expression: Expression ADD Expression
#line 255 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                              {
    yylhs.value.as < Node* > () = new AddExpression("Operation", "Add", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1251 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 47: // Expression: Expression SUBTRACT Expression
#line 260 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                   {
    yylhs.value.as < Node* > () = new SubExpression("Operation", "Subtract", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1261 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 48: // Expression: Expression MULTIPLY Expression
#line 265 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                   {
    yylhs.value.as < Node* > () = new MulExpression("Operation", "Multiply", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1271 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 49: // Expression: Expression EQUAL Expression
#line 270 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                {
    yylhs.value.as < Node* > () = new Node("Comparison", "Equal", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1281 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 50: // Expression: Expression DIVIDE Expression
#line 275 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                 {
    yylhs.value.as < Node* > () = new DivExpression("Operation", "Devide", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1291 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 51: // Expression: Expression LEFT_BRACKET Expression RIGHT_BRACKET
#line 280 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                     {
    yylhs.value.as < Node* > () = new Node("Operation", "ArrayLookup", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1301 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 52: // Expression: Expression DOT LENGTH
#line 285 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                          {
    yylhs.value.as < Node* > () = new Node("Statement", "ArrayLength", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1310 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 53: // Expression: Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS
#line 289 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                                                {
    yylhs.value.as < Node* > () = new Node("Expression", yystack_[3].value.as < std::string > (), yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[5].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 1320 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 54: // Expression: INTEGER_LITERAL
#line 294 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                    {
    yylhs.value.as < Node* > () = new NumberExpression("Number", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1328 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 55: // Expression: TRUE
#line 297 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
         {
    yylhs.value.as < Node* > () = new BooleanExpression("TrueOrFalse", "True", yylineno);
  }
#line 1336 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 56: // Expression: FALSE
#line 300 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
          {
    yylhs.value.as < Node* > () = new BooleanExpression("TrueOrFalse", "False", yylineno);
  }
#line 1344 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 57: // Expression: Identifier
#line 303 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
               {
    yylhs.value.as < Node* > () = new Node("Expression", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1352 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 58: // Expression: THIS
#line 306 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
         {
    yylhs.value.as < Node* > () = new Node("This", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1360 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 59: // Expression: NEW INT LEFT_BRACKET Expression RIGHT_BRACKET
#line 309 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                  {
    yylhs.value.as < Node* > () = new Node("NewIntArray", "TMP", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1369 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 60: // Expression: NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS
#line 313 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                      {
    yylhs.value.as < Node* > () = new Node("NewInstance", yystack_[2].value.as < std::string > (), yylineno);
  }
#line 1377 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 61: // Expression: NOT Expression
#line 316 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                   {
    yylhs.value.as < Node* > () = new Node("Not", "TMP", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1386 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 62: // Expression: LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS
#line 320 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
                                                  {
    yylhs.value.as < Node* > () = yystack_[1].value.as < Node* > ();
  }
#line 1394 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;

  case 63: // Identifier: IDENTIFIER
#line 326 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"
               {
    yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
  }
#line 1402 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"
    break;


#line 1406 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"

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
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
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

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
    error (yyexc.location, yyexc.what ());
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


  const signed char parser::yypact_ninf_ = -98;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      -2,    -1,    15,    45,    12,   -98,    12,   -98,    45,   -98,
      27,    28,   -98,    39,    39,    56,    29,    34,   -98,   -98,
     -98,    12,   -98,    38,    39,   -98,   -98,    40,    65,    12,
      41,    42,   -15,   -98,   -98,   -98,    70,    49,   -98,   -98,
     -98,    94,    63,    75,   -98,   -98,   -98,    16,    94,    94,
     -98,   116,   -98,    88,    67,    66,    12,    12,    72,    76,
      68,    96,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,   -20,   -98,    80,    95,    75,   -98,   -98,    94,
      98,   -98,   306,   291,   321,   321,   276,   326,   326,    68,
      68,   191,   -98,   113,    92,    50,   -98,   208,   -98,   -98,
      94,    12,   114,   115,    61,    89,   117,   -98,   105,    50,
     -98,   -98,   118,   173,   120,    94,    94,    89,   133,    61,
      94,    94,    94,   -98,   -98,    94,   136,   225,   242,   -98,
     -98,   135,   259,   154,   -98,    50,    61,    61,   -98,   127,
     137,   139,   159,   -98,   -98,   -98,   -98,    61,   -98
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     6,     0,     1,     0,     2,     6,    63,
       0,     0,     5,    18,    18,     0,     0,    29,    28,    21,
      19,     0,    20,     0,    18,    10,    11,     0,     0,     0,
       0,     0,     0,     3,    17,     7,     0,     0,    30,    27,
       8,     0,     0,    24,    55,    56,    58,     0,     0,     0,
      54,     0,    57,     0,     0,    22,     0,     0,     0,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,     0,     0,    24,    25,    26,     0,
       0,    62,    42,    43,    44,    45,    49,    46,    47,    48,
      50,     0,    52,     0,     0,    14,    23,     0,    60,    51,
      41,     0,     0,     0,    32,    63,     0,    15,     0,    14,
      16,    59,     0,    39,     0,     0,     0,     0,     0,    32,
       0,     0,     0,    13,    53,    41,     0,     0,     0,    38,
      31,     0,     0,     0,    40,    14,     0,     0,    37,     0,
       0,     0,    33,    35,    36,    12,     4,     0,    34
  };

  const short
  parser::yypgoto_[] =
  {
     -98,   -98,   -98,   -98,   157,   -98,   -90,   166,   -98,   -97,
     -98,     2,   -98,   106,   -98,   -39,    64,   -96,    59,   -35,
      -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,     3,    19,     7,     8,    20,    21,    22,   108,
     109,    23,    24,    54,    55,    25,   118,   110,   112,   113,
      52
  };

  const short
  parser::yytable_[] =
  {
      10,     1,    11,     4,    56,   107,    51,    92,   119,    26,
      26,    26,   123,    60,    61,     5,    27,    32,     9,   107,
      26,    40,    41,   119,    58,    37,    34,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    56,   141,    57,
     142,   143,    15,    59,    97,   107,    16,    17,    18,     6,
       9,   148,    77,    78,     9,    13,    14,    16,    17,    18,
     102,    30,   103,    16,    17,    18,    31,    33,    93,    35,
      36,   102,    57,   103,    38,    39,    42,     9,   104,    43,
     127,   128,    16,    17,    18,   131,   132,   133,   105,   104,
      66,    26,   106,    53,     9,    74,    28,   114,    75,   117,
      71,    76,    72,   106,    79,    26,    80,    44,    45,    46,
      47,    48,    94,     9,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    95,    49,   101,   120,    81,    71,    98,
      72,    26,     9,    50,    62,    63,    64,    65,    66,    67,
      68,    69,    70,   100,   115,   116,   122,   121,    71,   124,
      72,   126,    73,    62,    63,    64,    65,    66,    67,    68,
      69,    70,   129,   144,   135,    12,   145,    71,   146,    72,
     147,   138,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    29,    96,   130,   134,     0,    71,     0,    72,     0,
     140,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       0,     0,     0,     0,     0,    71,     0,    72,   125,    62,
      63,    64,    65,    66,    67,    68,    69,    70,     0,     0,
       0,     0,     0,    71,    99,    72,    62,    63,    64,    65,
      66,    67,    68,    69,    70,     0,     0,     0,     0,     0,
      71,   111,    72,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     0,     0,     0,     0,   136,    71,     0,    72,
      62,    63,    64,    65,    66,    67,    68,    69,    70,     0,
       0,     0,     0,   137,    71,     0,    72,    62,    63,    64,
      65,    66,    67,    68,    69,    70,     0,     0,     0,     0,
     139,    71,     0,    72,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     0,     0,     0,     0,     0,    71,    62,
      72,    64,    65,    66,    67,    68,    69,    70,     0,     0,
       0,     0,     0,    71,     0,    72,    64,    65,    66,    67,
      68,    69,    70,     0,     0,     0,     0,     0,    71,     0,
      72,    -1,    -1,    66,    67,    68,    69,    70,    66,     0,
       0,    69,    70,    71,     0,    72,     0,     0,    71,     0,
      72
  };

  const short
  parser::yycheck_[] =
  {
       4,     3,     6,     4,    43,    95,    41,    27,   104,    13,
      14,    15,   109,    48,    49,     0,    14,    21,    38,   109,
      24,    36,    37,   119,     8,    29,    24,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    76,   135,    43,
     136,   137,     3,    47,    79,   135,     7,     8,     9,     4,
      38,   147,    56,    57,    38,    28,    28,     7,     8,     9,
      10,    32,    12,     7,     8,     9,    32,    29,    72,    29,
       5,    10,    76,    12,    33,    33,     6,    38,    28,    30,
     115,   116,     7,     8,     9,   120,   121,   122,    38,    28,
      22,    95,    42,    30,    38,     7,    40,   101,    31,    38,
      32,    35,    34,    42,    32,   109,    30,    13,    14,    15,
      16,    17,    32,    38,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    28,    30,    33,    37,    31,    32,    31,
      34,   135,    38,    39,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    30,    30,    30,    41,    30,    32,    31,
      34,    31,    36,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    29,    36,    28,     8,    29,    32,    29,    34,
      11,    36,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    15,    76,   119,   125,    -1,    32,    -1,    34,    -1,
      36,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    31,    32,    -1,    34,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    31,    32,    -1,    34,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    32,    -1,    34,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,    18,
      34,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    34,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      34,    20,    21,    22,    23,    24,    25,    26,    22,    -1,
      -1,    25,    26,    32,    -1,    34,    -1,    -1,    32,    -1,
      34
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,    46,    47,     4,     0,     4,    49,    50,    38,
      65,    65,    49,    28,    28,     3,     7,     8,     9,    48,
      51,    52,    53,    56,    57,    60,    65,    56,    40,    52,
      32,    32,    65,    29,    56,    29,     5,    65,    33,    33,
      36,    37,     6,    30,    13,    14,    15,    16,    17,    30,
      39,    64,    65,    30,    58,    59,    60,    65,     8,    65,
      64,    64,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    32,    34,    36,     7,    31,    35,    65,    65,    32,
      30,    31,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    27,    65,    32,    28,    58,    64,    31,    33,
      30,    33,    10,    12,    28,    38,    42,    51,    54,    55,
      62,    33,    63,    64,    65,    30,    30,    38,    61,    62,
      37,    30,    41,    54,    31,    35,    31,    64,    64,    29,
      61,    64,    64,    64,    63,    28,    31,    31,    36,    31,
      36,    54,    62,    62,    36,    29,    29,    11,    62
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    45,    46,    47,    48,    49,    49,    50,    51,    51,
      52,    52,    53,    54,    54,    55,    55,    56,    56,    57,
      57,    57,    58,    58,    58,    59,    59,    60,    60,    60,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    65
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     6,    13,     2,     0,     5,     3,     5,
       1,     1,    12,     2,     0,     1,     1,     2,     0,     1,
       1,     1,     1,     3,     0,     2,     2,     3,     1,     1,
       3,     2,     0,     5,     7,     5,     5,     4,     3,     1,
       3,     0,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     6,     1,     1,     1,     1,     1,     5,
       4,     2,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PUBLIC", "CLASS",
  "VOID", "MAIN", "STRING", "INT", "BOOLEAN", "IF", "ELSE", "WHILE",
  "TRUE", "FALSE", "THIS", "NEW", "NOT", "AND", "OR", "LESS_THAN",
  "GREATER_THAN", "EQUAL", "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE",
  "LENGTH", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_PARENTHESIS",
  "RIGHT_PARENTHESIS", "LEFT_BRACKET", "RIGHT_BRACKET", "DOT", "COMMA",
  "SEMICOLON", "ASSIGN", "IDENTIFIER", "INTEGER_LITERAL", "STATIC",
  "RETURN", "SYSTEM_OUT_PRINTLN", "EXTENDS", "LOWER_THAN_ELSE", "$accept",
  "Goal", "MainClass", "MainMethod", "ClassDeclarationList",
  "ClassDeclaration", "VarDeclaration", "TypeOrIdentifier",
  "MethodDeclaration", "MethodBody", "MethodBodyItem", "ClassBody",
  "ClassBodyItem", "ParameterList", "Parameter", "Type", "StatementList",
  "Statement", "ExpressionList", "Expression", "Identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    63,    63,    72,    79,    89,    93,    97,   106,   110,
     117,   118,   121,   133,   137,   141,   142,   146,   150,   154,
     156,   158,   162,   163,   164,   168,   171,   176,   177,   178,
     179,   183,   184,   187,   193,   200,   206,   211,   218,   229,
     230,   231,   235,   240,   245,   250,   255,   260,   265,   270,
     275,   280,   285,   289,   294,   297,   300,   303,   306,   309,
     313,   316,   320,   326
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
#line 2012 "/home/lajna/code/BTH/DV1656/assignment3/generated/parser.tab.cc"

#line 331 "/home/lajna/code/BTH/DV1656/assignment3/parser.yy"


