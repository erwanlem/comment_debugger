#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct comment {
    char* name;
    char* var;
    int line;
};

struct comments {
    struct comment** comment_list;
    int nbComments;
};

extern struct comments list_comments;

void new_comment(char* name, char* vars, int line);

#endif