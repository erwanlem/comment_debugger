
main: y.tab.h lex.yy.c lex.comment.c main.o provider.o command.o 
	gcc -o main main.o provider.o command.o lexer/out/lex.yy.c lexer/out/y.tab.c lexer/out/lex.comment.c

provider.o: provider.c provider.h
	gcc -c provider.c

main.o: main.c
	gcc -c main.c

lex.yy.c: lexer/lexer.l
	flex -o lexer/out/lex.yy.c lexer/lexer.l

lex.comment.c: lexer/comment_lexer.l
	flex -Player0 -o lexer/out/lex.comment.c lexer/comment_lexer.l

command.o: command.c command.h
	gcc -c command.c

y.tab.h: lex.yy.c
	cd lexer; yacc -o out/y.tab.c -d -v parser.y; \
	cd ..

clean:
	rm *.o
	rm main
	rm lexer/out/*