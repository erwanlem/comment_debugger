#ifndef __GDB__ASYNC__PARSER__H__
#define __GDB__ASYNC__PARSER__H__

#include "value.h"
#include <vector>
#include <string>

namespace gdb {
    using namespace std;

    class AsyncOutput {
        public:
            enum AsyncClass {
                STOPPED,
                ASYNC_RECORD,
                UNDEFINED
            };


        private:
            AsyncClass asyncClass;
            vector<Value> results;

        public:
            AsyncOutput(AsyncClass clss, vector<Value> results)
            : asyncClass(clss)
            , results(results) 
            {};   

            AsyncOutput()
            : asyncClass(UNDEFINED)
            , results()
            {};    

    };


}


#endif