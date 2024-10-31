%{
#define YYSTYPE char*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

extern int yylineno;
extern FILE* yyin;

%}


%token COMMENT
%token IDENT
%token AT
%token COMMA
%token SEMI

%start instructions

%%

/**
    Grammar

    instructions:
        instr*

    instr:
        "//" '@' IDENT (variable)?

    variable:
        IDENT ',' variable
        | IDENT

*/

instructions:
    instr SEMI instructions
    | instr SEMI
    ;

instr:
    | COMMENT AT IDENT variable   { printf("(0) New instr // @ %s %s\n", $3, $4); }
    | COMMENT AT IDENT            { printf("(1) New instr // @ %s\n", $3); }
    ;

variable:
    IDENT COMMA variable
    | IDENT
    ;


%%

int yyerror(char* s)
{
  fprintf(stderr, "Parse error : %s (line %d)\n",s ,yylineno);
}

void parseComment(FILE* in) {
    yyin = in;
    yyparse();
}

int yywrap()
{
  return(1);
}