%{
#include <strings.h>

int longest = 0;
char longword[60];
%}

%%
[a-zA-Z]+	{ if (yyleng > longest) {
                     longest = yyleng;
                     strcpy (longword, yytext);
                     }
                }
.	|
\n	;
%%
int main (void) {
   yylex ();
   printf ("The longest word was \"%s\", which was %d characters long.\n",
	   longword, longest);
   return 0;
   }
