
main: lexer/lex.yy.c main.c
	gcc -o main main.c

lexer/lex.yy.c: lexer/lexer.l
	flex -o lexer/lex.yy.c lexer/lexer.l