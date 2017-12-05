name=test1
input=in.txt

all:
	lex -ll -o $(name).c $(name).l
	gcc -o $(name) $(name).c -ll -ly

clean:
	rm $(name) $(name).c

run:
	./$(name) ${input}
