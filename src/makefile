
main: main.o lex.yy.o lex.comment.o comment.o y.tab.o provider.o input.o provider.h C++ cplusplus/interface.h reader.o
	g++ -o main main.o provider.o interface.o command.o input.o comment.o lexer/out/lex.yy.o \
	 lexer/out/y.tab.o lexer/out/lex.comment.o reader.o

provider.o: provider.cpp provider.h
	gcc -c provider.cpp

main.o: main.cpp
	g++ -c main.cpp

lex.yy.c: lexer/lexer.l
	flex -o lexer/out/lex.yy.c lexer/lexer.l

lex.comment.c: lexer/comment_lexer.l y.tab.o
	flex -Player0 -o lexer/out/lex.comment.c lexer/comment_lexer.l

input.o: input.cpp input.h
	gcc -c input.cpp

comment.o:
	gcc -c lexer/comment.c

reader.o: reader.cpp reader.h
	g++ -c reader.cpp

y.tab.o:
	cd lexer/; bison -o out/y.tab.c -d parser.y;\
	cd out/; gcc -c y.tab.c; cd ../..

lex.yy.o: lex.yy.c y.tab.o
	cd lexer/out/; gcc -c lex.yy.c; cd ../..

lex.comment.o: lex.comment.c
	cd lexer/out/; gcc -c lex.comment.c; cd ../..

C++: cplusplus/interface.cpp cplusplus/interface.h cplusplus/command.h cplusplus/command.cpp cplusplus/command.h
	g++ -c cplusplus/interface.cpp
	g++ -c cplusplus/command.cpp

clean:
	rm -f main
	rm -f lexer/out/*
	find . -name '*.o' -delete