#include "reader.h"
#include <stdlib.h>
#include "lexer/y.tab.c"

struct instruction*
get_debug_instructions(char* file, int* len)
{
    yyparse();

    return NULL;
}