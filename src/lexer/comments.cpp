#include "comments.h"

/**
 * Create a new comment allocated in heap.
 * 
 * @param name (pointer to) debug comment name
 * @param vars (pointer to) debug comment variables (may be NULL)
 * @param line line number
 */
struct comment* create_comment(char* name, char* vars, int line) {
    struct comment* c = (struct comment*) malloc(sizeof(struct comment));

    c->line = line;
    c->name = name;
    c->var = vars;

    return c;
}

/**
 * Add new comment to structure `list_comments`.
 * It creates a new comment with `create_comment` (describe above).
 * 
 * @param name (pointer to) debug comment name
 * @param vars (pointer to) debug comment variables (may be NULL)
 * @param line line number
 */
void new_comment(char* name, char* vars, int line) {
    int s = list_comments.nbComments;

    struct comment* new_c = create_comment(name, vars, line);

    list_comments.comment_list = (struct comment**) realloc(list_comments.comment_list, (s+1) * sizeof(struct comment*));

    list_comments.comment_list[s] = new_c;

    list_comments.nbComments++;
}

/**
 * DEBUG FUNCTION
 */
void print_comments() {
    printf("nb comments = %d\n", list_comments.nbComments);
    for (int i = 0; i < list_comments.nbComments; i++) {
        printf("%s, %s, %d\n", 
            list_comments.comment_list[i]->name, 
            list_comments.comment_list[i]->var, 
            list_comments.comment_list[i]->line);
    }
}


/**
 * Free comment given in parameter
 * 
 * @param c the comment to free
 */
void freeComment(struct comment* c) {
    if (c->name != NULL) free(c->name);
    if (c->var != NULL) free(c->var);
    free(c);
}




/**
 * Free the structure `list_comments`. 
 * It removes every data allocated in heap.
 */
void freeListComment() {
    for (int i = 0; i < list_comments.nbComments; i++) {
        freeComment(list_comments.comment_list[i]);
    }

    free(list_comments.comment_list);
}