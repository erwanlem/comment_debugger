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
    command = " ";
    output = "a.out";

    for (int i = 1; i < argc; i++) {
        command += + argv[i];
        command += " ";
        if (isFlag(argv[i])) {
            string flg = getFlag( argv[i] );
            if (flg == "o") output = argv[i+1];
            flags.push_back( getFlag( argv[i] ) );
            continue;
        }

        int e = get_extension( argv[i] );
        //if (e == -1) throw std::invalid_argument("Invalid option " + std::string(argv[i]));
        if (strcmp(argv[i]+e, "c") == 0) 
        {
            language = C;
            files.push_back(std::string(argv[i]));
        }
        else if (strcmp( argv[i]+e, "cpp") == 0)
        {
            language = CPP;
            files.push_back(std::string(argv[i]));
        }
    }
}



//////////////////////////////////////////////////////////////////////////



std::vector<std::string>
Input::getFiles() const
{
  return files;
}



//////////////////////////////////////////////////////////////////////////



std::vector<std::string>
Input::getFlags() const
{
  return flags;
}
