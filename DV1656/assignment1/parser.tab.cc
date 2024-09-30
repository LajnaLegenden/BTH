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
#line 13 "parser.yy"

  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;

#line 54 "parser.tab.cc"


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
#line 127 "parser.tab.cc"

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
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_Identifier: // Identifier
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
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
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_Identifier: // Identifier
        value.move< Node * > (YY_MOVE (that.value));
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
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_Identifier: // Identifier
        value.copy< Node * > (that.value);
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
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_Identifier: // Identifier
        value.move< Node * > (that.value);
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
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_Type: // Type
      case symbol_kind::S_ParameterList: // ParameterList
      case symbol_kind::S_Parameter: // Parameter
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_Identifier: // Identifier
        yylhs.value.emplace< Node * > ();
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
  case 2: // Goal: MainClass ClassDeclarationList "end of file"
#line 39 "parser.yy"
                                         { yylhs.value.as < Node * > () = new Node("Goal", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); root = yylhs.value.as < Node * > (); }
#line 833 "parser.tab.cc"
    break;

  case 3: // MainClass: PUBLIC CLASS Identifier LEFT_BRACE PUBLIC STATIC VOID MAIN LEFT_PARENTHESIS STRING LEFT_BRACKET RIGHT_BRACKET Identifier RIGHT_PARENTHESIS LEFT_BRACE StatementList RIGHT_BRACE RIGHT_BRACE
#line 44 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("MainClass", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[15].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); }
#line 839 "parser.tab.cc"
    break;

  case 4: // ClassDeclarationList: ClassDeclaration ClassDeclarationList
#line 48 "parser.yy"
                                            { yylhs.value.as < Node * > () = new Node("ClassDeclarationList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 845 "parser.tab.cc"
    break;

  case 5: // ClassDeclarationList: %empty
#line 49 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("ClassDeclarationList", "Empty", yylineno); }
#line 851 "parser.tab.cc"
    break;

  case 6: // ClassDeclaration: CLASS Identifier LEFT_BRACE VarDeclarationList MethodDeclarationList RIGHT_BRACE
#line 54 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("ClassDeclaration", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 857 "parser.tab.cc"
    break;

  case 7: // VarDeclarationList: VarDeclaration VarDeclarationList
#line 58 "parser.yy"
                                        { yylhs.value.as < Node * > () = new Node("VarDeclarationList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 863 "parser.tab.cc"
    break;

  case 8: // VarDeclarationList: %empty
#line 59 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("VarDeclarationList", "Empty", yylineno); }
#line 869 "parser.tab.cc"
    break;

  case 9: // MethodDeclarationList: MethodDeclaration MethodDeclarationList
#line 63 "parser.yy"
                                              { yylhs.value.as < Node * > () = new Node("MethodDeclarationList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 875 "parser.tab.cc"
    break;

  case 10: // MethodDeclarationList: %empty
#line 64 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("MethodDeclarationList", "Empty", yylineno); }
#line 881 "parser.tab.cc"
    break;

  case 11: // VarDeclaration: Type Identifier SEMICOLON
#line 68 "parser.yy"
                                { yylhs.value.as < Node * > () = new Node("VarDeclaration", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 887 "parser.tab.cc"
    break;

  case 12: // MethodDeclaration: PUBLIC Type Identifier LEFT_PARENTHESIS ParameterList RIGHT_PARENTHESIS LEFT_BRACE VarDeclarationList StatementList RETURN Expression SEMICOLON RIGHT_BRACE
#line 73 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("MethodDeclaration", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[11].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[10].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[8].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); }
#line 893 "parser.tab.cc"
    break;

  case 13: // Type: INT LEFT_BRACKET RIGHT_BRACKET
#line 77 "parser.yy"
                                     { yylhs.value.as < Node * > () = new Node("Type", "int[]", yylineno); }
#line 899 "parser.tab.cc"
    break;

  case 14: // Type: BOOLEAN
#line 78 "parser.yy"
              { yylhs.value.as < Node * > () = new Node("Type", "boolean", yylineno); }
#line 905 "parser.tab.cc"
    break;

  case 15: // Type: INT
#line 79 "parser.yy"
          { yylhs.value.as < Node * > () = new Node("Type", "int", yylineno); }
#line 911 "parser.tab.cc"
    break;

  case 16: // Type: Identifier
#line 80 "parser.yy"
                 { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 917 "parser.tab.cc"
    break;

  case 17: // ParameterList: Type Identifier Parameter
#line 84 "parser.yy"
                                { yylhs.value.as < Node * > () = new Node("ParameterList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 923 "parser.tab.cc"
    break;

  case 18: // ParameterList: %empty
#line 85 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("ParameterList", "Empty", yylineno); }
#line 929 "parser.tab.cc"
    break;

  case 19: // Parameter: COMMA Type Identifier Parameter
#line 89 "parser.yy"
                                      { yylhs.value.as < Node * > () = new Node("Parameter", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 935 "parser.tab.cc"
    break;

  case 20: // Parameter: %empty
#line 90 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("Parameter", "Empty", yylineno); }
#line 941 "parser.tab.cc"
    break;

  case 21: // StatementList: Statement StatementList
#line 94 "parser.yy"
                              { yylhs.value.as < Node * > () = new Node("StatementList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 947 "parser.tab.cc"
    break;

  case 22: // StatementList: %empty
#line 95 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("StatementList", "Empty", yylineno); }
#line 953 "parser.tab.cc"
    break;

  case 23: // Statement: LEFT_BRACE StatementList RIGHT_BRACE
#line 99 "parser.yy"
                                           { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 959 "parser.tab.cc"
    break;

  case 24: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement ELSE Statement
#line 101 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 965 "parser.tab.cc"
    break;

  case 25: // Statement: IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 103 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 971 "parser.tab.cc"
    break;

  case 26: // Statement: WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
#line 105 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("WhileStatement", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 977 "parser.tab.cc"
    break;

  case 27: // Statement: SYSTEM_OUT_PRINTLN LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS SEMICOLON
#line 107 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("PrintStatement", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); }
#line 983 "parser.tab.cc"
    break;

  case 28: // Statement: Identifier ASSIGN Expression SEMICOLON
#line 109 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("AssignStatement", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 989 "parser.tab.cc"
    break;

  case 29: // Statement: Identifier LEFT_BRACKET Expression RIGHT_BRACKET ASSIGN Expression SEMICOLON
#line 111 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("ArrayAssignStatement", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 995 "parser.tab.cc"
    break;

  case 30: // Expression: Expression AND Expression
#line 115 "parser.yy"
                                { yylhs.value.as < Node * > () = new Node("AndExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1001 "parser.tab.cc"
    break;

  case 31: // Expression: Expression OR Expression
#line 116 "parser.yy"
                               { yylhs.value.as < Node * > () = new Node("OrExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1007 "parser.tab.cc"
    break;

  case 32: // Expression: Expression LESS_THAN Expression
#line 117 "parser.yy"
                                      { yylhs.value.as < Node * > () = new Node("LessThanExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1013 "parser.tab.cc"
    break;

  case 33: // Expression: Expression GREATER_THAN Expression
#line 118 "parser.yy"
                                         { yylhs.value.as < Node * > () = new Node("GreaterThanExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1019 "parser.tab.cc"
    break;

  case 34: // Expression: Expression EQUAL Expression
#line 119 "parser.yy"
                                  { yylhs.value.as < Node * > () = new Node("EqualExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1025 "parser.tab.cc"
    break;

  case 35: // Expression: Expression ADD Expression
#line 120 "parser.yy"
                                { yylhs.value.as < Node * > () = new Node("AddExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1031 "parser.tab.cc"
    break;

  case 36: // Expression: Expression SUBTRACT Expression
#line 121 "parser.yy"
                                     { yylhs.value.as < Node * > () = new Node("SubtractExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1037 "parser.tab.cc"
    break;

  case 37: // Expression: Expression MULTIPLY Expression
#line 122 "parser.yy"
                                     { yylhs.value.as < Node * > () = new Node("MultiplyExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1043 "parser.tab.cc"
    break;

  case 38: // Expression: Expression DIVIDE Expression
#line 123 "parser.yy"
                                   { yylhs.value.as < Node * > () = new Node("DivideExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1049 "parser.tab.cc"
    break;

  case 39: // Expression: Expression LEFT_BRACKET Expression RIGHT_BRACKET
#line 124 "parser.yy"
                                                       { yylhs.value.as < Node * > () = new Node("ArrayAccessExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 1055 "parser.tab.cc"
    break;

  case 40: // Expression: Expression DOT LENGTH
#line 125 "parser.yy"
                            { yylhs.value.as < Node * > () = new Node("ArrayLengthExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); }
#line 1061 "parser.tab.cc"
    break;

  case 41: // Expression: Expression DOT Identifier LEFT_PARENTHESIS ExpressionList RIGHT_PARENTHESIS
#line 126 "parser.yy"
                                                                                  { yylhs.value.as < Node * > () = new Node("MethodCallExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 1067 "parser.tab.cc"
    break;

  case 42: // Expression: INTEGER_LITERAL
#line 127 "parser.yy"
                      { yylhs.value.as < Node * > () = new Node("IntegerLiteral", yystack_[0].value.as < std::string > (), yylineno); }
#line 1073 "parser.tab.cc"
    break;

  case 43: // Expression: TRUE
#line 128 "parser.yy"
           { yylhs.value.as < Node * > () = new Node("BooleanLiteral", "true", yylineno); }
#line 1079 "parser.tab.cc"
    break;

  case 44: // Expression: FALSE
#line 129 "parser.yy"
            { yylhs.value.as < Node * > () = new Node("BooleanLiteral", "false", yylineno); }
#line 1085 "parser.tab.cc"
    break;

  case 45: // Expression: Identifier
#line 130 "parser.yy"
                 { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1091 "parser.tab.cc"
    break;

  case 46: // Expression: THIS
#line 131 "parser.yy"
           { yylhs.value.as < Node * > () = new Node("ThisExpression", "", yylineno); }
#line 1097 "parser.tab.cc"
    break;

  case 47: // Expression: NEW INT LEFT_BRACKET Expression RIGHT_BRACKET
#line 132 "parser.yy"
                                                    { yylhs.value.as < Node * > () = new Node("NewIntArrayExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); }
#line 1103 "parser.tab.cc"
    break;

  case 48: // Expression: NEW Identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS
#line 133 "parser.yy"
                                                        { yylhs.value.as < Node * > () = new Node("NewObjectExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); }
#line 1109 "parser.tab.cc"
    break;

  case 49: // Expression: NOT Expression
#line 134 "parser.yy"
                     { yylhs.value.as < Node * > () = new Node("NotExpression", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1115 "parser.tab.cc"
    break;

  case 50: // Expression: LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS
#line 135 "parser.yy"
                                                    { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1121 "parser.tab.cc"
    break;

  case 51: // ExpressionList: Expression ExpressionList
#line 139 "parser.yy"
                                { yylhs.value.as < Node * > () = new Node("ExpressionList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1127 "parser.tab.cc"
    break;

  case 52: // ExpressionList: COMMA Expression ExpressionList
#line 140 "parser.yy"
                                      { yylhs.value.as < Node * > () = new Node("ExpressionList", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 1133 "parser.tab.cc"
    break;

  case 53: // ExpressionList: %empty
#line 141 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("ExpressionList", "Empty", yylineno); }
#line 1139 "parser.tab.cc"
    break;

  case 54: // Identifier: IDENTIFIER
#line 145 "parser.yy"
                 { yylhs.value.as < Node * > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno); }
#line 1145 "parser.tab.cc"
    break;


#line 1149 "parser.tab.cc"

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


  const signed char parser::yypact_ninf_ = -118;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      12,    15,    25,    27,   -10,  -118,   -10,    41,    27,  -118,
      17,    20,  -118,  -118,    47,    -3,     3,    18,  -118,    49,
      -3,   -10,  -118,    50,    23,    -3,    24,    49,  -118,    22,
      54,  -118,   -10,  -118,  -118,  -118,    30,    31,    56,    -3,
      32,   -10,    39,    44,    28,    46,   -10,    -3,  -118,    -3,
      53,   -10,    -9,    55,    28,    51,    58,    -9,    59,    57,
      -9,   -11,    -9,  -118,   101,   101,    63,   101,   101,  -118,
     101,   101,    64,  -118,  -118,  -118,     0,   101,   101,  -118,
     214,  -118,   231,  -118,   248,   157,   265,   176,    65,    48,
      66,   333,   282,   101,   101,   101,   101,   101,   101,   101,
     101,   101,    -9,   101,   -15,    -9,    74,    83,    76,  -118,
    -118,   101,    89,  -118,   333,   333,   333,   333,   333,   333,
     333,   333,   333,    85,   299,  -118,    91,  -118,  -118,  -118,
     101,   316,  -118,    -9,  -118,    52,   195,  -118,  -118,   101,
     135,    92,  -118,   135,  -118,  -118,  -118
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     5,     0,     1,     0,     0,     5,    54,
       0,     0,     2,     4,     0,     8,     0,    15,    14,    10,
       8,     0,    16,     0,     0,     0,     0,    10,     7,     0,
       0,    13,     0,     6,     9,    11,     0,     0,     0,    18,
       0,     0,     0,     0,    20,     0,     0,     0,    17,     8,
       0,     0,    22,     0,    20,     0,     0,    22,     0,     0,
      22,     0,    22,    19,     0,     0,     0,     0,     0,    21,
       0,     0,     0,    43,    44,    46,     0,     0,     0,    42,
       0,    45,     0,    23,     0,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       3,     0,     0,    50,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    25,     0,    40,     0,    26,    27,    12,
       0,     0,    48,     0,    39,    53,     0,    47,    24,     0,
      53,     0,    29,    53,    51,    41,    52
  };

  const signed char
  parser::yypgoto_[] =
  {
    -118,  -118,  -118,   115,  -118,   -16,    98,  -118,  -118,    -7,
    -118,    72,   -48,   -95,     9,  -117,    -4
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     7,     8,    19,    26,    20,    27,    21,
      42,    48,    59,    60,   140,   141,    81
  };

  const unsigned char
  parser::yytable_[] =
  {
      10,    55,    11,    56,    28,    17,    18,   123,    89,    66,
     127,    22,    69,   125,    72,     1,    22,    29,    32,     4,
      57,    22,    70,   144,     9,     5,   146,    71,    37,     9,
       9,     6,    41,    52,    58,    22,     9,    44,   138,     9,
      51,    12,    50,    22,    23,    22,    14,    54,    61,    15,
      16,    24,    25,    61,    33,    30,    61,    31,    61,    35,
      36,    38,    39,    40,    47,    43,    73,    74,    75,    76,
      77,    45,    90,    80,    82,    49,    84,    85,    46,    86,
      87,   111,    64,    78,    62,    53,    91,    92,   139,    65,
      67,     9,    79,    83,    88,   110,   133,   112,    61,    68,
     126,    61,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   128,   124,   129,   130,    73,    74,    75,    76,    77,
     131,   132,   135,    13,   145,    34,    63,     0,     0,    61,
       0,     0,    78,     0,     0,     0,     0,     0,     0,   136,
       9,    79,     0,     0,     0,     0,     0,     0,   143,    73,
      74,    75,    76,    77,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     0,     0,     0,    78,     0,   103,     0,
     104,   139,     0,     0,     9,    79,    93,    94,    95,    96,
      97,    98,    99,   100,   101,     0,     0,     0,     0,     0,
     103,     0,   104,     0,   107,    93,    94,    95,    96,    97,
      98,    99,   100,   101,     0,     0,     0,     0,     0,   103,
       0,   104,     0,   109,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     0,     0,     0,     0,     0,   103,     0,
     104,     0,   142,    93,    94,    95,    96,    97,    98,    99,
     100,   101,     0,     0,     0,     0,   102,   103,     0,   104,
      93,    94,    95,    96,    97,    98,    99,   100,   101,     0,
       0,     0,     0,   105,   103,     0,   104,    93,    94,    95,
      96,    97,    98,    99,   100,   101,     0,     0,     0,     0,
     106,   103,     0,   104,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     0,     0,     0,     0,     0,   103,   108,
     104,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       0,     0,     0,     0,   113,   103,     0,   104,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     0,     0,     0,
       0,     0,   103,   134,   104,    93,    94,    95,    96,    97,
      98,    99,   100,   101,     0,     0,     0,     0,     0,   103,
     137,   104,    93,    94,    95,    96,    97,    98,    99,   100,
     101,     0,     0,     0,     0,     0,   103,     0,   104
  };

  const short
  parser::yycheck_[] =
  {
       4,    10,     6,    12,    20,     8,     9,   102,     8,    57,
     105,    15,    60,    28,    62,     3,    20,    21,    25,     4,
      29,    25,    33,   140,    39,     0,   143,    38,    32,    39,
      39,     4,    39,    49,    43,    39,    39,    41,   133,    39,
      47,     0,    46,    47,    41,    49,    29,    51,    52,    29,
       3,    33,     3,    57,    30,     5,    60,    34,    62,    37,
       6,    31,    31,     7,    36,    33,    14,    15,    16,    17,
      18,    32,    76,    64,    65,    29,    67,    68,    34,    70,
      71,    33,    31,    31,    29,    32,    77,    78,    36,    31,
      31,    39,    40,    30,    30,    30,    11,    31,   102,    42,
     104,   105,    93,    94,    95,    96,    97,    98,    99,   100,
     101,    37,   103,    30,    38,    14,    15,    16,    17,    18,
     111,    32,    31,     8,    32,    27,    54,    -1,    -1,   133,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,   130,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,   139,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    -1,    -1,    39,    40,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    35,    -1,    37,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    35,    -1,    37,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      35,    -1,    37,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    -1,    35,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    32,    33,    -1,    35,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      32,    33,    -1,    35,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    32,    33,    -1,    35,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,    47,    48,     4,     0,     4,    49,    50,    39,
      62,    62,     0,    49,    29,    29,     3,     8,     9,    51,
      53,    55,    62,    41,    33,     3,    52,    54,    51,    62,
       5,    34,    55,    30,    52,    37,     6,    62,    31,    31,
       7,    55,    56,    33,    62,    32,    34,    36,    57,    29,
      62,    55,    51,    32,    62,    10,    12,    29,    43,    58,
      59,    62,    29,    57,    31,    31,    58,    31,    42,    58,
      33,    38,    58,    14,    15,    16,    17,    18,    31,    40,
      60,    62,    60,    30,    60,    60,    60,    60,    30,     8,
      62,    60,    60,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    32,    33,    35,    32,    32,    37,    34,    37,
      30,    33,    31,    32,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    59,    60,    28,    62,    59,    37,    30,
      38,    60,    32,    11,    34,    31,    60,    34,    59,    36,
      60,    61,    37,    60,    61,    32,    61
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    46,    47,    48,    49,    49,    50,    51,    51,    52,
      52,    53,    54,    55,    55,    55,    55,    56,    56,    57,
      57,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    61,    62
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,    18,     2,     0,     6,     2,     0,     2,
       0,     3,    13,     3,     1,     1,     1,     3,     0,     4,
       0,     2,     0,     3,     7,     5,     5,     5,     4,     7,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       3,     6,     1,     1,     1,     1,     1,     5,     4,     2,
       3,     2,     3,     0,     1
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
  "RETURN", "SYSTEM_OUT_PRINTLN", "COMMENT", "ERROR", "$accept", "Goal",
  "MainClass", "ClassDeclarationList", "ClassDeclaration",
  "VarDeclarationList", "MethodDeclarationList", "VarDeclaration",
  "MethodDeclaration", "Type", "ParameterList", "Parameter",
  "StatementList", "Statement", "Expression", "ExpressionList",
  "Identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    39,    39,    43,    48,    49,    53,    58,    59,    63,
      64,    68,    72,    77,    78,    79,    80,    84,    85,    89,
      90,    94,    95,    99,   100,   102,   104,   106,   108,   110,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   139,   140,   141,   145
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
#line 1746 "parser.tab.cc"

#line 148 "parser.yy"

