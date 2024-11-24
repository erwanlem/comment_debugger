#ifndef __LEXER__READER__H__
#define __LEXER__READER__H__

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

void getCommentLines(char const* path, FILE* out);
struct comments parseComment(FILE* in);
void freeListComment();
void freeComment(struct comment* c);


/////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>
#include <iostream>



/**
 * Comment class
 * Equivalent to the C structure comment
 */
class Comment {
    private:
        int line;
        std::string name;
        std::string var;

    public:
        Comment(std::string name, std::string var, int line) : name(name), var(var), line(line) {};
        Comment(std::string name, int line) : name(name), var(""), line(line) {};
        Comment(int line) : name(""), var(""), line(line) {};
        Comment() {};

        int getLine()           { return line; }
        std::string getName()   { return name; }
        std::string getVar()    { return var; }
        bool hasVar()           { return !var.empty(); }
        bool hasName()          { return !name.empty(); }
};


/**
 * Read debug comments from file given by `path`.
 * 
 * @param path the path of the file
 * 
 * @return vector of extracted comments
 */
std::vector<Comment> readComments(std::string path);

#endif
