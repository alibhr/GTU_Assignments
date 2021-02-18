#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct line{
	char ID[640];
	char NAME[640];
	char SNAME[640];
	char MAIL[640];
}line;
int NumberOfLine(FILE (*filep)){
	int NL=0;
	char ch ;
	while(!feof(filep)){
		ch=getc(filep);
		if(ch=='\n'||ch==EOF){
			NL++;
		}
	}

	return NL;
}
int main (){
	int NL;
	int i,j,k;
	char ARR[640],c;

	line AR[1280];

	FILE *filep;
	filep=fopen("hw4_disordered_people.txt","r");
	NL=NumberOfLine(filep);
	
	fseek(filep,0,SEEK_SET);

	for(j=0;j<NL;j++){
		for(i=0;i<4;i++){

			fscanf(filep,"%s",ARR);


			if(ARR[0]>='a' && ARR[1]>='a'){				//MAIL
				if('z'>= ARR[0] && 'z'>= ARR[1])
				
				strcpy(AR[j].MAIL,ARR);
			}


			if('Z'>= ARR[0] && 'Z'>= ARR[1]){			//SURNAME
				if(ARR[0]>='A' && ARR[1]>='A'){
					
					strcpy(AR[j].SNAME,ARR);
				}
			}


			if('Z'>= ARR[0] && ARR[1]>='a'){			//NAME
				if(ARR[0]>='A' && 'z'>=ARR[1]){
					
					strcpy(AR[j].NAME,ARR);
				}
			}

			if(ARR[0]>='0' && ARR[1]>='0'){				//ID
				if('9'>ARR[0] && '9'>=ARR[1])
					
					strcpy(AR[j].ID,ARR);
			}
		}
		
	}
	fclose(filep);

	FILE *filepp;
	filepp=fopen("orderedFile.txt","w");
	fprintf(filepp,"%-14s","ID");
	fprintf(filepp,"%-14s","NAME");
	fprintf(filepp,"%-14s","SURNAME");
	fprintf(filepp,"%-14s\n","MAIL");
	for(k=0;k<NL;k++){
		fprintf(filepp,"%-12s  ",AR[k].ID);
		fprintf(filepp,"%-12s  ",AR[k].NAME);
		fprintf(filepp,"%-12s  ",AR[k].SNAME);
		fprintf(filepp,"%-12s\n",AR[k].MAIL);
	}


	return 0 ;
}