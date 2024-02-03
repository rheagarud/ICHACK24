%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern std::vector<const Expression*>g_root; // A way of getting the AST out

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
}

%token NUM NAME
%token LBRACKET RBRACKET PLUS MINUS MULT DIV MOD POW
%token LT GT LTE GTE EQUALS 
%right EQUALS
%left LT GT LTE GTE
%left PLUS MINUS
%left MULT DIV MOD
%right POW

%type <expr> TERM FACTOR PREC2 PREC3 PREC4 PREC5 PREC6 PREC7 PREC8 PREC9 PREC10
%type <expr> PREC11 PREC12 PREC14 PREC15
%type <str> NAME
%type <num> NUM

%start ROOT
%%

ROOT : PREC6                                                                  { g_root = *$1;}

PREC6 : PREC6 LT PREC5                                                        {$$ = std::cout << "LessThan" << std::endl; $$ = new ArithCompOperator($1, $3, LESS);}
      | PREC6 LTE PREC5                                                       {$$ = new ArithCompOperator($1, $4, LESSOREQUAL);}
      | PREC6 GT PREC5                                                        {$$ = new ArithCompOperator($1, $3, MORE);}
      | PREC6 GTE PREC5                                                       {$$ = new ArithCompOperator($1, $4, MOREOREQUAL);}
      | PREC6 EQUALS PREC5                                                    {$$ = new ArithCompOperator($1, $3, EQUALS);}
      | PREC5                                                                 {$$ = $1;}


PREC5 : PREC4                                                                 {$$ = $1;}

PREC4 : PREC4 T_PLUS PREC3                                                    {$$ = new ArithCompOperator($1, $3, ADDITION);}
      | PREC4 T_MINUS PREC3                                                   {$$ = new ArithCompOperator($1, $3, SUBTRACTION);}
      | PREC3                                                                 {$$ = $1;}

PREC3 : PREC3 MULT PREC2                                                      {$$ = new ArithCompOperator($1, $3, MULTIPLICATION);}
      | PREC3 DIV PREC2                                                       {$$ = new ArithCompOperator($1, $3, DIVISION);}
      | PREC3 MOD PREC2                                                       {$$ = new ArithCompOperator($1, $3, MODULO);}
      | PREC2                                                                 {$$ = $1;}

PREC2 : PREC2 POW FACTOR                                                      {$$ = new ArithCompOperator($1, $3, POWER);}
      | FACTOR                                                                {$$ = $1;}

FACTOR : LBRACKET PREC4 RBRACKET                                              {$$ = $2;}
       | T_NUM                                                                {$$ = $1;}
       | T_NAME                                                               {std::cout << "T_NAME " << *$1 << std::endl; $$ = new Variable(*$1); delete $1;}


%%

std::vector<const Expression*> g_root; // Definition of variable (to match declaration earlier)

std::vector<const Expression*> parseAST()
{
  /* g_root=0; */
  yyparse();
  return g_root;
}