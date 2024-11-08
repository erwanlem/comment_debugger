#include <string>
#include <iostream>
#include <vector>
#include "provider.h"
#include "command.h"
#include "comment_read.h"

using namespace std;


int main(int argc, char const *argv[])
{   
    string path = "../test/simple.cpp";

    vector<Comment> c = readComments(path);


    for (Comment comm : c) {
        cout << comm.getName() << ", " << comm.getVar() << ", " << comm.getLine() << endl;
    }

    return 0;
}
