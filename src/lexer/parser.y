%{
#define YYSTYPE char*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "../comment.h"

extern int lineno;
extern FILE* yyin;

%}


%token COMMENT
%token IDENT
%token AT
%token COMMA
%token SEMI
%token NUMBER
%token LPAR RPAR

%start instructions

%%

instructions:
    instr SEMI instructions
    | instr SEMI
    ;

instr:
      LPAR NUMBER RPAR COMMENT AT IDENT variable   { new_comment( $6, $7, lineno); printf("%d\n", lineno); }
    | LPAR NUMBER RPAR COMMENT AT IDENT            { new_comment( $6, NULL, lineno); printf("%d\n", lineno); }
    | LPAR NUMBER RPAR COMMENT AT                  { new_comment( NULL, NULL, lineno); printf("%d\n", lineno); }
    ;

variable:
    IDENT COMMA variable
    | IDENT
    ;


%%

int yyerror(char const* s)
{
  fprintf(stderr, "Parse error : %s (line %d)\n",s ,lineno);
}

void parseComment(FILE* in) {
    list_comments.comment_list = (struct comment**) malloc(0);
    list_comments.nbComments = 0;

    yyin = in;
    yyparse();
}

int yywrap()
{
  return(1);
}