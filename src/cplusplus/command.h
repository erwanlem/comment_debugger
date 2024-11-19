#ifndef __CPLUSPLUS__COMMAND__H__
#define __CPLUSPLUS__COMMAND__H__

#include <string>
#include <vector>
#include "../reader.h"

namespace cplusplus {

    typedef std::string Command;

    /**
     * Generate commands to send to gdb for the requested comments
     */
    std::vector<Command> generateCommands(std::vector<Comment>&);

}


#endif