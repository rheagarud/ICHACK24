%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%
[0-9]+\.[0-9]+                      {fprintf (stdout, "Flt : %s\n", yytext); yylval.flt = strtof(yytext, NULL); return FLT;}
[0-9]+                              {fprintf (stdout, "Num : %s\n", yytext); yylval.num = strtod(yytext, 0); return NUM;}
[a-z](\_[0-9]+)?                    {fprintf (stdout, "Name : %s\n", yytext); yylval.str = new std::string(yytext); return NAME;} // can be variable or function name
\(                                  {fprintf (stdout, "( : %s\n", yytext); return LBRACKET;}
\)                                  {fprintf (stdout, ") : %s\n", yytext); return RBRACKET;}
\*\*                                {fprintf (stdout, "** : %s\n", yytext); return POW;}
\*                                  {fprintf (stdout, "* : %s\n", yytext); return MULT;}
\+                                  {fprintf (stdout, "+ : %s\n", yytext); return PLUS;}
\-                                  {fprintf (stdout, "- : %s\n", yytext); return MINUS;}
\/                                  {fprintf (stdout, "/ : %s\n", yytext); return DIV;}
\^                                  {fprintf (stdout, "^ : %s\n", yytext); return POW;}
\>\=                                {fprintf (stdout, ">= : %s\n", yytext); return GTE;}   
\<\=                                {fprintf (stdout, "<= : %s\n", yytext); return LTE;}
\>                                  {fprintf (stdout, "> : %s\n", yytext); return GT;}
\<                                  {fprintf (stdout, "> : %s\n", yytext); return LT;}   
\=                                  {fprintf (stdout, "= : %s\n", yytext); return EQUALS;}
[%]                                 {fprintf (stdout, "= : %s\n", yytext); return MOD;}
[ \t\r\n]+		                    {;}
.                                   {fprintf(stdout,"Invalid token : %s\n",yytext);exit(1);}


%%

void yyerror (char const *s){
    fprintf (stderr, "Parse error : %s\n", yytext);
    exit(1);
}