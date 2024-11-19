#include "input.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>


using namespace std;

/**
 * Get file extension
 */
int Input::get_extension(const char* str) {
    int begin = -1;
    size_t i = 0;
    while (str[i++] != '\0')
    {
        if (str[i-1] == '.') {
            begin = i;
        }
    }

    return begin;
}


//////////////////////////////////////////////////////////////////////////


bool
Input::isFlag(const char* str)
{
    if (str[0] == '-') {
        return true;
    }
    return false;
}



//////////////////////////////////////////////////////////////////////////



std::string Input::getFlag(const char* str) 
{
    int i = 0;
    while (str[i] == '-') i++;
    return string(str+i);
}



//////////////////////////////////////////////////////////////////////////




void
Input::interpret(int argc, char const* argv[])
{
    files = std::vector<std::string>();

    for (int i = 0; i < argc; i++) {
        if (isFlag(argv[i])) {
            flags.push_back( getFlag( argv[i] ) );
            continue;
        }

        int e = get_extension( argv[i] );
        if (e == -1) throw std::invalid_argument("Invalid option " + std::string(argv[i]));
        else if (strcmp(argv[i]+e, "c") == 0 
            || strcmp( argv[i]+e, "cpp") == 0) 
        {            
            files.push_back(std::string(argv[i]));
        }
    }
}



//////////////////////////////////////////////////////////////////////////



std::vector<std::string>
Input::getFiles()
{
  return files;
}



//////////////////////////////////////////////////////////////////////////



std::vector<std::string>
Input::getFlags()
{
  return flags;
}
