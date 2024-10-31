#ifndef __READER__H__
#define __READER__H__

#include "lexer/lex.yy.c"


/**
 * Describe debug instruction
 */
struct instruction {
    int line;
    char** variables;
    char* name;
};



/**
 * Get comment instructions in the given file
 * 
 * @param file the file to read
 * @param len (out) number of instructions extracted
 * 
 * @return `struct instruction*` a pointer to the list of extracted instructions
 */
struct instruction* get_debug_instructions(char* file, int* len);


#endif
