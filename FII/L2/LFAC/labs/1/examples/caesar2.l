%%
[a-wA-W]	printf ("%c", yytext[0]+3);

[xyzXYZ]	printf ("%c", yytext[0]-23);
%%
