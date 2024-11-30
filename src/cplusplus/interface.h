#ifndef __INTERFACE__H__
#define __INTERFACE__H__

#include <iostream>
#include <vector>
#include "../provider.h"
#include "commands.h"
#include "../reader.h"
#include <thread>


void parse_output(const char* in);

namespace cplusplus {

    /**
     * run debug process for C++.
     * This function is the main function of the language debugging API.
     * 
     * This function runs the program until it exits (with or without error) and 
     * sends output instructions to the printer.
     * 
     * @param comments Debug comments describing user request
     */
    void run(std::string exe, std::vector<Comment>& comments);


}

#endif