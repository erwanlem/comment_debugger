#ifndef __LEXER_COMMENT__H__
#define __LEXER_COMMENT__H__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * This file is the interface between the C parser and the C++ main program.
 * The transition is made in readComments which creates C++ object from C
 * struct.
 */



#ifdef __cplusplus
extern "C" {
#endif
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

    FILE* getCommentLines(char const* path, FILE* out);
    void parseComment(FILE* in);
    void freeListComment();
    void freeComment(struct comment* c);

#ifdef __cplusplus
}
#endif


/**
 * Comment class
 * Equivalent to the C structure comment
 */
class Comment {
    private:
        int line;
        string name;
        string var;

    public:
        Comment(string name, string var, int line) : name(name), var(var), line(line) {};
        Comment() {};

        int getLine() { return line; }
        string getName() { return name; }
        string getVar() { return var; }
};





/**
 * Read debug comments from file given by `path`.
 * 
 * @param path the path of the file
 * 
 * @return vector of extracted comments
 */
vector<Comment> readComments(string path) 
{
    vector<Comment> c = vector<Comment>(0);

    char* ptr;
    size_t size;

    FILE* tmp = open_memstream(&ptr, &size);

    getCommentLines(path.c_str(), tmp);
    fflush(tmp);

    printf("%s\n", ptr);

    parseComment(tmp);

    struct comment* comm;
    for (int i = 0; i < list_comments.nbComments; i++) {
        comm = list_comments.comment_list[i];
        
        string var, name;
        if (comm->var == NULL) var = "";
        else var = comm->var;
        if (comm->name == NULL) name = "";
        else name = comm->name;

        c.push_back( Comment(name, var, comm->line) );

    }

    freeListComment();

    fclose(tmp);

    return c;
}

#endif