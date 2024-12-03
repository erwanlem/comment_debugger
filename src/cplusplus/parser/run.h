#include "parser_class/streamRecord.h"
#include "parser_class/value.h"
#include "parser.hh"

void set_input_string(const char* in);
void end_lexical_scan(void);

void parse_output(const char* in) {
    //std::cout << in << std::endl;

    std::vector<gdb::Output *> outputs;

    set_input_string(in);
    yy::parser parse(outputs);
    parse();
    end_lexical_scan();

    for (auto &out : outputs) {
        if (out->isStream()) {
            std::cout << "NEW STREAM" << std::endl;
            gdb::StreamRecord* s = static_cast<gdb::StreamRecord*>(out);
            if (s == nullptr) std::cout << "Cast error" << std::endl;
            else
            if ( s->getStreamType() == gdb::StreamRecord::StreamType::CONSOLE ) {
                std::cout << s->getValue() << std::endl;
            } else if ( s->getStreamType() == gdb::StreamRecord::StreamType::TARGET ) {
                //std::cout << s->getValue() << std::endl;
            } else if ( s->getStreamType() == gdb::StreamRecord::StreamType::LOG ) {
                //std::cout << s->getValue() << std::endl;
            }
        } else if (out->isResult()) {
            std::cout << "NEW RESULT" << std::endl;
        } else if (out->isAsync()) {
            std::cout << "NEW ASYNC" << std::endl;
        }
    }
}