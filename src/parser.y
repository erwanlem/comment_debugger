%{
    /**
    * This file parse gdb output.
    * The following grammar is based on the grammar described in the gdb mi documentation.
    * 
    * For more information read 
    * https://sourceware.org/gdb/current/onlinedocs/gdb.html/GDB_002fMI-Output-Syntax.html#GDB_002fMI-Output-Syntax
    */

    #include <ctype.h>
    #include <stdoi.h>
    #define YYSTYPE double
%}

%token DIGITS
%token NL
%token STRING
%token OPEN_CURL_BRACKET CLOSE_CURL_BRACKET
%token OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
%token COMMA

%token DONE RUNNING CONNECTED ERROR EXIT
%token STOPPED

%token GDB

%%

output :
    out_of_band_record result_record GDB NL;

result_record :
    DIGITS '^' result_class comma_result NL;

comma_result :
    %empty
    | COMMA result comma_result;

out_of_band_record :
    async_record
    | stream_record;

async_record :
    exec_async_output
    | status_async_output
    | notify_async_output;

exec_async_output :
    DIGITS '*' async_output NL;

status_async_output :
    DIGITS '+' async_output NL;

notify_async_output :
    DIGITS '=' async_output NL;

async_output :
    async_class comma_result;

result_class :
    DONE
    | RUNNING
    | CONNECTED
    | ERROR
    | EXIT
    ;

async_class :
    STOPPED
    ;

result :
    variable '=' value;

variable :
    STRING;

value :
    const_
    | tuple
    | list
    ;

const_ :
    STRING;

tuple :
    OPEN_CURL_BRACKET CLOSE_CURL_BRACKET
    | OPEN_CURL_BRACKET result comma_result CLOSE_CURL_BRACKET
    ;

list :
    OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET 
    | OPEN_SQUARE_BRACKET value comma_value CLOSE_SQUARE_BRACKET
    | OPEN_SQUARE_BRACKET result comma_result CLOSE_SQUARE_BRACKET

comma_value :
    | %empty
    | COMMA value comma_value

stream_record :
    console_stream_output
    | target_stream_output
    | log_stream_output
    ;

console_stream_output :
    '~' STRING NL
    ;

target_stream_output :
    '@' STRING NL
    ;

log_stream_output :
    '&' STRING NL
    ;



%%

#include "lexer/lex.yy.c"

void yyerror(char* s)
{
    fprintf (stderr, "%s\n", s);
}

int main(void) {
    return yyparse();
}