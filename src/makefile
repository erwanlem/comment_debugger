
main: lexer/lex.yy.c main.o provider.o
	gcc -o main main.o provider.o

provider.o: provider.c provider.h
	gcc -c provider.c

main.o: main.c
	gcc -c main.c

lexer/lex.yy.c: lexer/lexer.l
	flex -o lexer/lex.yy.c lexer/lexer.l