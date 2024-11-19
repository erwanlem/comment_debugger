/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DIGITS = 258,                  /* DIGITS  */
    NL = 259,                      /* NL  */
    OPEN_CURL_BRACKET = 260,       /* OPEN_CURL_BRACKET  */
    CLOSE_CURL_BRACKET = 261,      /* CLOSE_CURL_BRACKET  */
    OPEN_SQUARE_BRACKET = 262,     /* OPEN_SQUARE_BRACKET  */
    CLOSE_SQUARE_BRACKET = 263,    /* CLOSE_SQUARE_BRACKET  */
    COMMA = 264,                   /* COMMA  */
    CIRC = 265,                    /* CIRC  */
    STAR = 266,                    /* STAR  */
    PLUS = 267,                    /* PLUS  */
    EQUAL = 268,                   /* EQUAL  */
    TILD = 269,                    /* TILD  */
    AT = 270,                      /* AT  */
    AND = 271,                     /* AND  */
    CSTRING = 272,                 /* CSTRING  */
    STRING = 273,                  /* STRING  */
    DONE = 274,                    /* DONE  */
    RUNNING = 275,                 /* RUNNING  */
    CONNECTED = 276,               /* CONNECTED  */
    ERROR = 277,                   /* ERROR  */
    EXIT = 278,                    /* EXIT  */
    STOPPED = 279,                 /* STOPPED  */
    ASYNC_RECORD_1 = 280,          /* ASYNC_RECORD_1  */
    ASYNC_RECORD_2 = 281,          /* ASYNC_RECORD_2  */
    ASYNC_RECORD_3 = 282,          /* ASYNC_RECORD_3  */
    ASYNC_RECORD_4 = 283,          /* ASYNC_RECORD_4  */
    ASYNC_RECORD_5 = 284,          /* ASYNC_RECORD_5  */
    ASYNC_RECORD_6 = 285,          /* ASYNC_RECORD_6  */
    ASYNC_RECORD_7 = 286,          /* ASYNC_RECORD_7  */
    ASYNC_RECORD_8 = 287,          /* ASYNC_RECORD_8  */
    ASYNC_RECORD_9 = 288,          /* ASYNC_RECORD_9  */
    ASYNC_RECORD_10 = 289,         /* ASYNC_RECORD_10  */
    ASYNC_RECORD_11 = 290,         /* ASYNC_RECORD_11  */
    ASYNC_RECORD_12 = 291,         /* ASYNC_RECORD_12  */
    ASYNC_RECORD_13 = 292,         /* ASYNC_RECORD_13  */
    ASYNC_RECORD_14 = 293,         /* ASYNC_RECORD_14  */
    GDB = 294                      /* GDB  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef char* YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
