HOMEWORKNAME=tema 3
TEAMNAME=ion ionescu A3 pop popescu B1
PREPEND=[GPCL]
CC=g++
CFLAGS=-Wall
LDFLAGS=-lm -lGL -lGLU -lglut
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
	$(CC) $(GENERALFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@

clean: 
	rm -Rf $(EXECUTABLES) $(ZIPNAME) || echo ""

zip: clean
	zip -r $(ZIPNAME) .
