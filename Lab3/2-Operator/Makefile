all: lexer.fl parser.y
	flex lexer.fl
	bison -v -d -Wcounterexamples parser.y
	gcc parser.tab.c lex.yy.c -lfl -lm -o a.out

clean:
	rm -f parser.tab.h
	rm -f parser.tab.c
	rm -f lex.yy.c
	rm -f parser.output
	rm -f a.out
	rm -f *~
