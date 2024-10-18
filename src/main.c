#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer/lex.yy.c"





int main(int argc, char const *argv[])
{   
    drop_debug = 1;

    FILE *f = fopen("../test/simple.cpp", "r");
    FILE *fr = fopen("../test/tmp.cpp", "a");

    lexfile = fr; // set temporary file

    yyin = f; // set input file

    yylex(); // start lexer

    printf("\n\nThere are %d lines\n", lines);

    return 0;
}
