#include "input.h"
#include "provider.h"
#include "reader.h"
#include <iostream>
#include <string>
#include <vector>
#include "cplusplus/interface.h"

#include <atomic>
#include <thread>

using namespace std;

int
main(int argc, char const* argv[])
{
	Input input;
	input.interpret(argc, argv);
	
	/*cout << "Files :" << endl;
	for (string s : input.getFiles()) {
		cout << s << endl;
	}
	cout << endl;
	cout << "Flags :" << endl;
	for (string s : input.getFlags()) {
		cout << s << endl;
	}*/

	vector<Comment> debug_instr = readComments(input.getFiles()[0]);

  	cplusplus::run(debug_instr);

	return 0;
}
