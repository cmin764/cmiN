#fisier folosit pentru compilarea serverului&clientului TCP iterativ

all:
	gcc servTcpIt.c -o servTcpIt
	gcc cliTcpIt.c -o cliTcpIt
clean:
	rm -f *~cliTcpIt servTcpIt