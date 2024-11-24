#include "commands.h"

#include <string>
#include <vector>

using namespace std;

namespace cplusplus {

    #define RUN "exec-run\n"
    #define QUIT "quit\n"

    vector<Command> generateCommands(vector<Comment>& comments) {
        vector<Command> commands(0);

        int bkpt_number = 1;

        for (Comment c : comments) {
            commands.push_back("-break-insert " + to_string(c.getLine()) + "\n");
            
            if (c.hasVar()) {
                cout << ">>" << c.getVar() << endl;
                commands.push_back("-break-commands " + to_string(bkpt_number++) + string(" \"print ") 
                                        + c.getVar() + "\" " + "\"continue\"\n");
            }
            else
                commands.push_back("-break-commands " + to_string(bkpt_number++) 
                                        + string(" \"info locals\" ") + "\"continue\"\n");
        }

        commands.push_back(RUN);
        commands.push_back(QUIT);

        return commands;

    }

}