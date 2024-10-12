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
int lines = 1; // line of the file pointer

FILE* lexfile; // Temporary file

%}

    /* Keywords for C language (here for test) */
KEYWORDS        return|typedef|define|extern|inline|static|sizeof|break|continue|constexpr

    /* Variable name (Simplified for tests) */
IDENT           [a-zA-Z0-9]+

    /* Variable affectation */
AFFECT          {IDENT}[" "]*=[" "]*[^;]

    /* Multiple declaration and affectation of variables */
MULTIAFFECT     (({AFFECT}|{IDENT}[" "]*),[" "]*)*({AFFECT}|{IDENT}[" "]*);



%%

    /*******************/
    /*** Lexer Rules ***/
    /*******************/

{KEYWORDS}[" "]+{MULTIAFFECT}     { }

    /* Variables declarations */
{IDENT}[" "]+{MULTIAFFECT}        { fprintf(lexfile, "%s",  yytext); printf("NEW VARIABLE %s\n", yytext); }


    /* Debugger comments */
"//"[" "]*@[" "]*{IDENT}          { printf("Debug comment %s\n", yytext); }

\n                                { fprintf(lexfile, "%s",  yytext); lines++; }

<<EOF>>                           { return 0; }

[^\n]                             { fprintf(lexfile, "%s",  yytext); }




%%


    /*****************/
    /*** User code ***/
    /*****************/

int yywrap() {}