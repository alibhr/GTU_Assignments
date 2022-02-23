%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "VariableTable.h"
	#include "ArrayList.h"

	int yyerror(char* s);
	int yylex();

	extern FILE *yyout;
	extern FILE *yyin;
%}

%union
{
	void*	values;
	char	id[30];
	int		val;
}

%start INPUT

%token	KW_AND 
%token	KW_OR
%token	KW_NOT
%token	KW_EQUAL
%token	KW_LESS
%token	KW_NIL
%token	KW_LIST
%token	KW_APPEND
%token	KW_CONCAT
%token	KW_SET
%token	KW_DEFFUN
%token	KW_FOR
%token	KW_IF
%token	KW_EXIT
%token	KW_LOAD
%token	KW_DISP
%token	KW_TRUE
%token	KW_FALSE
%token	OP_PLUS
%token	OP_MINUS
%token	OP_DIV
%token	OP_MULT
%token	OP_OP
%token	OP_CP
%token	OP_DBLMULT
%token	OP_OC
%token	OP_CC
%token	OP_COMMA
%token	COMMENT

%token <val> VALUE
%token <id> IDENTIFIER

%type <val> INPUT
%type <val> EXPI
%type <val> EXPB
%type <values> EXPLISTI
%type <values> LISTVALUE
%type <values> VALUES

%%

INPUT:
	EXPI			{ printf("Syntax OK.\nResult: %d\n\n", $1);		fprintf(yyout, "Syntax OK.\nResult: %d\n\n", $1); }
	| 
	INPUT EXPI		{ printf("Syntax OK.\nResult: %d\n\n", $2);		fprintf(yyout, "Syntax OK.\nResult: %d\n\n", $2); }
	| 
	EXPLISTI		{ printf("Syntax OK.\nResult: ");	printList($1, stdout);	printf("\n");	fprintf(yyout, "Syntax OK.\nResult: ");	printList($1, yyout);	fprintf(yyout, "\n"); }
	|
	INPUT EXPLISTI	{ printf("Syntax OK.\nResult: ");	printList($2, stdout);	printf("\n");	fprintf(yyout, "Syntax OK.\nResult: ");	printList($2, yyout);	fprintf(yyout, "\n"); }
	|
	INPUT COMMENT	{ printf("Syntax OK.\nResult: Comment\n\n");	fprintf(yyout, "Syntax OK.\nResult: Comment\n\n"); }
	|
	COMMENT			{ printf("Syntax OK.\nResult: Comment\n\n");	fprintf(yyout, "Syntax OK.\nResult: Comment\n\n"); }
	;

EXPI:
	VALUE {$$ = $1;}
	|
	IDENTIFIER  { 
		Variable var = getByName($1); 
		$$ = var.value; 
	}
	|
	OP_OP OP_PLUS EXPI EXPI OP_CP {$$ = $3 + $4;}
	|
	OP_OP OP_MINUS EXPI EXPI OP_CP {$$ = $3 - $4;}
	|
	OP_OP OP_MULT EXPI EXPI OP_CP {$$ = $3 * $4;}
	|
	OP_OP OP_DIV EXPI EXPI OP_CP {$$ = $3 / $4;}
	|
	OP_OP KW_SET IDENTIFIER EXPI OP_CP { $$ = $4; addVariable($3, $4); }
	|
	OP_OP KW_IF EXPB EXPI OP_CP {
		if($3 == 1 )
			$$ = $4;
		else
			$$ = 0;
	}
	;

EXPB:
	KW_TRUE { $$ = 1; }
	|
	KW_FALSE { $$ = 0; }
	|
	OP_OP KW_AND EXPB EXPB OP_CP { $$ = $3 && $4; }
	|	
	OP_OP KW_OR EXPB EXPB OP_CP { $$ = $3 || $4; }
	|
	OP_OP KW_NOT EXPB OP_CP { $$ = !($3); }
	|
	OP_OP KW_EQUAL EXPB EXPB OP_CP { $$ = ($3 == $4); }
	|
	OP_OP KW_EQUAL EXPI EXPI OP_CP { $$ = ($3 == $4); }
	;

EXPLISTI:
	OP_OP KW_CONCAT EXPLISTI EXPLISTI OP_CP { $$ = concat($3, $4); }
	|
	OP_OP KW_APPEND EXPI EXPLISTI OP_CP { $$ = append($4, $3); }
	|
	OP_OP KW_IF EXPB EXPLISTI OP_CP {
		if($3 == 1 )
			$$ = $4;
		else
			$$ = NULL;
	}
	|
	LISTVALUE { $$ = $1; }
	;

LISTVALUE:
	OP_OP KW_LIST VALUES OP_CP { $$ = $3; }
	|
	OP_OP KW_LIST OP_CP { $$ = initArrayList(); }
	|
	KW_NIL { $$ = NULL; }
	;

VALUES:
	VALUES VALUE { $$ = addToList($1, $2); }
	|
	VALUE { $$ = addToList(NULL, $1); }
	;

%%

int yyerror(char* s){
	printf("SYNTAX_ERROR Expression not recognized\n\n");
	fprintf(yyout,"SYNTAX_ERROR Expression not recognized\n\n");
}

int main(int argc, char* argv[]){
	FILE* filep;
	yyout = fopen("interpreter_output.txt","w");
	
	if(argc == 2){
    	filep = fopen(argv[1], "r");

		if(filep == NULL){
			printf("\nFile can not be found!\n");
		}
		else{
			yyin = filep;
		}
    }
    else if(argc > 2){
    	printf("\n USAGE: %s filename \n", argv[0]);
		printf("filename is optional\n");
    }

	initTable();

	yyparse();

	return 0;

}
