#ifndef __PARSER__COMMENT_H__
#define __PARSER__COMMENT_H__

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



struct comments list_comments;

void new_comment(char* name, char* vars, int line);

#endif