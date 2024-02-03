%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%
[0-9]+                              {fprintf (stderr, "Num : %s\n", yytext); yylval.num = strtod(yytext, 0); return NUM;}
[a-z](\_[0-9]+)?                    {fprintf (stderr, "Name : %s\n", yytext); yylval.str = new std::string(yytext); return T_NAME;} // can be variable or function name
\(                                  {fprintf (stderr, "( : %s\n", yytext); return LBRACKET;}
\)                                  {fprintf (stderr, ") : %s\n", yytext); return RBRACKET;}
\*\*                                {fprintf (stderr, "** : %s\n", yytext); return POW;}
\*                                  {fprintf (stderr, "* : %s\n", yytext); return MULT;}
\+                                  {fprintf (stderr, "+ : %s\n", yytext); return PLUS;}
\-                                  {fprintf (stderr, "- : %s\n", yytext); return MINUS;}
\/                                  {fprintf (stderr, "/ : %s\n", yytext); return DIV;}
\^                                  {fprintf (stderr, "^ : %s\n", yytext); return POW;}
\>\=                                {fprintf (stderr, ">= : %s\n", yytext); return GTE;}   
\<\=                                {fprintf (stderr, "<= : %s\n", yytext); return LTE;}
\>                                  {fprintf (stderr, "> : %s\n", yytext); return GT;}
\<                                  {fprintf (stderr, "> : %s\n", yytext); return LT;}   
\=                                  {fprintf (stderr, "= : %s\n", yytext); return EQUALS;}
[%]                                 {fprintf (stderr, "= : %s\n", yytext); return MOD;}
[ \t\r\n]+		                    {;}
.                                   {fprintf(stderr,"Invalid token : %s\n",yytext);exit(1);}


%%

void yyerror (char const *s){
    fprintf (stderr, "Parse error : %s\n", yytext);
    exit(1);
}