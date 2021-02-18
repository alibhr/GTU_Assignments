#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3
#define red 0
#define yellow 1
#define blue 2
#define black 3
#define white 4
#define	square 1
#define rectangular 2
#define circle 3

double CreateBody(int);
int SetColor(int);
double LoadMoves(int,double);
int SetAttackPower(int,int);
void ShowPokemon(int,double,int,double,int);

int main(){	
		int shape,color,attack_power;
		double size_of_body,move_lenght;
		shape=circle;//SQUARE=1/RECTANGULAR=2/CIRCLE=3 Pick one of them.
		size_of_body=CreateBody(shape);
		color=798;//red is 0, yellow is1, blue is 2, black is 3 and white is 4.
		color=SetColor(color);
		move_lenght=LoadMoves(shape,size_of_body);
		attack_power=SetAttackPower(0,150);
		ShowPokemon(shape,size_of_body,color,move_lenght,attack_power);
	return 0;
}

double CreateBody(int shape){
	int lenght,width,radius;
	if(shape==1){
		printf("Enter the lenght\n");
		scanf("%d",&lenght);
		return lenght*lenght;
	}
	if(shape==2){
		printf("Enter the lenght:");
		scanf("%d",&lenght);
		printf("Enter the width:");
		scanf("%d",&width);
		return width*lenght;
	}
	if(shape==3){
		printf("Enter the radius:");
		scanf("%d",&radius);
		return PI*radius*radius;
	}
}

int SetColor(int color){
	if(color >= 0 && color <= 1000){
		return color % 5;
	}
	else{
		return 1;
	}
}

double LoadMoves(int shape,double body_size){
	if(shape==1){
		return (sqrt(body_size))*4;
	}
	if(shape==2){
		return ((body_size / 5) * 2) + 10;
	}
	if(shape==3){
		return 2 * PI * (sqrt(body_size/PI));
	}
}

int SetAttackPower(int lower_bound,int upper_bound){
	int attack;
	srand(time(NULL));
	attack=(rand() % (upper_bound + 1 - lower_bound))+lower_bound;
	return attack;
}

void ShowPokemon(int shape,double body_size,int color,double move_lenght,int attack_power){
	printf("\e[1;H\e[2J\n");
	if(shape==1){
		int i,j, kenar=sqrt(body_size);
		for (i=0;i<kenar;i++){
			for(j=0;j<kenar;j++){
				printf("*");
			}
			printf("\n");
		}
		printf("Name: Square pokemon\n");
	}
	if(shape==2){
		int kenarr,k,l;
		kenarr=(body_size / 5);
		for(k=0;k<kenarr;k++){
			for(l=0;l<5;l++){
				printf("*");
			}
			printf("\n");
		}
		printf("Name: Rectangular pokemon\n");
	}
	if(shape==3){
		int radius=sqrt(body_size / PI);
		int i,j;
		int temp=(radius/2),temp1,temp2,sayi1=1;
		temp1=temp;
		temp2=radius;
		if(radius%2==1){
			sayi1++;
		}
		for(i=1;i<temp2;i++){
			printf("    ");
		}	
		printf("X\n");
		for(i=0;i<temp;i++){
			for(j=1;j<temp1;j++){
				printf("\t");
			}
			temp1--;
			printf("X");
			for(j=0;j<sayi1;j++){
				printf("\t");
			}
			sayi1+=2;
			printf("X\n");
		}	
		temp1++;
		sayi1-=4;
		for(i=1;i<temp;i++){
			for(j=0;j<temp1;j++){
				printf("\t");
			}
			temp1++;
			printf("X");
			for(j=0;j<sayi1;j++){
				printf("\t");
			}
			sayi1=sayi1-2;
			printf("X");
			printf("\n");
		}
		for(i=1;i<temp2;i++){
			printf("    ");
		}
		printf("X\n");
		printf("Name: Circle pokemon\n");
	}
	printf("Size: %.2lf\n", body_size);
	if(color==red){
		printf("Color: Red \n");
	}
	if(color==yellow){
		printf("Color: Yellow \n");		
	}
	if(color==blue){
		printf("Color: Blue \n");	
	}
	if(color==black){
		printf("Color: Black \n");	
	}
	if(color==white){
		printf("Color: White \n");	
	}
	printf("Move: %.2lf\n", move_lenght);
	printf("Attack Power: %d\n", attack_power);
}
