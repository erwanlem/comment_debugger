#include "interface.h"
#include <atomic>
#include <mutex>

namespace cplusplus {

    void send_output(bool &finished, std::string &buffer, std::mutex &access) 
    {
        while (!finished) {
            access.lock();
            if (buffer.find("(gdb)") != std::string::npos) {
                std::cout << buffer << std::endl << std::endl;
                buffer = "";
            }
            access.unlock();
        }
    }


    void run_gdb(std::vector<Command> commands) {
        std::mutex m;
        std::string buffer;
        buffer = "";
        bool finished = false;

        gdb_proc* gdb = gdb_connect("../gdb_test/test");

        // reader thread
        std::thread th1(gdb_read, gdb, std::ref(buffer), std::ref(m));

        // output thread
        std::thread th2(send_output, std::ref(finished), std::ref(buffer), std::ref(m));

        for (Command c : commands) {
            gdb_send(gdb, c.c_str());
        }

        th1.join();
        finished = true;
        th2.join();

    }





    void
    run(std::vector<Comment>& comments)
    {
        std::vector<Command> commands = generateCommands(comments);

        for (Command& c : commands) {
            std::cout << "> " << c << std::endl;
        }
        //run_gdb(commands);

    }

}
