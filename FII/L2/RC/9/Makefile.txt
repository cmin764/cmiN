#fisier folosit pentru compilarea serverului&clientului TCP concurent

all:
	gcc servTcpCSel.c -o servTcp
	gcc cliTcp.c -o cliTcp
clean:
	rm -f *~cliTcp servTcp
