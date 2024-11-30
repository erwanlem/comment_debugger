#ifndef __GDB__OUTPUT__PARSER__H__
#define __GDB__OUTPUT__PARSER__H__

#include "async.h"
#include "value.h"


namespace gdb {
    using namespace std;

    class Output {
        public:
            enum OutputType {
                STREAM,
                ASYNC,
                RESULT,
                NONE
            };

        private:
            OutputType type;

        public:
            Output() : type(NONE) {};
            Output(OutputType t) : type(t) {};

            OutputType getType() const  { return type; };
            bool isResult() const       { return type == RESULT; }
            bool isAsync() const        { return type == ASYNC;  }
            bool isStream() const       { return type == STREAM; }

    };



    class OutBandRecord : public Output {
        public:
            OutBandRecord() : Output(NONE) {};
            OutBandRecord(OutputType t) : Output(t) {};
    };


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

    class StreamRecord : public OutBandRecord {
        public:
            enum StreamType {
                CONSOLE,
                TARGET,
                LOG,
                NONE
            };

        private:
            StreamType type;
            string value;

        public:
            StreamRecord(StreamType type, string value)
            : OutBandRecord(STREAM)
            , type(type)
            , value(value)
            {};

            StreamRecord()
            : OutBandRecord(STREAM)
            , type(NONE)
            , value()
            {};

            StreamType getType() const { return type; }
            string getValue() const { return value; }

    };

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