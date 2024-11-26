#include "reader.h"

/**
 * Read debug comments from file given by `path`.
 * 
 * @param path the path of the file
 * 
 * @return vector of extracted comments
 */
std::vector<Comment> readComments(std::string path) 
{
    std::vector<Comment> c = std::vector<Comment>(0);

    char* ptr;
    size_t size;

    FILE* tmp = open_memstream(&ptr, &size);

    getCommentLines(path.c_str(), tmp);
    fflush(tmp);

    struct comments s = parseComment(tmp);

    struct comment* comm;
    for (int i = 0; i < s.nbComments; i++) {
        comm = s.comment_list[i];
        
        std::string var, name;
        if (comm->var == NULL) var = "";
        else var = std::string(comm->var);
        if (comm->name == NULL) name = "";
        else name = std::string(comm->name);

        c.push_back( Comment(name, var, comm->line) );

    }

    freeListComment();

    fclose(tmp);

    return c;
}