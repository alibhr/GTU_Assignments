%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "gpp_interpreter.h"

	int isOpen;

%}

VALUE		([0-9]|[1-9][0-9]+)
VALUE_ERR	"0"[0-9]+
ID			[[:alpha:]][[:alnum:]]*
ID_ERROR	[[:digit:]]+[[:alpha:]]+
OP_ERROR	[^[:space:]\n()"]?+[^[[:alnum:][^[:space:]\n()"]?+
IGNORE		" "+|"\n"|"\t"

%%

and			return KW_AND;
or			return KW_OR;
not			return KW_NOT;
equal		return KW_EQUAL;
less		return KW_LESS;
nil			return KW_NIL;
list		return KW_LIST;
append		return KW_APPEND;
concat		return KW_CONCAT;
set			return KW_SET;
deffun		return KW_DEFFUN;
for			return KW_FOR;
if			return KW_IF;
exit		return KW_EXIT;
load		return KW_LOAD;
disp		return KW_DISP;
true		return KW_TRUE;
false		return KW_FALSE;

"+"			return OP_PLUS;
"-"			return OP_MINUS;
"/"			return OP_DIV;
"*"			return OP_MULT;
"("			return OP_OP;
")"			return OP_CP;
"**"		return OP_DBLMULT;
","			return OP_COMMA;
"\"" 		{
	isOpen = !isOpen;
	if(isOpen == 0)
		return OP_OC;
	else
		return OP_CC;
}

";;".?+		return COMMENT;

{VALUE} 	{ yylval.val = atoi(yytext); return VALUE; }
{VALUE_ERR}	return 0;

{ID}		{ strcpy(yylval.id, yytext); return IDENTIFIER; }
{ID_ERROR}	return 0;
{OP_ERROR}	return 0;

^\n			{ if(yyin == stdin) return 0; }
<<EOF>>		{ return 0; }

{IGNORE}	{ /*** ignore ***/ }

. return 0;

%%

int yywrap(){}

/*
int main(int argc, char **argv){

	char *DefaultFileName = "grammar.txt";

	isOpen = 0;

	if(argc > 1){
		yyin = fopen(argv[1], "r");
		
		if(!yyin) {
			printf("\"%s\" file couldn't be found.\n", argv[1]) ;
			return 1;
		}

	}
	else{ yyin = stdin; }

	yyout = fopen("parsed_cpp.txt","w");

	yylex();

	return 0;
}
*/
