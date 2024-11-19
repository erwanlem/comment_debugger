

main: parser.tab.c lex.yy.o
	gcc -o parse  parser.tab.c lex.yy.o

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.o: parser.tab.c lexer.l
	flex lexer.l; gcc -c lex.yy.c