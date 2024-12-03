#ifndef __GDB__OUT__BAND__RECORD__H__
#define __GDB__OUT__BAND__RECORD__H__

#include "output.h"

namespace gdb {

    /**
     * Class OutBandRecord
     */
    class OutBandRecord : public Output {
        public:
            OutBandRecord() : Output(NONE) {};
            OutBandRecord(OutputType t) : Output(t) {};
    };

}

#endif