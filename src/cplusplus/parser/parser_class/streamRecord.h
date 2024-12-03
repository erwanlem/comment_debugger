#ifndef __GDB__STREAM__RECORD__H__
#define __GDB__STREAM__RECORD__H__


#include "outbandrecord.h"
#include <string>


namespace gdb {

    using namespace std;

    /**
     * Class StreamRecord
     */
    class StreamRecord : public OutBandRecord {
        public:
            enum StreamType {
                CONSOLE,
                TARGET,
                LOG,
                NONE
            };

        private:
            StreamType streamType;
            string content;

        public:
            OutputType getType() const { return STREAM; }

            StreamRecord(StreamType type, string v)
            : OutBandRecord(STREAM)
            , streamType(type)
            , content(v)
            {};

            StreamRecord()
            : OutBandRecord(STREAM)
            , streamType(NONE)
            , content("")
            {};

            StreamType getStreamType() const { return streamType; }
            string getValue() const { return content;  }

    };


}


#endif