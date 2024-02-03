%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression* g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

/*
  Any node in the AST is one of these things
*/
%union{
  Expression* expr;
  int num;
  std::string* str;
  float flt;
}

%token NUM NAME FLT
%token LBRACKET RBRACKET PLUS MINUS MULT DIV MOD POW
%token LT GT LTE GTE EQUALS 
%right EQUALS
%left LT GT LTE GTE
%left PLUS MINUS
%left MULT DIV MOD
%right POW

%type <expr> ROOT FACTOR PREC2 PREC3 PREC4 PREC5 PREC6 UNARY
%type <str> NAME
%type <num> NUM
%type <flt> FLT

%start ROOT
%%

ROOT : PREC6                                                                  { g_root = $1;}

PREC6 : PREC6 LT PREC5                                                        {$$ = new ArithCompOperator($1, $3, LESS);}
      | PREC6 LTE PREC5                                                       {$$ = new ArithCompOperator($1, $3, LESSOREQUAL);}
      | PREC6 GT PREC5                                                        {$$ = new ArithCompOperator($1, $3, MORE);}
      | PREC6 GTE PREC5                                                       {$$ = new ArithCompOperator($1, $3, MOREOREQUAL);}
      | PREC6 EQUALS PREC5                                                    {$$ = new ArithCompOperator($1, $3, EQUAL);}
      | PREC5                                                                  {$$ = $1;}


PREC5 : PREC4                                                                 {$$ = $1;}

PREC4 : PREC4 PLUS PREC3                                                       {std::cout << "GOING UP: ADDING " << $1->expressionType() << $3->expressionType() << std::endl; $$ = new ArithCompOperator($1, $3, ADDITION);}
      | PREC4 MINUS PREC3                                                     {$$ = new ArithCompOperator($1, $3, SUBTRACTION);}
      | PREC3                                                                 {$$ = $1;}

PREC3 : PREC3 MULT PREC2                                                      {std::cout << "GOING UP: MULT " << $1->expressionType() << $3->expressionType() << std::endl; $$ = new ArithCompOperator($1, $3, MULTIPLICATION);}
      | PREC3 DIV PREC2                                                       {$$ = new ArithCompOperator($1, $3, DIVISION);}
      | PREC3 MOD PREC2                                                       {$$ = new ArithCompOperator($1, $3, MODULO);}
      | PREC2                                                                 {$$ = $1;}

PREC2 : PREC2 POW FACTOR                                                      {$$ = new ArithCompOperator($1, $3, POWER);}
      | FACTOR                                                                {$$ = $1;}

UNARY : MINUS FACTOR                                                          {std::cout << "GOING UP: NEGATING " << $2->getIntValue() << std::endl; $$ = new Unary($2, NEGATE);}

FACTOR : LBRACKET PREC4 RBRACKET                                              {$$ = $2;}
       | NUM                                                                  {std::cout << "GOING UP: IntMade " << $1 << std::endl;$$ = new Int($1);}
       | NAME                                                                 {std::cout << "GOING UP: NAME " << *$1 << std::endl; $$ = new Variable(*$1); delete $1;}
       | UNARY                                                                {$$ = $1;}
       | FLT                                                                  {std::cout << "GOING UP: FloatMade " << $1 << std::endl; $$ = new Float($1);}
%%

const Expression* g_root; // Definition of variable (to match declaration earlier)

const Expression* parseAST()
{
  /* g_root=0; */
  yyparse();
  return g_root;
}