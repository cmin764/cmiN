bin=./bin
src=./src
sname=rms-server
cname=rms-cli

all:
	gcc -Wall -std=c11 -o $(bin)/$(sname) $(src)/$(sname).c -lpthread
	cp $(src)/$(cname).py $(bin)/$(cname)
	chmod +x $(bin)/$(cname)

clean:
	rm $(bin)/$(sname)
	rm $(bin)/$(cname)
