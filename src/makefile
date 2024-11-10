
main: lex.yy.o lex.comment.o comment.o y.tab.o provider.o command.o provider.h
	g++ -o main main.cpp provider.o command.o comment.o lexer/out/lex.yy.o lexer/out/y.tab.o lexer/out/lex.comment.o

provider.o: provider.cpp provider.h
	gcc -c provider.cpp

main.o: main.cpp comment_read.h
	g++ -c main.cpp

lex.yy.c: lexer/lexer.l
	flex -o lexer/out/lex.yy.c lexer/lexer.l

lex.comment.c: lexer/comment_lexer.l y.tab.o
	flex -Player0 -o lexer/out/lex.comment.c lexer/comment_lexer.l

command.o: command.c command.h
	gcc -c command.c

comment.o:
	gcc -c lexer/comment.c

y.tab.o:
	cd lexer/; bison -o out/y.tab.c -d parser.y;\
	cd out/; gcc -c y.tab.c; cd ../..

lex.yy.o: lex.yy.c y.tab.o
	cd lexer/out/; gcc -c lex.yy.c; cd ../..

lex.comment.o: lex.comment.c
	cd lexer/out/; gcc -c lex.comment.c; cd ../..

clean:
	rm *.o
	rm main
	rm lexer/out/*