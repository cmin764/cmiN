#fisier folosit pentru compilarea serverului&clientului UDP

all:
	gcc servUdp.c -o servUdp
	gcc cliUdp.c -o cliUdp
clean:
	rm -f *~cliUdp servUdp
