#include "commands.h"

#include <string>
#include <vector>

using namespace std;

namespace cplusplus {

    #define RUN "-exec-run\n"
    #define QUIT "quit\n"
    #define TTY "-inferior-tty-set /dev/pts/1\n"

    vector<Command> generateCommands(vector<Comment>& comments) {
        vector<Command> commands(0);

        int bkpt_number = 1;

        //commands.push_back(TTY);

        for (Comment c : comments) {
            commands.push_back("-break-insert " + to_string(c.getLine()) + "\n");
            
            commands.push_back("-break-commands " + to_string(bkpt_number++) 
                                    + string(" \"info locals\" ") + "\"continue\"\n");
        }

        commands.push_back(RUN);
        commands.push_back(QUIT);

        return commands;

    }

}