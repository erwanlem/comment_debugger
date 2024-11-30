#ifndef __COMPILE__H__
#define __COMPILE__H__

#include <string>
#include <string.h>
#include "input.h"

/**
 * This file run the compilation of the input
 * 
 * The main issue in compilation is to find the right compiler for the input.
 * We define a list of supported compilers and we check if they are available 
 * on the system. If it is we run otherwise we throw error.
 * If user wants to compile using an unsupported compiler he can suggest it 
 * with the option `--compiler=myCompiler`.
 * 
 * Actually we just put the compiler name in front of the flags/file part of the input.
 * 
 */




// Define C and C++ compilers
#define GCC         "gcc"
#define GPP         "g++"
#define CLANG       "clang"
#define CLANGPP     "clang++"




/**
 * Check if command exist
 * 
 * It uses the `which` command to check the existence
 */
bool commandExist(std::string command);




/**
 * Search for a compiler appropriate with the input language
 * 
 * @param lang language use in the input
 */
std::string findCompiler(Language lang);




/**
 * Run compiler for the input
 * It adds the `g` flag if it is not in the input flags
 * 
 * @param in user input
 */
void compile(Input in);


#endif