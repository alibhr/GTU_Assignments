/* THIS PROGRAM SORTS ARRAY DEMONSTRATION PURPOSES */
/* GTU RULEZ */
#include<stdio.h>
#include <math.h>
#define TRUE 1
#define FALSE 0


int PrintSelection(int selection){
 printf("Selected Menu item is:");
 printf("%d\n",selection);
 return 1;
 
}

int DisplayMenu(){
 int selection;
 printf("\e[2J"); // clears screen
 
 printf("%s","\e[5;31;47mWELCOME TO ADDING PROGRAM\e[0m\n");
 printf("%s","(1) Add two numbers\n");
 printf("%s","(2) Sort an array\n");
 printf("%s","(3) Subtract two numbers\n");
 printf("%s","(4) Divide numbers\n");
 printf("%s","(5) Summarize numbers with words\n");
 printf("%s","(6) Exponent two numbers x to the y\n");
 printf("%s","(0) quit\n");
 printf("Selection:");	
 scanf("%d",&selection);
 PrintSelection(selection);
 return selection;
}

int TenToPow(int stair){			
	int res=1,u;
	for(u=1;u<stair;u++){
		res=res*10;
	}
	return res ;
}

int main(){
int number1, number2, sum;
char wanttoexit = FALSE;
char c;
int choice;
int i,j;
int myArray[100];
int max;
int pivot;
int temp;
int TenToPow(int);
int number,step[10],stair=0,summ;

// main loop
while(wanttoexit == FALSE){

	// display menu and get result	
	choice = DisplayMenu();
	
	
	if(choice == 1){
		printf("%s","PLEASE  ENTER FIRST NUMBER\n");
		scanf("%d",&number1);
		printf("%s","PLEASE  ENTER SECOND NUMBER\n");
		scanf("%d",&number2);
		sum = number1 + number2;
		printf("The result is: ");
		printf("%d\n",sum);
		c=getchar();
		c=getchar();
	}
	if(choice == 2){
		printf("%s","Enter numbers for array and 0 for end\n");
		for(i=0;i<100;i++){
			scanf("%d",&choice);
			if(choice == 0) break;
			myArray[i] = choice;
			max = i ;
		}
		printf("Numbers are entered.. \n");
		printf("Now sorting.. ");
	    for(i=0;i<=max;i++){
	       for(j=0;j<max; j++){
	           if(myArray[j] > myArray[j+1]){
	           		temp = myArray[j];
	           		myArray[j]= myArray[j+1];
	           		myArray[j+1]=temp;
	           }
		    }
		    
		}
		printf("finished..\n ");
	    for(i=0;i<=max;i++){
	      printf("%d  ",myArray[i]);
	    }
	      printf("are the numbers.\n");
	      if(choice==0){
	      	c=getchar();
			c=getchar();
	      	
	      	choice = DisplayMenu();
		  }
	        
		    
		
	}

	if(choice == 3){
		int First,Second,sub;
		printf("PLEASE ENTER FIRST NUMBER \n");
		scanf("%d",&First);
		printf("PLESAE ENTER SECOND NUMBER \n");
		scanf("%d",&Second);
		sub=First-Second;
		printf("The result is: %d\n",sub);
		c=getchar();
		c=getchar();

	}

	if(choice == 4){
		float Divided,Divisor;
		float result;
		printf("\nENTER DIVIDED NUMBER\n");
		scanf("%f",&Divided);
		printf("PLEASE ENTER DIVISOR NUMBER\n");
		scanf("%f",&Divisor);
		result=Divided/Divisor;
		printf("The result is: %f\n",result);
		c=getchar();
		c=getchar();
	}

	if(choice == 5){		
		printf("PLEASE ENTER THE NUMBER\n");
		scanf("%d",&number);
		int car ;
		car=number;											//for negative numbers 
		if(number<0){
			number=number*(-1);
			printf("The result is : -%d = ",number);		//for negative numbers 

		}
		else {printf("The result is : %d = ",number);
		}

		while(number>0){
			stair++;										//to find number of digit
			step[stair]=number%10;							//to put the digits in array
			number=number/10;
		}
		int carry;
		carry=car;											//for negative numbers
		for(stair;stair>0;stair--){
			summ=TenToPow(stair);
			if(stair==1){
				if(carry<0){
					printf("%d)",step[stair]);				//for negative numbers
				}

				else {
					printf("%d",step[stair]);
				}		
				
			}
			else {
				if(car<0){
					printf("-(%dx%d + ",step[stair],summ);	//for negative numbers
					car=1;

				}
				else printf("%dx%d + ",step[stair],summ);
			}
			
		}
			
			c=getchar();
			c=getchar();
	}
	if(choice == 6){
		int base,exponent;
		printf("PLEASE ENTER BASE NUMBER\n");
		scanf("%d",&base);
		printf("PLEASE ENTER EXPONENT NUMBER\n");
		scanf("%d",&exponent);
		int result=1,loop;
			for(loop=1;loop<=exponent;loop++){
				result*=base;
			}
			printf("The result is: %d\n",result);

	}
			c=getchar();
			c=getchar();


	if(choice == 0){
		wanttoexit = TRUE;
		printf("exiting...");
	}
} // end of while

}
