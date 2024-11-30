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


char* cpy;

%}


    /* Variable name (Simplified for tests) */
NUM                [0-9]+
ALPHANUM           [a-zA-Z0-9]+

%%

    /*******************/
    /*** Lexer Rules ***/
    /*******************/

    /* Debugger comments */
"//"                                        { return COMMENT; }

{NUM}                                       { flval.intval = atoi(yytext);
                                             return NUMBER; }

{ALPHANUM}                                  { cpy = (char *)calloc(strlen(yytext)+1,sizeof(char));
                                              strcpy(cpy, yytext);
                                              flval.strval = cpy;
                                              return IDENT; 
                                            }

","                                         { return COMMA; }

"@"                                         { return AT; }

";"                                         { return SEMI; }

"("                                         { return LPAR; }

")"                                         { return RPAR; }

\n                                          { }

<<EOF>>                                     { return 0; }

[^\n]                                       { }


%%


    /*****************/
    /*** User code ***/
    /*****************/

int fwrap(){return(1);}