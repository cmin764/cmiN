%{
#include "words2.tab.h"
extern int yylval;
extern int at_end;
%}

%%

<<EOF>>		{
		at_end = 1;
		return END;
		}

" "		|
\n		|
"\t"		;

[Tt]he		|
[Aa]n?		return ARTICLE;

go(es)?		|
jumps?		|
runs?		|
likes?		|
eats?		return VERB;

dogs?		|
cats?		|
fish		|
fox(es)?	|
moose		return NOUN;

quick		|
slow		|
lazy		|
clever		|
smart		|
stupid		|
brown		|
black		|
blue		|
red		|
orange		|
white		|
big		|
small		return ADJECTIVE;

quickly		|
easily		|
openly		|
slowly		return ADVERB;

over		|
under		|
around		|
through		|
between		return PREPOSITION;

.		return yytext[0]; /* default action allows yacc to see literal characters */
%%
