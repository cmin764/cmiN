HOMEWORKNAME=tema 2
TEAMNAME=Cosmin Poieana A6
PREPEND=[GPCL]
CC=g++
CFLAGS=-Wall
LDFLAGS=-lm -lGL -lGLU -lglut -std=c++14
CPPSOURCES= $(wildcard ./*.cpp)
CPPOBJECTS= $(CPPSOURCES:.cpp=.o)
CSOURCES= $(wildcard ./src/*.c)
SOURCES= $(CSOURCES) $(CPPSOURCES)
OBJECTS= $(COBJECTS) $(CPPOBJECTS)
CEXES= $(CSOURCES:.c=)
CPPEXES= $(CPPSOURCES:.cpp=)
EXECUTABLES= $(CEXES) $(CPPEXES)
ZIPNAME="[GPCL] $(TEAMNAME) $(HOMEWORKNAME).zip"

all: $(SOURCES) $(EXECUTABLES)

debug:
	make CFLAGS="-Wall -ggdb -emacs -O0"

release:
	make CFLAGS="-Wall -DNDEBUG -O3"


$(EXECUTABLES): $(SOURCES)
	$(CC) $(GENERALFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean: 
	rm -Rf $(EXECUTABLES) $(ZIPNAME) || echo ""

zip: clean
	zip -r $(ZIPNAME) .
