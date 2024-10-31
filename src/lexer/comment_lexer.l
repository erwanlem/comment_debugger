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
int drop_debug = 0;

int lines = 1; // line of the file pointer

FILE* lexfile; // Temporary file

%}

    /* Variable name (Simplified for tests) */
IDENT           [a-zA-Z0-9]+

%option yylineno

%%

    /*******************/
    /*** Lexer Rules ***/
    /*******************/

    /* Debugger comments */
"//"[" "]*@[" "]*{IDENT}([" "]*{IDENT})?    { fprintf(lexfile, "%s;\n", yytext); }

\n                                          { lines++; }

<<EOF>>                                     { return 0; }

[^\n]                                       { }


%%


    /*****************/
    /*** User code ***/
    /*****************/


int yywrap() {}

FILE* getCommentLines(char* path, FILE* out) {
    FILE *f = fopen(path, "r");

    layer0in = f;

    lexfile = out;

    layer0lex();

    fclose(f);
}