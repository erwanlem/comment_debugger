%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "../comment.h"

extern int lineno;
extern FILE* yyin;
int yylex (void);
void yyerror (char const *);

%}

%union {
  int intval;
  char* strval;
}


%token COMMENT
%token IDENT
%token AT
%token COMMA 
%token SEMI
%token NUMBER
%token LPAR RPAR

%start instructions

%type<strval> COMMENT IDENT AT COMMA SEMI LPAR RPAR variable
%type<intval> NUMBER

%%

instructions:
    instr SEMI instructions
    | instr SEMI
    ;

instr:
      LPAR NUMBER RPAR COMMENT AT IDENT variable   { new_comment( $6, $7, $2); }
    | LPAR NUMBER RPAR COMMENT AT IDENT            { new_comment( $6, NULL,  $2); }
    | LPAR NUMBER RPAR COMMENT AT                  { new_comment( NULL, NULL,  $2); }
    ;

variable:
    IDENT COMMA variable
    | IDENT
    ;


%%

void yyerror(char const* s)
{
  fprintf(stderr, "Parser error : %s (line %d)\n",s ,lineno);
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