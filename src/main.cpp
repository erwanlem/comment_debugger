#include <string>
#include <iostream>
#include <vector>
#include "provider.h"
#include "command.h"
#include "comment_read.h"

using namespace std;


int main(int argc, char const *argv[])
{   
    /*string path = "../test/simple.cpp";

    vector<Comment> c = readComments(path);


    for (Comment comm : c) {
        cout << comm.getName() << ", " << comm.getVar() << ", " << comm.getLine() << endl;
    }*/
   char const* str1 = "-break-insert main\n";
   char const* str2 = "-exec-continue\n";
   char const* str3 = "-exec-run\n";

   struct gdb_proc* gdb = gdb_connect();

   gdb_send(gdb, str1);
   gdb_send(gdb, str2);
   gdb_send(gdb, str3);
   gdb_send(gdb, "quit\n");

   cout << gdb_read(gdb) << endl;

   gdb_close(gdb);

    return 0;
}
