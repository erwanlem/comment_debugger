#ifndef __GDB__ASYNC__RECORD__H__
#define __GDB__ASYNC__RECORD__H__


#include "outbandrecord.h"
#include "async.h"
#include <vector>
#include "value.h"

namespace gdb {
    using namespace std;

    /**
     * Class AsyncRecord
     */
    class AsyncRecord : public OutBandRecord {
        public:
            enum AsyncType {
                EXEC,
                STATUS,
                NOTIFY,
                NONE
            };
        
        private:
            AsyncType type;
            AsyncOutput output;
            vector<Result> results;
            bool resultValue;

        public:
            OutputType getType() const { return ASYNC; }

            AsyncRecord(AsyncType type, AsyncOutput output, vector<Result> results)
            : OutBandRecord(ASYNC)
            , type(type)
            , output(output)
            , results(results)
            , resultValue(true)
            {};

            AsyncRecord(AsyncType type, AsyncOutput output)
            : OutBandRecord(ASYNC)
            , type(type)
            , output(output)
            , results()
            , resultValue(false)
            {};

            AsyncRecord()
            : OutBandRecord(ASYNC)
            , type(NONE)
            , output(AsyncOutput())
            , results()
            , resultValue(false)
            {};
    };


}


#endif