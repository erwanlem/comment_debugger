%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "comments.h"


extern int lineno;
extern FILE* fin;
int flex (void);
void ferror (char const *);
void new_comment(char* name, char* vars, int line);
struct comments list_comments;

%}

%union {
  int intval;
  char* strval;
}

%define api.prefix {f}

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

instructions
    : instr SEMI instructions
    | 
    ;

instr
    : LPAR NUMBER RPAR COMMENT AT IDENT variable   { new_comment( $6, $7, $2); }
    | LPAR NUMBER RPAR COMMENT AT IDENT            { new_comment( $6, NULL,  $2); }
    | LPAR NUMBER RPAR COMMENT AT                  { new_comment( NULL, NULL,  $2); }
    ;

variable
    : IDENT COMMA variable
    | IDENT
    ;


%%

void ferror(char const* s)
{
  fprintf(stderr, "Parser error : %s (line %d)\n", s, lineno);
}

struct comments parseComment(FILE* in) {
    list_comments.comment_list = (struct comment**) malloc(0);
    list_comments.nbComments = 0;

    fin = in;

    fparse();

    return list_comments;
}

int fwrap()
{
  return(1);
}