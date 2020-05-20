Lexer: lexer.l
	flex lexer.l
	gcc -w -o lexer lex.yy.c -lfl
	ls -l

LexerParser: lexer.l parser.y
	flex lexer.l
	bison parser.y -d --debug -v
	gcc -w -o parser parser.tab.c lex.yy.c -lfl -g
	ls -l

clean:
	rm lex.yy.c parser.tab.h parser.tab.c parser.output
	ls -l
