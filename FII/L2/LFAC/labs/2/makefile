name=limbaj

all:
	lex $(name).l
	yacc -d $(name).y
	gcc -o $(name) lex.yy.c y.tab.c -ll -ly

run:
	./$(name)

clean:
	rm $(name) lex.yy.c y.tab.c
