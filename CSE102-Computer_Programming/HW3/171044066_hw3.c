//Total Homework 3
#include <stdio.h>

int simple_calculator_program();/*Part 1*/
int avarage_calculate();		/*Part 2*/
int draw_shape_diamond();		/*Part 3*/

/*beginning of functions for part 1 */
int doit(int process(),int first_number,int second_number);
int addition(int first_number,int second_number);
int substraction(int first_number,int second_number);
int multiplication(int first_number,int second_number);
int division(int first_number,int second_number);
int power(int first_number,int second_number);
int modulo(int first_number,int second_number);
/*end of functions for part 1 */

/*beginning of functions for part 2 */
int take_grades(int[]);
int take_exam_grades(int[]);
double calculate_homework(int[]);
double calculate_lab(int[]);
double calculate_all(int,int[],int);
/*end of functions for part 2 */

int main(){
	int flag=1;
	int selection=0;
	while(flag){
		printf("******************* Homework 3 *******************\n");
		printf("part 1) Simple calculator program.(press 1)\n");
		printf("part 2) calculate weighted average.(press 2)\n");
		printf("part 3) draw shape.(press 3)\n");
		printf("press 0(zero) to quit\n");
		printf("******************* Homework 3 *******************\n");
		scanf("%d",&selection);

		if(selection == 1){
			simple_calculator_program();
		}
		if(selection == 2){
			avarage_calculate();
		}
		if(selection == 3){
			draw_shape_diamond();
		}
		if(selection == 0){
			printf("Done\n");
			flag=0;
		}
	}
	return 0;
}

/*Beginning of part 1*/
int simple_calculator_program(){

	int quit = 0, first_number = 0, second_number = 0, prev = 0;
	char expression[64], operator[2];
	printf("******************* Part 1 *******************\n");
	printf("program starts from 0.\n");
	printf("addition:(+)\nsubstraction:(-)\nmultiplication:(*)\ndivision:(/)\npower:(**)\nmodulo:(%%)\nMenu(m)\n");
	printf("example usage (** 2 8) or (** 2)\t(don't forget the spaces)\n");
	printf("******************* Part 1 *******************\n");

	//buffer problem
	while ((getchar()) != '\n'); 

	while( !quit ){
		
		fgets(expression,64,stdin);
		int test = sscanf(expression,"%s%d%d", operator, &first_number, &second_number);

		if( test == 2 ){
			second_number = first_number;
			first_number = prev;
		}

		if( operator[0] == '*' && operator[1] == '*' ){
			prev = doit(power,first_number,second_number);
		}

		else if( operator[0] == '*' ){
			prev = doit(multiplication,first_number,second_number);
		}
		
		else if( operator[0] == '/' ){
			if(second_number != 0)
				prev = doit(division,first_number,second_number);
			else
				printf("second number can't be zero! (division)\n");
		}
		
		else if( operator[0] == '+' ){
			prev = doit(addition,first_number,second_number);
		}
		
		else if( operator[0] == '-' ){
			prev = doit(substraction,first_number,second_number);
		}
		
		else if( operator[0] == '%' ){
			if(second_number != 0)
				prev = doit(modulo,first_number,second_number);
			else
				printf("second number can't be zero! (modulo)\n");
		}
		
		else if( operator[0] == 'm' || operator[0] == 'M'){
			quit = 1;
		}
		
		else{
			printf("invaild operation !.\n");
		}

		printf("%d\n", prev);
	}
	return 0;
}

int doit(int process(),int first_number,int second_number){
	return process(first_number,second_number);
}
int addition(int first_number,int second_number){
	return (first_number + second_number);
}
int substraction(int first_number,int second_number){
	return (first_number - second_number);
}
int multiplication(int first_number,int second_number){
	return (first_number * second_number);
}
int division(int first_number,int second_number){
	return (first_number / second_number);
}
int power(int first_number,int second_number){
    int i,result=1;
    for(i=0;i<second_number;i++){
        result=result*first_number;
    }
	return result;
}
int modulo(int first_number,int second_number){
	return (first_number % second_number);
}
/*End of part 1*/

/*Beginning of part 2*/
int avarage_calculate(){
	int i;
	int homework_grades[10];
	int lab_grades[10];
	int mid_and_final[2];
	double average_lab,average_homework;
	double weighted_avereage;
	printf("FOR HOMEWORK\n");
	take_grades(homework_grades);
	printf("FOR LAB\n");
	take_grades(lab_grades);
	take_exam_grades(mid_and_final);
	average_homework=calculate_homework(homework_grades);
	average_lab=calculate_lab(lab_grades);
	weighted_avereage=calculate_all(average_homework,mid_and_final,average_lab);
	printf("weighted avereage :%.2lf\n",weighted_avereage);
	return 0;
}
int take_grades(int grades[]){
	int i;
	for(i=0;i<10;i++){
		printf("Enter your grade %d:",i+1);
		scanf("%d",&grades[i]);
	}
}
int take_exam_grades(int grade[]){
	printf("Enter your midterm grade: ");
	scanf("%d",&grade[0]);
	printf("Enter your Final grade: ");
	scanf("%d",&grade[1]);
}
double calculate_homework(int grades[]){
	int i ;
	double average=0.0;
	for(i=0;i<10;i++){
		average=average+grades[i];
	}
	return (average/10.0);
}
double calculate_lab(int grades[]){
	int i ;
	double average=0.0;
	for(i=0;i<10;i++){
		average=average+grades[i];
	}
	return (average/10.0);	
}
double calculate_all(int homework,int mid_and_final[],int lab){
	double weighted_avereage;
	weighted_avereage=(homework/10.0)+(lab/5.0)+(mid_and_final[0]*(3.0/10.0))+(mid_and_final[1]*(4.0/10.0));
	return weighted_avereage;	
}
/*End of part 2*/

/*Beginning of part 3*/
int draw_shape_diamond(){
	int i,j;//for loops.
	int height,temp,star=0;
	printf("Enter the height of shape:");
	scanf("%d",&height);
	temp=height;
	for(i=0;i<height;i++){
		for(j=1;j<temp;j++){
			printf(" ");
		}
		temp--;
		printf("/");
		for(j=0;j<star;j++){
			printf("*");
		}
		star=star+2;
		printf("\\");
		printf("\n");
	}
	star=star-2;
	for(i=0;i<height;i++){
		for(j=0;j<temp;j++){
			printf(" ");
		}
		temp++;
		printf("\\");
		for(j=0;j<star;j++){
			printf("*");
		}
		star=star-2;
		printf("/\n");
	}
	return 0 ;
}
/*End of part 2*/
