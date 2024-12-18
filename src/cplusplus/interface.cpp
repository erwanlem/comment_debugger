#include "interface.h"
#include <atomic>
#include <mutex>

namespace cplusplus {
    using namespace std;

    void send_output(bool &finished, string &buffer, mutex &access) 
    {
        string cmd;
        size_t index;
        while (!finished) {
            access.lock();
            if (buffer.find("(gdb)") != string::npos) {
                index = buffer.find("(gdb)");
                cmd = buffer.substr(0, index+7);
                buffer = buffer.substr(index+7, buffer.size());
                //cout << cmd << endl << endl;
                parse_output(cmd.c_str());
            }
            access.unlock();
        }
    }


    void run_gdb(string exe, vector<Command> commands) {
        mutex m;
        string buffer;
        buffer = "";
        bool finished = false;

        gdb_proc* gdb = gdb_connect(exe);

        // reader thread
        thread th1(gdb_read, gdb, ref(buffer), ref(m));

        // output thread
        thread th2(send_output, ref(finished), ref(buffer), ref(m));

        for (Command c : commands) {
            gdb_send(gdb, c.c_str());
        }

        th1.join();
        finished = true;
        th2.join();

    }





    void
    run(string exe, vector<Comment>& comments)
    {
        vector<Command> commands = generateCommands(comments);

        run_gdb(exe, commands);

    }

}
