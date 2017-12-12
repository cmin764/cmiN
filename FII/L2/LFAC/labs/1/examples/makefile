LEX = /usr/bin/flex
CFLAGS = -g
LDLIBS = -lfl
CC = /usr/bin/gcc
YACC = /usr/bin/yacc

lexlongword:	lexlongword.c

lexlongword.c: lexlongword.l

ex1:	ex1.c
ex1.c:	ex1.l

ch301:	ch301.tab.o ch301.scan.o
	$(CC) -o ch301 ch301.tab.o ch301.scan.o $(LDLIBS)
# ch301.tab.o:	ch301.tab.c
ch301.scan.o:	ch301.scan.c ch301.tab.h
ch301.tab.c:	ch301.y
	$(YACC) -d ch301.y
	mv -f y.tab.c ch301.tab.c
	mv -f y.tab.h ch301.tab.h
ch301.tab.h:	ch301.y
	$(YACC) -d ch301.y
	mv -f y.tab.c ch301.tab.c
	mv -f y.tab.h ch301.tab.h
ch301.scan.c:		ch301.l
	$(LEX) ch301.l
	mv -f lex.yy.c ch301.scan.c

ch302:	ch302.tab.o ch302.scan.o
	$(CC) -o ch302 ch302.tab.o ch302.scan.o $(LDLIBS)
ch302.scan.o:	ch302.scan.c ch302.tab.h
ch302.tab.c:	ch302.y
	$(YACC) -d ch302.y
	mv -f y.tab.c ch302.tab.c
	mv -f y.tab.h ch302.tab.h
ch302.tab.h:	ch302.y
	$(YACC) -d ch302.y
	mv -f y.tab.c ch302.tab.c
	mv -f y.tab.h ch302.tab.h
ch302.scan.c:	ch302.l
	$(LEX) ch302.l
	mv -f lex.yy.c ch302.scan.c

words2:	words2.tab.o words2.scan.o
	$(CC) -o words2 words2.tab.o  words2.scan.o $(LDLIBS)
words2.scan.o:	words2.scan.c words2.tab.h
words2.tab.c:	words2.y
	$(YACC) -d words2.y
	mv -f y.tab.c words2.tab.c
	mv -f y.tab.h words2.tab.h
words2.tab.h:	words2.y
	$(YACC) -d words2.y
	mv -f y.tab.c words2.tab.c
	mv -f y.tab.h words2.tab.h
words2.scan.c:	words2.l
	$(LEX) words2.l
	mv -f lex.yy.c words2.scan.c

clean:
	rm -f parse.tab.h parse.tab.c lex.yy.c y.tab.h parse.c parse \
	ch301.tab.o ch301.scan.o ch301.tab.c ch301.scan.c ch301.tab.h \
	ch301 y.tab.c ch302 ch302.scan.o ch302.tab.c ch302.tab.h \
	ch302.scan.c ch302.tab.o


