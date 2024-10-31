#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <unistd.h>
#include <stdlib.h>

struct comment {
    char* name;
    char** var;
    int line;
};



struct comment* create_comment(char* name, char** vars, int line) {
    struct comment* c = (struct comment*) malloc(sizeof(struct comment));

    c->line = line;
    c->name = name;
    c->var = vars;

    return c;
}

#endif