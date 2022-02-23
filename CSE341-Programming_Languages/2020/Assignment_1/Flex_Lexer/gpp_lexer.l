
%{
	int isOpen;
	
	void print_the_token(char *str){
		fprintf(yyout, "%s", str);
		fprintf(stdout, "%s", str);
	}
	
	void print_the_error(char *error){
		fprintf(yyout, "SYNTAX_ERROR %s cannot be tokenized\n", error);
		fprintf(stdout, "SYNTAX_ERROR %s cannot be tokenized\n", error);
	}

%}

VALUE		([0-9]|[1-9][0-9]+)
VALUE_ERR	"0"[0-9]+
ID			[[:alpha:]][[:alnum:]]*
ID_ERROR	[[:digit:]]+[[:alpha:]]+
OP_ERROR	[^[:space:]\n()"]?+[^[[:alnum:][^[:space:]\n()"]?+
IGNORE		" "+|"\n"|"\t"

%%

and			{ print_the_token("KW_AND\n"); }
or			{ print_the_token("KW_OR\n"); }
not			{ print_the_token("KW_NOT\n"); }
equal		{ print_the_token("KW_EQUAL\n"); }
less		{ print_the_token("KW_LESS\n"); }
nil			{ print_the_token("KW_NIL\n"); }
list		{ print_the_token("KW_LIST\n"); }
append		{ print_the_token("KW_APPEND\n"); }
concat		{ print_the_token("KW_CONCAT\n"); }
set			{ print_the_token("KW_SET\n"); }
deffun		{ print_the_token("KW_DEFFUN\n"); }
for			{ print_the_token("KW_FOR\n"); }
if			{ print_the_token("KW_IF\n"); }
exit		{ print_the_token("KW_EXIT\n"); }
load		{ print_the_token("KW_LOAD\n"); }
disp		{ print_the_token("KW_DISP\n"); }
true		{ print_the_token("KW_TRUE\n"); }
false		{ print_the_token("KW_FALSE\n"); }

"+"			{ print_the_token("OP_PLUS\n"); }
"-"			{ print_the_token("OP_MINUS\n"); }
"/"			{ print_the_token("OP_DIV\n"); }
"*"			{ print_the_token("OP_MULT\n"); }
"("			{ print_the_token("OP_OP\n"); }
")"			{ print_the_token("OP_CP\n"); }
"**"		{ print_the_token("OP_DBLMULT\n"); }
","			{ print_the_token("OP_COMMA\n"); }
"\"" 		{ (isOpen == 0) ? print_the_token("OP_OC\n") : print_the_token("OP_CC\n"); isOpen = !isOpen; }

";;".?+		{ print_the_token("COMMENT\n"); }

{VALUE} 	{ print_the_token("VALUE\n"); }
{VALUE_ERR}	{ print_the_error(yytext); }

{ID}		{ print_the_token("IDENTIFIER\n"); }
{ID_ERROR}	{ print_the_error(yytext); }
{OP_ERROR}	{ print_the_error(yytext); }

^\n			{ if(yyin == stdin) return 0; }
<<EOF>>		{ return 0; }

{IGNORE}	{ /*** ignore ***/ }

. { print_the_error(yytext); }

%%

int yywrap(){}

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

