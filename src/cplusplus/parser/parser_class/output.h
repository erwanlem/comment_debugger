#ifndef __GDB__OUTPUT__H__
#define __GDB__OUTPUT__H__


namespace gdb {

    /**
     * Class Output
     */
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

            virtual OutputType getType() const { return NONE; };
            bool isResult() const       { return type == RESULT; }
            bool isAsync() const        { return type == ASYNC;  }
            bool isStream() const       { return type == STREAM; }

    };

}


#endif