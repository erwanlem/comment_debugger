    /*
        ********************* Main lexer for comments debugger *************************

        This file is the main lexer of the software. Its purpose is to extract debugger 
        specific comments. We use here the lexical analyzer `lex` (flex). 
        For more information about the structure of lex files you can read the manual at 
        https://manpages.ubuntu.com/manpages/focal/man1/flex.1.html or by 
        typing `info flex` in your terminal.

    */



    /*********************/
    /**** Definitions ****/
    /*********************/

%{

#include "parser.hh"
#include <string.h>
#include "driver.hh"

namespace cpp {
    char* cpy;
}

%}

%option noyywrap 
    // nounput noinput batch debug

    /* Variable name (Simplified for tests) */
NUM                [0-9]+

%%

    /*******************/
    /*** Lexer Rules ***/
    /*******************/

    /* Debugger comments */

"{"                             { return yy::parser::make_OPEN_CURL_BRACKET(); }
"}"                             { return yy::parser::make_CLOSE_CURL_BRACKET(); }

"["                             { return yy::parser::make_OPEN_SQUARE_BRACKET(); }
"]"                             { return yy::parser::make_CLOSE_SQUARE_BRACKET(); }

","                             { return yy::parser::make_COMMA(); }

"^"                             { return yy::parser::make_CIRC(); }

"*"                             { return yy::parser::make_STAR(); }
"+"                             { return yy::parser::make_PLUS(); }
"="                             { return yy::parser::make_EQUAL(); }

"~"                             { return yy::parser::make_TILD(); }
"@"                             { return yy::parser::make_AT(); }
"&"                             { return yy::parser::make_AND(); }

"done"                          { return yy::parser::make_DONE(std::string(yytext)); }
"running"                       { return yy::parser::make_RUNNING(std::string(yytext)); }
"connected"                     { return yy::parser::make_CONNECTED(std::string(yytext)); }
"error"                         { return yy::parser::make_ERROR(std::string(yytext)); }
"exit"                          { return yy::parser::make_EXIT(std::string(yytext)); }

"stopped"                       { return yy::parser::make_STOPPED(std::string(yytext)); }

"thread-group-added"            { return yy::parser::make_ASYNC_RECORD_1(); }
"thread-group-removed"          { return yy::parser::make_ASYNC_RECORD_2(); }
"thread-group-started"          { return yy::parser::make_ASYNC_RECORD_3(); }
"thread-group-exited"           { return yy::parser::make_ASYNC_RECORD_4(); }
"thread-created"                { return yy::parser::make_ASYNC_RECORD_5(); }
"thread-exited"                 { return yy::parser::make_ASYNC_RECORD_6(); }
"library-loaded"                { return yy::parser::make_ASYNC_RECORD_7(); }
"library-unloaded"              { return yy::parser::make_ASYNC_RECORD_8(); }
"thread-selected"               { return yy::parser::make_ASYNC_RECORD_9(); }
"breakpoint-created"            { return yy::parser::make_ASYNC_RECORD_10(); }
"breakpoint-modified"           { return yy::parser::make_ASYNC_RECORD_11(); }
"breakpoint-deleted"            { return yy::parser::make_ASYNC_RECORD_12(); }
"record-started"                { return yy::parser::make_ASYNC_RECORD_13(); }
"record-stopped"                { return yy::parser::make_ASYNC_RECORD_14(); }

"(gdb)"                         { return yy::parser::make_GDB(); }

\r\n                            { return yy::parser::make_NL(); }
\n                              { return yy::parser::make_NL(); }


\"(\\.|[^\\"])*\"               {
                                    return yy::parser::make_CSTRING(yytext); 
                                }

[a-zA-Z_\-]([a-zA-Z_\-]|[0-9])* {
                                    return yy::parser::make_STRING(yytext); 
                                }

{NUM}                           { return yy::parser::make_DIGITS( std::stoi(yytext) ); }

.                               {}

%%


    /*****************/
    /*** User code ***/
    /*****************/


void set_input_string(const char* in) {
    yy_scan_string(in);
}

void end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}

