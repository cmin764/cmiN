%{
/* this sample demonstrates very simple word recognition: verbs & other */
%}
%%

[\t ]+		/* ignore whitespace */ ;

is		|
am		|
are		|
were		|
was		|
be		|
being		|
been		|
do		|
does		|
did		|
will		|
would		|
should		|
can		|
could		|
has		|
have		|
had		|
go		{ printf ("\"%s\" is a verb\n", yytext); }
[a-zA-Z]+	{ printf ("\"%s\" is not a verb\n", yytext); }
.		|
\n		ECHO; /* which is the default anyway */
%%
int main (void) {
	return yylex ();
}
/* This is the "default main program" anyway, so it could be omitted. */
