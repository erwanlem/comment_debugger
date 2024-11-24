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



#include "parser.h"
#include <string.h>



%}

%option yylineno
    /* Variable name (Simplified for tests) */
NUM                [0-9]+

%%

    /*******************/
    /*** Lexer Rules ***/
    /*******************/

    /* Debugger comments */

"{"                 {  yylval = yytext; return OPEN_CURL_BRACKET; }
"}"                 {  yylval = yytext; return CLOSE_CURL_BRACKET; }

"["                 {  yylval = yytext; return OPEN_SQUARE_BRACKET; }
"]"                 {  yylval = yytext; return CLOSE_SQUARE_BRACKET; }

","                 {  yylval = yytext; return COMMA; }

"^"                 {  yylval = yytext; return CIRC; }

"*"                 {  yylval = yytext; return STAR; }
"+"                 {  yylval = yytext; return PLUS; }
"="                 {  yylval = yytext; return EQUAL; }

"~"                 {  yylval = yytext; return TILD; }
"@"                 { yylval = yytext; return AT; }
"&"                 { yylval = yytext; return AND; }

"done"              { yylval = yytext; return DONE; }
"running"           { yylval = yytext; return RUNNING; }
"connected"         { yylval = yytext; return CONNECTED; }
"error"             { yylval = yytext; return ERROR; }
"exit"              { yylval = yytext; return EXIT; }

"stopped"           { yylval = yytext; return STOPPED; }

"thread-group-added"      { yylval = yytext; return ASYNC_RECORD_1; }
"thread-group-removed"    { yylval = yytext; return ASYNC_RECORD_2; }
"thread-group-started"    { yylval = yytext; return ASYNC_RECORD_3; }
"thread-group-exited"     { yylval = yytext; return ASYNC_RECORD_4; }
"thread-created"          { yylval = yytext; return ASYNC_RECORD_5; }
"thread-exited"           { yylval = yytext; return ASYNC_RECORD_6; }
"library-loaded"          { yylval = yytext; return ASYNC_RECORD_7; }
"library-unloaded"        { yylval = yytext; return ASYNC_RECORD_8; }
"thread-selected"         { yylval = yytext; return ASYNC_RECORD_9; }
"breakpoint-created"      { yylval = yytext; return ASYNC_RECORD_10; }
"breakpoint-modified"     { yylval = yytext; return ASYNC_RECORD_11; }
"breakpoint-deleted"      { yylval = yytext; return ASYNC_RECORD_12; }
"record-started"          { yylval = yytext; return ASYNC_RECORD_13; }
"record-stopped"          { yylval = yytext; return ASYNC_RECORD_14; }

"(gdb)"                         { yylval = yytext; return GDB; }

\r\n                            { return NL; }
\n                              { return NL; }


\"(\\.|[^\\"])*\"               { return CSTRING; }

[a-zA-Z_\-]([a-zA-Z_\-]|[0-9])* { return STRING; }

{NUM}               { yylval = yytext; return DIGITS; }

%%


    /*****************/
    /*** User code ***/
    /*****************/