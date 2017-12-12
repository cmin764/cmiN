%{
#include "ch302.tab.h"
extern int yylval;
%}

%%
[0-9]+	{ yylval = atoi (yytext); 
	printf ("scanned the number %d\n", yylval);
	return NUMBER; }
[ \t]	{ printf ("skipped whitespace\n"); }
\n	{ printf ("reached end of line\n");
	return 0;
	}
.	{ printf ("found other data \"%s\"\n", yytext);
	return yytext[0];
	}
%%
