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

    extern int yylineno;
    int yylex (void);
    void yyerror (char const *);

%}

%define parse.error verbose
%define api.value.type {char*}

%token DIGITS
%token NL
%token OPEN_CURL_BRACKET CLOSE_CURL_BRACKET
%token OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
%token COMMA
%token CIRC STAR
%token PLUS EQUAL
%token TILD AT AND

%token CSTRING STRING

%token DONE RUNNING CONNECTED ERROR EXIT
%token STOPPED

%token ASYNC_RECORD_1 ASYNC_RECORD_2 ASYNC_RECORD_3 ASYNC_RECORD_4 ASYNC_RECORD_5
%token ASYNC_RECORD_6 ASYNC_RECORD_7 ASYNC_RECORD_8 ASYNC_RECORD_9 ASYNC_RECORD_10
%token ASYNC_RECORD_11 ASYNC_RECORD_12 ASYNC_RECORD_13 ASYNC_RECORD_14

%token GDB

%start output

%%

output:
    out_of_band_record output
    | result_record GDB NL {}
    | result_record out_of_band_record GDB NL { yyerrok; }
    | GDB NL
    | error NL
    ;

result_record:
    CIRC result_class COMMA comma_result NL {}
    | CIRC result_class NL {}
    | DIGITS CIRC result_class NL {}
    | DIGITS CIRC result_class COMMA comma_result NL {}
    ;

comma_result:
    result COMMA comma_result {}
    | result {}
    ;

out_of_band_record:
    async_record
    | stream_record {};

async_record:
    exec_async_output
    | status_async_output
    | notify_async_output;

exec_async_output:
    STAR async_output NL {}
    | STAR result_class COMMA comma_result NL {}
    | DIGITS STAR async_output NL {}
    ;

status_async_output:
    PLUS async_output NL {}
    | DIGITS PLUS async_output NL {}
    ;

notify_async_output:
    EQUAL async_output NL {}
    | DIGITS EQUAL async_output NL {}
    ;

async_output:
    async_class COMMA comma_result
    ;

result_class:
    DONE
    | RUNNING
    | CONNECTED
    | ERROR
    | EXIT
    ;

async_class:
    STOPPED
    | ASYNC_RECORD_1
    | ASYNC_RECORD_2
    | ASYNC_RECORD_3
    | ASYNC_RECORD_4
    | ASYNC_RECORD_5
    | ASYNC_RECORD_6
    | ASYNC_RECORD_7
    | ASYNC_RECORD_8
    | ASYNC_RECORD_9
    | ASYNC_RECORD_10
    | ASYNC_RECORD_11
    | ASYNC_RECORD_12
    | ASYNC_RECORD_13
    | ASYNC_RECORD_14
    ;

result:
    variable EQUAL value;

variable:
    STRING;

value:
    const_
    | tuple
    | list
    ;

const_:
    CSTRING
    ;

tuple :
    OPEN_CURL_BRACKET CLOSE_CURL_BRACKET
    | OPEN_CURL_BRACKET comma_result CLOSE_CURL_BRACKET
    ;

list :
    OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET 
    | OPEN_SQUARE_BRACKET comma_value CLOSE_SQUARE_BRACKET
    | OPEN_SQUARE_BRACKET comma_result CLOSE_SQUARE_BRACKET

comma_value:
    value COMMA comma_value
    | value
    ;

stream_record :
    console_stream_output
    | target_stream_output
    | log_stream_output
    ;

console_stream_output :
    TILD CSTRING NL
    ;

target_stream_output :
    AT CSTRING NL
    ;

log_stream_output :
    AND CSTRING NL
    ;

%%

extern FILE* yyin;

int yywrap()
{
  return(1);
}

void yyerror(char const* s)
{
    fprintf (stderr, "%s\nLine %d : Last token = %s\n", s, yylineno, yylval);
}

int main(void) {
    FILE* f = fopen("test.txt", "r");
    yyin = f;

    return yyparse();
}