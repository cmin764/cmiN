name=pyc

all:
	lex $(name).l
	yacc -d $(name).y
	gcc -w -o $(name) lex.yy.c y.tab.c -ll -ly

run:
	./$(name) $(name).pc

clean:
	rm $(name) lex.yy.c y.tab.c y.tab.h
