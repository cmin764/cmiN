	enum {ARTICLE, VERB, NOUN, ADJECTIVE,
		ADVERB, PUNCTUATION, PREPOSITION, END};
%%
<<EOF>>		return END;

" "		|
"\t"		;

the		|
an?		return ARTICLE;

go(es)?		|
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

"."		|
,		|
"?"		|
;		|
:		|
!		|
@		|
#		|
"$"		|
"%"		|
"^"		|
&		|
"*"		|
"("		|
")"		return PUNCTUATION;

over		|
under		|
around		|
through		|
between		return PREPOSITION;

%%
int main(void) {
	int result;
	int running = 1;
	while (running) {
		result = yylex();
		switch (result) {
			case ARTICLE: printf("Article "); break;	
			case VERB: printf("Verb "); break;	
			case NOUN: printf("Noun "); break;	
			case ADJECTIVE: printf("Adjective "); break;	
			case ADVERB: printf("Adverb "); break;	
			case PUNCTUATION: printf("Punctuation "); break;	
			case PREPOSITION: printf("Preposition "); break;	
			case END: running=0; break;
			default: printf ("Huh?");
			}
		}
	return 0;
	}
