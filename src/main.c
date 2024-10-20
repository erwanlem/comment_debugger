#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "provider.h"

#include "lexer/lex.yy.c"





int main(int argc, char const *argv[])
{   
    /*drop_debug = 1;

    FILE *f = fopen("../test/simple.cpp", "r");
    FILE *fr = fopen("../test/tmp.cpp", "a");

    lexfile = fr; // set temporary file

    yyin = f; // set input file

    yylex(); // start lexer

    printf("\n\nThere are %d lines\n", lines);*/

    struct gdb_proc* proc = gdb_connect();
    if (proc != NULL) printf("Proc created successfully with pid %d\n", proc->pid);
    else printf("gdb connection failed\n");

    gdb_send(proc, "help\n");
    gdb_send(proc, "quit\n");

    gdb_read(proc);
    gdb_close(proc);

    return 0;
}
