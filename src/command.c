#include "command.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * Get file extension
 */
int get_extension(const char* str) {
    int begin = -1;
    size_t i = 0;
    while (str[i++] != '\0')
    {
        if (str[i-1] == '.') {
            begin = i;
        }
    }

    return begin;
}


//////////////////////////////////////////////////////////////////////////


struct command* parse_input(int argc, const char* args[])
{
    
    char** arg_copy = (char**) malloc(sizeof(char*) * argc);
    int index = 0;

    for (int i = 0; i < argc; i++) {
        int e = get_extension(args[i]);
        if (e == -1) continue;
        else if (strcmp(args[i]+e, "c") == 0 
            || strcmp( args[i]+e, "cpp") == 0) 
        {
            char* str = (char*) malloc(sizeof(char) * strlen(args[i]));
            memcpy(str, &args[i], strlen(args[i]));
            arg_copy[index++] = str;
        }
    }
    
    arg_copy[index] = NULL;

    struct command* c = (struct command*) malloc(sizeof(struct command));
    c->files = arg_copy;
    c->clear = 0;
}



//////////////////////////////////////////////////////////////////////////

void
free_command(struct command* c)
{
    char** files = c->files;
    size_t i = 0;

    while (files[i] != NULL) {
        free(files[i]);
        i++;
    }

    free(files);
    free(c);
}
