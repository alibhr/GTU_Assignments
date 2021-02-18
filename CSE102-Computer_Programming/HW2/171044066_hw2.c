#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void menu ();
void draw_hourglass(int height);
void draw_mountain_road(int lenght,int max_radious);
int make_a_guess(int, int, int);
void show_scores(int, int);

int main(){
	srand(time(NULL));//for random numbers.
	menu();		//calling menu function in the main function.
	return 0 ;
}
void menu (){
	int choice,height,lenght,max_radious; //integer variables to use in function.
	int flag=1;	//checking for while loop.
	int score_human=0;
	int score_program=0;	
	int trial,GN,LN,min=1,max=1024,distance,i;//we can chance the min and max values manually in this part.

	while(flag==1){	
		printf("***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("Choice:");
		scanf("%d",&choice);
		switch(choice){
			case 1 :
				LN=(rand()%(max+1-min))+min;//taking random number from funcion and determining the interval of random number.
				printf("%d\n",LN);
				for(trial=1;trial<=10;trial++){//this loop executes 10 times,we can chance the loops number mnually.
					GN=make_a_guess(trial,min,max);//taking a guess number from users.
					distance = LN - GN;//looking for the distance.//LN=lucky number.
					if(distance < 0){//if the distance is greather than lucky number 
						max=GN;		//new maximum of interval will be guess number.
						distance=distance*(-1);//if we are in this block, distance is negative and we need popsitive distance for the next parts.
					}
					if(distance==0){//if distance is 0 ,it means user find the lucky number.
						printf("distance: %d.  you win!\n",distance);
						score_human++;//when the user fint the lucky number ,they get 1 point.
						show_scores(score_human, score_program);//showing the last situation of the competition.
						max=1024;
						min=0;
						break;					
					}
					distance=log2(distance)+1;//(log2(1)=0'ı önlemek için +1 );
					printf("%d\n", distance);
					printf("Distance is %d\n",distance);
					if(GN<LN){
						min=GN;
					}

/**********************This lines work but i think less efficiency*******************/			
/*					else if(distance>=512){
						printf("Distance is 10\n");//showing the distance how far user from the lucky number.
						if(GN<LN){
							min=GN;//user don't have to struggle with smaller numbers than previous guess.  
						}
					}
					else if(distance>=256){
						printf("Distance is 9\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=128){
						printf("Distance is 8\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=64){
						printf("Distance is 7\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=32){
						printf("Distance is 6\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=16){
						printf("Distance is 5\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=8){
						printf("Distance is 4\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=4){
						printf("Distance is 3\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=2){
						printf("Distance is 2\n");
						if(GN<LN){
							min=GN;
						}
					}
					else if(distance>=1){
						printf("Distance is 1\n");
						if(GN<LN){
							min=GN;
						}
					}*/
				}
				if(trial==11){//if the user can't the lucky number this condition will be true so the number must be 1+trial.
					printf("Program win!\n");
					score_program++;//program get 1 point .
					show_scores(score_human, score_program);
					max=1024;
					min=0;
					break ;
				}
				break;
			case 2:
				printf("Enter The height of hourglass :");
				do{
					scanf("%d",&height);
					if(height%2==0){//we don't want even numbers for height.
						printf("Height must be odd number,try again please:\n");
					}
					if(height<0){//height can't be negative numbers.
						printf("Height must be positive,try again please:\n");
					}
				}while(height%2==0 || height<0);

				draw_hourglass(height);
				break;
			case 3:
				printf("Enter the lenght:");
				scanf("%d",&lenght);
				printf("Enter the maximum radius:");
				scanf("%d",&max_radious);
				draw_mountain_road(lenght,max_radious);
				break;
			case 4:
				flag=0;//if the program comes in this block ,flag gonna be zero and loop gonna be over.
				break;
			default ://to check the choosen whether the chosen is valid.
				printf("Tis is an invalid choice.Try again!\n");
		}
	}
}

int make_a_guess(int trial,int min,int max){
	int GN;//guess number.
	printf("(Trial: %d)Make a guess between %d and %d:",trial,min,max);
	scanf("%d",&GN);
	if(GN<min || GN>max){//to check whether the guess in interval.
		printf("This isn't in interval!!!\n");
		make_a_guess(trial,min,max);
	}
	else{
		return GN;
	}
}

void show_scores(int score_human, int score_program){
	printf("Your score: %d    Program score: %d\n",score_human,score_program);
}


void draw_hourglass(int height){
	int i,j;//for loops.
	int temp=((height+1)/2),temp1=height,space=1,star=3;/*aim of temps is saving the essential height.*/
	for(i=1;i<temp;i++){//this loop for top of the hourglass.except the middle.
		for(j=0;j<temp1;j++){
			printf("*");
		}
		temp1=temp1-2;//setting the number of the stars for next lines.
		printf("\n");//go to new line.
		for(j=0;j<space;j++){
			printf(" ");
		}
		space++;//setting the number of space.
	}
	printf("*\n");//middle of the hourglass
	space=space-2;
	for(i=1;i<temp;i++){//this loop for bottom of the hourglass.
		for(j=0;j<space;j++){
			printf(" ");
		}
		space=space-1;//setting the number of space.
		for(j=0;j<star;j++){
			printf("*");
		}
		star=star+2;//setting the number of space.
		printf("\n");
	}
}

void draw_mountain_road(int lenght,int max_radious){
	char back_slash=92;//back slash in ascii.
	int radious;
	int i,j,k;//for loops.
	radious=(rand() % (max_radious+1))+1;
	int space = radious+max_radious;//to prevent the overflow.
	for(k=0;k<lenght;k++){//lenght of the road.
		if(k % 2 == 0){//road starts right side and continue the once in even number.
			radious=rand() % (max_radious+1);
			for(i=0;i<radious;i++){
				for(j=0;j<space;j++){
					printf(" ");
				}
				space--;
				printf("/\n");
			}	
			for(i=0;i<space;i++){
				printf(" ");
			}
			printf("|\n");	
			space++;
			for(i=0;i<radious;i++){
				for(j=0;j<space;j++){
					printf(" ");
				}
				printf("%c\n",back_slash);
				space++;
			}
		}
//
		else{//roads continue the once in odd number.
			radious=rand()%(max_radious+1);	
			for(i=0;i<radious;i++){
				for(j=0;j<space;j++){
					printf(" ");
				}
				space++;
				printf("%c\n",back_slash);
			}	
			for(i=0;i<space;i++){
				printf(" ");
			}
			printf("|\n");
			space--;	
			for(i=0;i<radious;i++){
				for(j=0;j<space;j++){
					printf(" ");
				}
				printf("/\n");
				space--;
			}
		}
	}
}