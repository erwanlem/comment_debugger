#include "compile.h"



/**
 * Check if command exist
 * 
 * It uses the `which` command to check the existence
 */
bool commandExist(std::string command) {
    std::string c = "which -s " + command;
    return !system(c.c_str());
}




/////////////////////////////////////////////////////////////////




/**
 * Search for a compiler appropriate with the input language
 * 
 * @param lang language use in the input
 */
std::string findCompiler(Language lang)
{
    switch (lang)
    {
    case C:
        if (commandExist(GCC))
            return GCC;
        else if (commandExist(CLANG))
            return CLANG;

        break;
    
    case CPP:
        if (commandExist(GPP))
            return GPP;
        else if (commandExist(CLANGPP))
            return CLANGPP;

        break;

    case OCAML:
    case RUST:

        break;

    default:
        break;
    }
    // Other files

    return "";
}




/////////////////////////////////////////////////////////////////




/**
 * Run compiler for the input
 * It adds the `g` flag if it is not in the input flags
 * 
 * @param in user input
 */
void compile(Input in) 
{
    std::string compiler = findCompiler(in.getLanguage());
    
    bool found = false;
    for (auto f : in.getFlags())
        if (f == "g")
            found = true;

    std::string compiler_command;
    if (found)
        compiler_command = compiler + in.fullCommand();
    else
        compiler_command = compiler + " -g " + in.fullCommand();
    
    int o = system(compiler_command.c_str());
}