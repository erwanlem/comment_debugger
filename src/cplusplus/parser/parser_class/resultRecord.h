#include "output.h"
#include "outbandrecord.h"
#include <vector>
#include "value.h"

namespace gdb {
    using namespace std;

    /**
     * Class ResultRecord
     */
    class ResultRecord : public Output {
        public:
            enum ResultClass {
                DONE,
                RUNNING,
                CONNECTED,
                ERROR,
                EXIT,
                NONE
            };
        
        private:
            ResultClass resultClass;
            vector<Value> results;

            bool resultValue;

        public:
            ResultRecord(ResultClass resultClass, vector<Value> results)
            : Output(RESULT)
            , resultClass(resultClass)
            , results(results) 
            , resultValue(true)
            {};

            ResultRecord(ResultClass resultClass)
            : Output(RESULT)
            , resultClass(resultClass)
            , results()
            , resultValue(false)
            {};

            ResultRecord()
            : Output(RESULT)
            , resultClass(NONE)
            , results()
            , resultValue(false)
            {};

    };

}
