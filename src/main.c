#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "provider.h"
#include "command.h"
#include "lexer/lexer_comment.h"

int execute(struct command* c) {
    
    
    return 0;
}






int main(int argc, char const *argv[])
{   

    /*FILE *f = fopen("../test/simple.cpp", "r");
    FILE *fr = fopen("../test/tmp.cpp", "a");

    lexfile = fr; // set temporary file

    yyin = f; // set input file

    yylex(); // start lexer

    printf("\n\nThere are %d lines\n", lines);
*/
    char* ptr;
    size_t size;

    //FILE *f = fopen("../test/simple.cpp", "r");

    FILE* tmp = open_memstream(&ptr, &size);

    //yyin = f;

    //lexfile = tmp;

    getCommentLines("../test/simple.cpp", tmp);
    
    fflush(tmp);

    printf("%s\n\n", ptr);

    parseComment(tmp);

    fclose(tmp);
    //struct command* c = parse_input(argc, argv);

    //free_command(c);

    return 0;
}
