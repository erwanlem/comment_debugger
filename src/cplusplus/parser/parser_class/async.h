#ifndef __GDB__ASYNC__PARSER__H__
#define __GDB__ASYNC__PARSER__H__

#include "value.h"
#include <vector>
#include <string>

namespace gdb {

    /**
     * Class AsyncOutput
     */
    class AsyncOutput {
        public:
            enum AsyncClass {
                STOPPED,
                ASYNC_RECORD,
                UNDEFINED
            };


        private:
            AsyncClass asyncClass;
            std::vector<Value> results;

        public:
            AsyncOutput(AsyncClass clss, std::vector<Value> results)
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