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

#line 63 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"


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
#line 136 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"

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
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
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
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
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
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
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
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
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
      case symbol_kind::S_ClassBodyItem: // ClassBodyItem
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_Identifier: // Identifier
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
#line 61 "parser.yy"
                                   { 
    yylhs.value.as < Node* > () = new Node("Goal", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[0].value.as < std::list<Node*> > ());
    root = yylhs.value.as < Node* > ();
  }
#line 857 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 3: // MainClass: PUBLIC CLASS Identifier LEFT_BRACE PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE Statement RIGHT_BRACE RIGHT_BRACE
#line 70 "parser.yy"
                                                                                                                                                                                            { 
    yylhs.value.as < Node* > () = new Node("MainClass", "", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[15].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[5].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 868 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 4: // ClassDeclarationList: ClassDeclaration ClassDeclarationList
#line 79 "parser.yy"
                                          { 
    yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
    yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
  }
#line 877 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 5: // ClassDeclarationList: %empty
#line 83 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 883 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 6: // ClassDeclaration: CLASS Identifier LEFT_BRACE ClassBody RIGHT_BRACE
#line 87 "parser.yy"
                                                      {
    yylhs.value.as < Node* > () = new Node("ClassDeclaration", yystack_[3].value.as < Node* > ()->value, yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 893 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 7: // ClassDeclaration: CLASS Identifier EXTENDS Identifier LEFT_BRACE ClassBody RIGHT_BRACE
#line 92 "parser.yy"
                                                                         {
    yylhs.value.as < Node* > () = new Node("ClassDeclaration", yystack_[5].value.as < Node* > ()->value, yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[5].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 904 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 8: // VarDeclaration: Type Identifier SEMICOLON
#line 102 "parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("VarDeclaration", yystack_[1].value.as < Node* > ()->value, yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 914 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 9: // VarDeclaration: Type Identifier ASSIGN Expression SEMICOLON
#line 107 "parser.yy"
                                                {
        yylhs.value.as < Node* > () = new Node("VarDeclaration", yystack_[3].value.as < Node* > ()->value, yylineno);
        add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
        add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
        add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
      }
#line 925 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 10: // MethodDeclaration: PUBLIC Type Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE MethodBody RETURN Expression SEMICOLON RIGHT_BRACE
#line 118 "parser.yy"
                                                                                                                                          {
    yylhs.value.as < Node* > () = new Node("MethodDeclaration", yystack_[9].value.as < Node* > ()->value, yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[10].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[9].value.as < Node* > ());
    Node* params = new Node("ParameterList", "", yylineno);
    add_children(params, yystack_[7].value.as < std::list<Node*> > ());
    add_child(yylhs.value.as < Node* > (), params);
    add_children(yylhs.value.as < Node* > (), yystack_[4].value.as < std::list<Node*> > ());  // Add all children from MethodBody
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());    // Add the return expression
  }
#line 940 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 11: // MethodBody: MethodBodyItem MethodBody
#line 131 "parser.yy"
                              {
    yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
    yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
  }
#line 949 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 12: // MethodBody: %empty
#line 135 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 955 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 13: // MethodBodyItem: VarDeclaration
#line 139 "parser.yy"
                   { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 961 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 14: // MethodBodyItem: Statement
#line 140 "parser.yy"
              { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 967 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 15: // ClassBody: ClassBodyItem ClassBody
#line 144 "parser.yy"
                            {
      yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
      yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ());
    }
#line 976 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 16: // ClassBody: %empty
#line 148 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 982 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 17: // ClassBodyItem: VarDeclaration
#line 152 "parser.yy"
                   { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 988 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 18: // ClassBodyItem: MethodDeclaration
#line 153 "parser.yy"
                      { yylhs.value.as < Node* > () = yystack_[0].value.as < Node* > (); }
#line 994 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 19: // ParameterList: Type Identifier
#line 157 "parser.yy"
                    { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[1].value.as < Node* > (), yystack_[0].value.as < Node* > ()}; }
#line 1000 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 20: // ParameterList: Type Identifier COMMA ParameterList
#line 158 "parser.yy"
                                        { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[2].value.as < Node* > ()); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[3].value.as < Node* > ()); }
#line 1006 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 21: // ParameterList: %empty
#line 159 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1012 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 22: // Type: INT LEFT_BRACKET RIGHT_BRACKET
#line 163 "parser.yy"
                                   { yylhs.value.as < Node* > () = new Node("Type", "Int[]", yylineno); }
#line 1018 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 23: // Type: BOOLEAN
#line 164 "parser.yy"
            { yylhs.value.as < Node* > () = new Node("Type", "Boolean", yylineno); }
#line 1024 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 24: // Type: INT
#line 165 "parser.yy"
        { yylhs.value.as < Node* > () = new Node("Type", "Int", yylineno); }
#line 1030 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 25: // Type: Identifier
#line 166 "parser.yy"
               { yylhs.value.as < Node* > () = new Node("Type", yystack_[0].value.as < Node* > ()->value, yylineno); }
#line 1036 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 26: // StatementList: Statement StatementList
#line 170 "parser.yy"
                            { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[1].value.as < Node* > ()); }
#line 1042 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 27: // StatementList: %empty
#line 171 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1048 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 28: // Statement: LEFT_BRACE StatementList RIGHT_BRACE
#line 175 "parser.yy"
                                         {
    yylhs.value.as < Node* > () = new Node("Statement", "Block", yylineno);
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 1057 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 29: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 179 "parser.yy"
                                                                                     {
    yylhs.value.as < Node* > () = new Node("Statement", "If", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1067 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 30: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement
#line 184 "parser.yy"
                                                                              {
    yylhs.value.as < Node* > () = new Node("Statement", "IfElse", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1078 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 31: // Statement: WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 190 "parser.yy"
                                                                  {
    yylhs.value.as < Node* > () = new Node("Statement", "While", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1088 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 32: // Statement: SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON
#line 195 "parser.yy"
                                                                               {
    yylhs.value.as < Node* > () = new Node("Statement", "Println", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1097 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 33: // Statement: Identifier ASSIGN Expression SEMICOLON
#line 199 "parser.yy"
                                           {
    yylhs.value.as < Node* > () = new Node("Statement", "Assign", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1107 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 34: // Statement: Identifier LEFT_BRACKET Expression RIGHT_BRACKET ASSIGN Expression SEMICOLON
#line 204 "parser.yy"
                                                                                 {
    yylhs.value.as < Node* > () = new Node("Statement", "ArrayAssign", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[6].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[4].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1118 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 35: // ExpressionList: Expression
#line 213 "parser.yy"
               { yylhs.value.as < std::list<Node*> > () = std::list<Node*>{yystack_[0].value.as < Node* > ()}; }
#line 1124 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 36: // ExpressionList: Expression COMMA ExpressionList
#line 214 "parser.yy"
                                    { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); yylhs.value.as < std::list<Node*> > ().push_front(yystack_[2].value.as < Node* > ()); }
#line 1130 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 37: // ExpressionList: %empty
#line 215 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1136 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 38: // Expression: Expression AND Expression
#line 219 "parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("Expression", "And", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1146 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 39: // Expression: Expression OR Expression
#line 224 "parser.yy"
                             {
    yylhs.value.as < Node* > () = new Node("Expression", "Or", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1156 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 40: // Expression: Expression LESS_THAN Expression
#line 229 "parser.yy"
                                    {
    yylhs.value.as < Node* > () = new Node("Expression", "LessThan", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1166 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 41: // Expression: Expression GREATER_THAN Expression
#line 234 "parser.yy"
                                       {
    yylhs.value.as < Node* > () = new Node("Expression", "GreaterThan", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1176 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 42: // Expression: Expression ADD Expression
#line 239 "parser.yy"
                              {
    yylhs.value.as < Node* > () = new Node("Expression", "Add", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1186 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 43: // Expression: Expression SUBTRACT Expression
#line 244 "parser.yy"
                                   {
    yylhs.value.as < Node* > () = new Node("Expression", "Subtract", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1196 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 44: // Expression: Expression MULTIPLY Expression
#line 249 "parser.yy"
                                   {
    yylhs.value.as < Node* > () = new Node("Expression", "Multiply", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1206 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 45: // Expression: Expression EQUAL Expression
#line 254 "parser.yy"
                                {
    yylhs.value.as < Node* > () = new Node("Expression", "Equal", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1216 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 46: // Expression: Expression DIVIDE Expression
#line 259 "parser.yy"
                                 {
    yylhs.value.as < Node* > () = new Node("Expression", "Devide", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1226 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 47: // Expression: Expression LEFT_BRACKET Expression RIGHT_BRACKET
#line 264 "parser.yy"
                                                     {
    yylhs.value.as < Node* > () = new Node("Expression", "ArrayLookup", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1236 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 48: // Expression: Expression DOT LENGTH
#line 269 "parser.yy"
                          {
    yylhs.value.as < Node* > () = new Node("Expression", "ArrayLength", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1245 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 49: // Expression: Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS
#line 273 "parser.yy"
                                                                                {
    yylhs.value.as < Node* > () = new Node("Expression", "Call", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[5].value.as < Node* > ());
    add_child(yylhs.value.as < Node* > (), yystack_[3].value.as < Node* > ());
    add_children(yylhs.value.as < Node* > (), yystack_[1].value.as < std::list<Node*> > ());
  }
#line 1256 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 50: // Expression: INTEGER_LITERAL
#line 279 "parser.yy"
                    {
    yylhs.value.as < Node* > () = new Node("Expression", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1264 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 51: // Expression: TRUE
#line 282 "parser.yy"
         {
    yylhs.value.as < Node* > () = new Node("Expression", "True", yylineno);
  }
#line 1272 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 52: // Expression: FALSE
#line 285 "parser.yy"
          {
    yylhs.value.as < Node* > () = new Node("Expression", "False", yylineno);
  }
#line 1280 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 53: // Expression: Identifier
#line 288 "parser.yy"
               {
    yylhs.value.as < Node* > () = new Node("Expression", yystack_[0].value.as < Node* > ()->value, yylineno);
  }
#line 1288 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 54: // Expression: THIS
#line 291 "parser.yy"
         {
    yylhs.value.as < Node* > () = new Node("Expression", "This", yylineno);
  }
#line 1296 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 55: // Expression: NEW INT LEFT_BRACKET Expression RIGHT_BRACKET
#line 294 "parser.yy"
                                                  {
    yylhs.value.as < Node* > () = new Node("Expression", "NewArray", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[1].value.as < Node* > ());
  }
#line 1305 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 56: // Expression: NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS
#line 298 "parser.yy"
                                                      {
    yylhs.value.as < Node* > () = new Node("Expression", "NewObject", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[2].value.as < Node* > ());
  }
#line 1314 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 57: // Expression: NOT Expression
#line 302 "parser.yy"
                   {
    yylhs.value.as < Node* > () = new Node("Expression", "Not", yylineno);
    add_child(yylhs.value.as < Node* > (), yystack_[0].value.as < Node* > ());
  }
#line 1323 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 58: // Expression: LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS
#line 306 "parser.yy"
                                                  {
    yylhs.value.as < Node* > () = yystack_[1].value.as < Node* > ();
  }
#line 1331 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;

  case 59: // Identifier: IDENTIFIER
#line 312 "parser.yy"
               {
    yylhs.value.as < Node* > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno);
  }
#line 1339 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"
    break;


#line 1343 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"

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


  const signed char parser::yypact_ninf_ = -87;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      15,    22,    33,    44,    11,   -87,    11,   -87,    44,   -87,
      39,   -20,   -87,    70,     6,    11,    34,    -2,    45,   -87,
     -87,   -87,    49,     6,    11,   -87,    51,    80,    11,    56,
     -87,   -87,    10,     6,    84,    61,   -87,   -87,    67,    64,
      66,    -2,   -87,   -87,   -87,     4,    67,    67,   -87,   100,
     -87,   -87,    87,    69,    11,    75,    71,     0,   201,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,   -11,
     -87,    81,    86,    82,    67,    85,   -87,   350,   335,   365,
     365,   320,   370,   370,     0,     0,   218,   -87,    97,    95,
      60,    -2,   235,   -87,   -87,    67,    11,   103,   105,    -7,
     108,   -87,    74,    60,   -87,     8,   -87,   -87,   109,   183,
     110,    67,    67,   113,    -7,     8,    67,    67,   -87,    67,
      67,   -87,    67,   111,   252,   269,   -87,   -87,   286,   126,
     303,   145,   -87,    -7,    -7,    -7,   117,   125,   118,   -87,
     127,   146,   -87,   -87,   -87,    67,   130,    -7,   164,   -87,
     -87,   -87
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     5,     0,     1,     0,     2,     5,    59,
       0,     0,     4,     0,    16,     0,     0,     0,    24,    23,
      17,    18,     0,    16,     0,    25,     0,     0,     0,     0,
       6,    15,     0,    16,     0,     0,    22,     8,     0,     0,
       0,    21,    51,    52,    54,     0,     0,     0,    50,     0,
      53,     7,     0,     0,     0,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       9,     0,     0,    19,     0,     0,    58,    38,    39,    40,
      41,    45,    42,    43,    44,    46,     0,    48,     0,     0,
      12,    21,     0,    56,    47,    37,     0,     0,     0,    27,
       0,    13,     0,    12,    14,    25,    20,    55,     0,    35,
       0,     0,     0,     0,    27,     0,     0,     0,    11,     0,
       0,    49,    37,     0,     0,     0,    28,    26,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,    33,
       0,    29,    31,    32,    10,     0,     0,     0,     0,     3,
      30,    34
  };

  const short
  parser::yypgoto_[] =
  {
     -87,   -87,   -87,   153,   -87,   -86,   -87,    72,   -87,    38,
     -87,    83,   -16,    58,   -71,    54,    -8,    -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     7,     8,    20,    21,   102,   103,    22,
      23,    53,    24,   113,   104,   108,   109,    50
  };

  const short
  parser::yytable_[] =
  {
      10,    28,    11,    97,   101,    98,    18,    19,    14,    17,
      25,    26,    55,    25,    18,    19,    87,   101,     1,    25,
      32,    99,    63,    15,    35,    54,     4,     9,   114,    25,
      49,     9,    68,     5,    69,   100,     9,    25,    57,    58,
     119,    56,     9,   114,     9,   120,    37,    38,     6,     9,
      73,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    31,   140,   141,   142,    88,    92,    13,    18,    19,
      97,    39,    98,    16,    27,    54,   150,    29,    30,    33,
      42,    43,    44,    45,    46,    34,   105,    25,    99,    36,
      40,    41,   110,    51,    71,   115,    52,    47,     9,   105,
      72,    75,   100,   124,   125,     9,    48,    74,   128,   129,
     115,   130,   131,    89,    90,   117,    93,    91,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    95,    96,   115,
     115,   115,    68,   111,    69,   112,    70,   148,   116,   133,
     121,   123,   126,   115,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   143,   144,   145,   146,   147,    68,   149,
      69,    12,   137,    59,    60,    61,    62,    63,    64,    65,
      66,    67,   127,     0,   106,   118,   132,    68,     0,    69,
       0,   139,    59,    60,    61,    62,    63,    64,    65,    66,
      67,     0,     0,     0,     0,     0,    68,     0,    69,     0,
     151,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,    68,     0,    69,   122,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
       0,     0,    76,    68,     0,    69,    59,    60,    61,    62,
      63,    64,    65,    66,    67,     0,     0,     0,     0,     0,
      68,    94,    69,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,    68,   107,    69,
      59,    60,    61,    62,    63,    64,    65,    66,    67,     0,
       0,     0,     0,   134,    68,     0,    69,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
     135,    68,     0,    69,    59,    60,    61,    62,    63,    64,
      65,    66,    67,     0,     0,     0,     0,   136,    68,     0,
      69,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,    68,   138,    69,    59,    60,
      61,    62,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,    68,    59,    69,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,    68,     0,    69,
      61,    62,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,    68,     0,    69,    -1,    -1,    63,    64,    65,
      66,    67,    63,     0,     0,    66,    67,    68,     0,    69,
       0,     0,    68,     0,    69
  };

  const short
  parser::yycheck_[] =
  {
       4,    17,     6,    10,    90,    12,     8,     9,    28,     3,
      14,    15,     8,    17,     8,     9,    27,   103,     3,    23,
      24,    28,    22,    43,    28,    41,     4,    38,    99,    33,
      38,    38,    32,     0,    34,    42,    38,    41,    46,    47,
      32,    45,    38,   114,    38,    37,    36,    37,     4,    38,
      54,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    23,   133,   134,   135,    69,    74,    28,     8,     9,
      10,    33,    12,     3,    40,    91,   147,    32,    29,    28,
      13,    14,    15,    16,    17,     5,    90,    91,    28,    33,
       6,    30,    96,    29,     7,    99,    30,    30,    38,   103,
      31,    30,    42,   111,   112,    38,    39,    32,   116,   117,
     114,   119,   120,    32,    28,    41,    31,    35,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    30,    33,   133,
     134,   135,    32,    30,    34,    30,    36,   145,    30,    28,
      31,    31,    29,   147,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    36,    29,    37,    29,    11,    32,    29,
      34,     8,    36,    18,    19,    20,    21,    22,    23,    24,
      25,    26,   114,    -1,    91,   103,   122,    32,    -1,    34,
      -1,    36,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    -1,
      36,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    31,    32,    -1,    34,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    31,    32,    -1,    34,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    32,    -1,    34,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    -1,    31,    32,    -1,
      34,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32,    18,    34,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    34,    20,    21,    22,    23,    24,
      25,    26,    22,    -1,    -1,    25,    26,    32,    -1,    34,
      -1,    -1,    32,    -1,    34
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,    46,    47,     4,     0,     4,    48,    49,    38,
      62,    62,    48,    28,    28,    43,     3,     3,     8,     9,
      50,    51,    54,    55,    57,    62,    62,    40,    57,    32,
      29,    54,    62,    28,     5,    62,    33,    36,    37,    54,
       6,    30,    13,    14,    15,    16,    17,    30,    39,    61,
      62,    29,    30,    56,    57,     8,    62,    61,    61,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    32,    34,
      36,     7,    31,    62,    32,    30,    31,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    27,    62,    32,
      28,    35,    61,    31,    33,    30,    33,    10,    12,    28,
      42,    50,    52,    53,    59,    62,    56,    33,    60,    61,
      62,    30,    30,    58,    59,    62,    30,    41,    52,    32,
      37,    31,    35,    31,    61,    61,    29,    58,    61,    61,
      61,    61,    60,    28,    31,    31,    31,    36,    33,    36,
      59,    59,    59,    36,    29,    37,    29,    11,    61,    29,
      59,    36
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    45,    46,    47,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    57,    57,    57,    57,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    62
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,    18,     2,     0,     5,     7,     3,     5,
      12,     2,     0,     1,     1,     2,     0,     1,     1,     2,
       4,     0,     3,     1,     1,     1,     2,     0,     3,     5,
       7,     5,     5,     4,     7,     1,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     6,
       1,     1,     1,     1,     1,     5,     4,     2,     3,     1
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
  "Goal", "MainClass", "ClassDeclarationList", "ClassDeclaration",
  "VarDeclaration", "MethodDeclaration", "MethodBody", "MethodBodyItem",
  "ClassBody", "ClassBodyItem", "ParameterList", "Type", "StatementList",
  "Statement", "ExpressionList", "Expression", "Identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    61,    61,    70,    79,    83,    87,    92,   102,   107,
     118,   131,   135,   139,   140,   144,   148,   152,   153,   157,
     158,   159,   163,   164,   165,   166,   170,   171,   175,   179,
     184,   190,   195,   199,   204,   213,   214,   215,   219,   224,
     229,   234,   239,   244,   249,   254,   259,   264,   269,   273,
     279,   282,   285,   288,   291,   294,   298,   302,   306,   312
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
#line 1950 "/home/lajna/code/BTH/DV1656/assignment2/parser.tab.cc"

#line 317 "parser.yy"

