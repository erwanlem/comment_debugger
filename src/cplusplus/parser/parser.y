%{
    /**
    * A parser for gdb output.
    * The following grammar is based on the grammar described in the gdb mi documentation.
    * 
    * For more information read 
    * https://sourceware.org/gdb/current/onlinedocs/gdb.html/GDB_002fMI-Output-Syntax.html#GDB_002fMI-Output-Syntax
    */

    #include <ctype.h>
    #include <stdio.h>
    #include <string>
    #include <vector>
    # include <map>
    #include <string>
    #include <unordered_map>

%}

%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.8.1"
%header

%define api.token.raw


%define parse.error verbose
//%define api.value.type {char*}

%define api.token.constructor
%define api.value.type variant

%code {
    # include "driver.hh"
}

%code requires {
    #include "value.h"
    #include "async.h"
    #include "output.h"
}

%parse-param {std::vector<gdb::Output> &out}

%token <int> DIGITS
%token NL
%token OPEN_CURL_BRACKET CLOSE_CURL_BRACKET
%token OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
%token COMMA
%token CIRC STAR
%token PLUS EQUAL
%token TILD AT AND

%token <std::string> STRING
%token <std::string> CSTRING

%token <std::string> DONE RUNNING CONNECTED ERROR EXIT
%token <std::string> STOPPED

%token ASYNC_RECORD_1 ASYNC_RECORD_2 ASYNC_RECORD_3 ASYNC_RECORD_4 ASYNC_RECORD_5
%token ASYNC_RECORD_6 ASYNC_RECORD_7 ASYNC_RECORD_8 ASYNC_RECORD_9 ASYNC_RECORD_10
%token ASYNC_RECORD_11 ASYNC_RECORD_12 ASYNC_RECORD_13 ASYNC_RECORD_14

%token GDB

%start output

%type <std::string> variable const_ console_stream_output target_stream_output log_stream_output
%type <gdb::List> list
%type <gdb::Value> value
%type <gdb::Tuple> tuple
%type <std::vector<gdb::Value>> comma_value comma_result
%type <gdb::Result> result
%type <gdb::AsyncOutput::AsyncClass> async_class
%type <gdb::ResultRecord::ResultClass> result_class
%type <gdb::AsyncRecord> notify_async_output status_async_output exec_async_output async_record
%type <gdb::AsyncOutput> async_output
%type <gdb::StreamRecord> stream_record
%type <gdb::OutBandRecord> out_of_band_record
%type <gdb::ResultRecord> result_record
%type <std::vector<gdb::Output>> output

%%

output:
    out_of_band_record output                           { out.push_back($1); $$ = out; }
    | result_record GDB NL                              { out.push_back($1); $$ = out; }
    | result_record out_of_band_record GDB NL           { // TODO Verify order
                                                            out.push_back($1);
                                                            out.push_back($2);
                                                            $$ = out;
                                                        }
    | GDB NL                                            { $$ = out; }
    | error NL                                          { $$ = out; }
    ;

result_record:
    CIRC result_class COMMA comma_result NL             { $$ = gdb::ResultRecord($2, $4); }
    | CIRC result_class NL                              { $$ = gdb::ResultRecord($2); }
    | DIGITS CIRC result_class NL                       { $$ = gdb::ResultRecord($3); }
    | DIGITS CIRC result_class COMMA comma_result NL    { $$ = gdb::ResultRecord($3, $5); }
    ;


comma_result:
    result COMMA comma_result   { $3.push_back($1); $$ = $3; }
    | result                    { 
                                    std::vector<gdb::Value> r(0);
                                    r.push_back($1);
                                    $$ = r;
                                }
    ;

out_of_band_record:
    async_record                                { $$ = $1; }
    | stream_record                             { $$ = $1; }
    ;

async_record:
    exec_async_output                           { $$ = $1; }
    | status_async_output                       { $$ = $1; }
    | notify_async_output                       { $$ = $1; }
    ;

exec_async_output:
    STAR async_output NL                        { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::EXEC, $2); }
    | STAR result_class COMMA comma_result NL   { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::EXEC, 
                                                                        gdb::AsyncOutput(gdb::AsyncOutput::AsyncClass::UNDEFINED, $4)); 
                                                }
    | DIGITS STAR async_output NL {}            { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::EXEC, $3); }
    ;

status_async_output:
    PLUS async_output NL                        { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::STATUS, $2); }
    | DIGITS PLUS async_output NL               { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::STATUS, $3); }
    ;

notify_async_output:
    EQUAL async_output NL                       { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::NOTIFY, $2); }
    | DIGITS EQUAL async_output NL              { $$ = gdb::AsyncRecord(gdb::AsyncRecord::AsyncType::NOTIFY, $3); }
    ;

async_output:
    async_class COMMA comma_result          { $$ = gdb::AsyncOutput($1, $3); }
    ;

result_class:
    DONE            { $$ = gdb::ResultRecord::ResultClass::DONE; }
    | RUNNING       { $$ = gdb::ResultRecord::ResultClass::RUNNING; }
    | CONNECTED     { $$ = gdb::ResultRecord::ResultClass::CONNECTED; }
    | ERROR         { $$ = gdb::ResultRecord::ResultClass::ERROR; }
    | EXIT          { $$ = gdb::ResultRecord::ResultClass::EXIT; }
    ;

async_class:
    STOPPED           { $$ = gdb::AsyncOutput::AsyncClass::STOPPED; }
    | ASYNC_RECORD_1  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_2  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_3  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_4  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_5  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_6  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_7  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_8  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_9  { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_10 { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_11 { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_12 { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_13 { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    | ASYNC_RECORD_14 { $$ = gdb::AsyncOutput::AsyncClass::ASYNC_RECORD; }
    ;

result:
    variable EQUAL value                                    { $$ = gdb::Result($1, $3); }
    ;

variable:
    STRING                                                  { $$ = $1; }
    ;

value:
    const_                                                  { $$ = gdb::Const($1); }  
    | tuple                                                 { $$ = $1; }
    | list                                                  { $$ = $1; }
    ;

const_:
    CSTRING                                                 { $$ = $1; }
    ;

tuple :
    OPEN_CURL_BRACKET CLOSE_CURL_BRACKET                    { $$ = gdb::Tuple(); }
    | OPEN_CURL_BRACKET comma_result CLOSE_CURL_BRACKET     { $$ = gdb::Tuple($2); }
    ;

list :
    OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET                { $$ = gdb::List(); }
    | OPEN_SQUARE_BRACKET comma_value CLOSE_SQUARE_BRACKET  { $$ = gdb::List($2); }
    | OPEN_SQUARE_BRACKET comma_result CLOSE_SQUARE_BRACKET { $$ = gdb::List($2); }

comma_value:
    value COMMA comma_value                                 { $3.push_back($1); $$ = $3; }
    | value                                                 { 
                                                                std::vector<gdb::Value> v(0); 
                                                                v.push_back($1); $$ = v; 
                                                            }
    ;

stream_record :
    console_stream_output                                   { $$ = gdb::StreamRecord(
                                                                gdb::StreamRecord::StreamType::CONSOLE,
                                                                $1);
                                                            }
    | target_stream_output                                  { $$ = gdb::StreamRecord(
                                                                gdb::StreamRecord::StreamType::TARGET,
                                                                $1); }
    | log_stream_output                                     { $$ = gdb::StreamRecord(
                                                                gdb::StreamRecord::StreamType::LOG,
                                                                $1); }
    ;

console_stream_output :
    TILD CSTRING NL                                         { $$ = $2; }
    ;

target_stream_output :
    AT CSTRING NL                                           { $$ = $2; }
    ;

log_stream_output :
    AND CSTRING NL                                          { $$ = $2; }
    ;

%%

void set_input_string(const char* in);
void end_lexical_scan(void);

void yy::parser::error (const std::string& m)
{
  std::cerr << ": " << m << '\n';
}

void parse_output(const char* in) {
    //std::cout << in << std::endl;

    std::vector<gdb::Output> outputs;

    set_input_string(in);
    yy::parser parse(outputs);
    parse();
    end_lexical_scan();

    /*for (auto &out : outputs) {
        if (out.isStream()) {
            std::cout << "NEW STREAM" << std::endl;
            gdb::StreamRecord* s = static_cast<gdb::StreamRecord*>(&out);
            if ( s->getType() == gdb::StreamRecord::StreamType::CONSOLE ) {
                std::cout << "CONSOLE" << std::endl;
            } else if ( s->getType() == gdb::StreamRecord::StreamType::TARGET ) {
                std::cout << s->getValue() << std::endl;
            } else if ( s->getType() == gdb::StreamRecord::StreamType::LOG ) {
                //std::cout << s->getValue() << std::endl;
            }
        } else if (out.isResult()) {
            std::cout << "NEW RESULT" << std::endl;
        } else if (out.isAsync()) {
            std::cout << "NEW ASYNC" << std::endl;
        }
    }*/
}