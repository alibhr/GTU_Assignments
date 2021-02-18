#include <stdio.h>
#include <stdlib.h>

#define SIZE 64 

void menu();
void part1();
void part2();
void part3();
void part4();
void part5();

/*functions of part1*/
void factors_of(int temp,int number,int auxilary);
int EBOB(int number1,int number2);

/*functions of part2*/
void print_array_r(int numbers[],int first,int last);
void sort_divide(int numbers[],int first,int last);
void sort_merge(int numbers[],int first,int mid,int last);

/*functions of part3*/
void function_r(int number);

/*functions of part4*/
int check(int number,int digit);
int find_digit(int number);
int pow_r(int base,int exponent);

/*functions of part5*/
char find_the_first_capital_letter(char string[SIZE]);


int main(){

	menu();

	return 0;
}
void menu(){
	int selection=1;
	int flag=1;
	while(flag){
		printf("1) part 1\n");
		printf("2) part 2\n");
		printf("3) part 3\n");
		printf("4) part 4\n");
		printf("5) part 5\n");
		printf("6) exit\n");
		printf("Which part do you want to control ?\n:");
		scanf("%d",&selection);
		if(selection==1){
			part1();
		}
		else if(selection==2){
			part2();
		}
		else if(selection==3){
			part3();
		}
		else if(selection==4){
			part4();
		}
		else if(selection==5){
			part5();
		}
		else if(selection==6){
			flag=0;
		}
		else{
			printf("this is not a valid choice,try again!\n:");
		}
	}
}
void part1(){
	printf("Enter the numbers :\n");
	int number1,number2,i=2,ebob;
	scanf("%d %d",&number1,&number2);

	printf("Factors of %d { ",number1);
	factors_of(number1,number1,i);
	printf("}\n");

	printf("Factors of %d { ",number2);
	factors_of(number2,number2,i);
	printf("}\n");

	ebob=EBOB(number1,number2);
	
	printf("common factor of %d and %d is { ",number1,number2);
	factors_of(ebob,ebob,i);
	printf("}\n");
		
	printf("common factor of %d and %d is %d\n",number1,number2,ebob);
	
}
void factors_of(int temp,int number,int auxilary){
	if(number%auxilary==0 && temp>=auxilary){
		printf("%d ", auxilary);
		factors_of(temp,number/auxilary,auxilary);
	}
	else if(auxilary<=temp){
		factors_of(temp,number,auxilary+1);
	}
}
int EBOB(int number1,int number2){
	if(number2!=0){
		EBOB(number2,number1%number2);
	}
	else{
		return number1 ;
	}
}
/*end of part1*/
void part2(){
	int *numbers,size,i;
	printf("Enter the lenght of list :");
	scanf("%d",&size);
	numbers=(int*)malloc(sizeof(int)*size);
	for(i=0;i<size;i++){
		printf("%d.number:", i+1);
		scanf("%d",&numbers[i]);
//		printf("%d ",numbers[i]);
	}
	printf("unsorted array: ");
	print_array_r(numbers,0,size-1);
	sort_divide(numbers,0,size-1);
	printf("ordered array: ");
	print_array_r(numbers,0,size-1);
	printf("\n");
}
void sort_divide(int numbers[],int first,int last){
//	print_array_r(numbers,first,last);
	int mid;
	if(first<last){
		mid=(first+last)/2;
		sort_divide(numbers,first,mid);
		sort_divide(numbers,mid+1,last);
		sort_merge(numbers,first,mid,last);
	}
}
void sort_merge(int numbers[],int first,int mid,int last){
	int temp_first=first;
	int temp_mid=mid+1;
	int ordered[SIZE];
	int i=0;//indeks of the ordered array.
	
	while(first <= mid && temp_mid <= last){
		if(numbers[first]<=numbers[temp_mid]){
			ordered[i]=numbers[first];
			i++;
			first++;
		}
		else{
			ordered[i]=numbers[temp_mid];
			i++;
			temp_mid++;
		}
	}//en iyi ihtimalle burdaya geldiğinde sıralanmış olacak.when the best case and when program run up to here array will be already ordered.
	while(first<=mid){//sıralanma sırasında kalan olursa sıralanmış arraya geri kalanlar olduğu gibi eklenir çünkü kalanlar zaten sıralanmış.
		ordered[i]=numbers[first];
		i++;
		first++;
	}
	while(temp_mid<=last){//
		ordered[i]=numbers[temp_mid];
		i++;
		temp_mid++;
	}
	for(first=temp_first;first<=last;first++){//sıralanmış arrayi sıralanması gereken arrayin üzerine yazmak.
		numbers[first]=ordered[first-temp_first];
	}
}
void print_array_r(int numbers[],int first,int last){
	if(first<=last){
		printf("%d ",numbers[first]);
		print_array_r(numbers,first+1,last);
	}
	else if(first>last){
		printf("\n");
	}
}
/*end of part2*/
void part3(){
	int number;
	printf("Enter a number:\n");
	scanf("%d",&number);
	function_r(number);
}

void function_r(int number){
	if(number != 1){
		if(number%2==0){
			number=number/2;
			printf("%d\n", number);
			function_r(number);
		}
		else if(number%2==1){
			number=(3*number)+1;
			printf("%d\n", number);
			function_r(number);
		}
	}
}
/*end of part3*/
void part4(){
	int number,digit;
	printf("Enter the number : ");
	scanf("%d",&number);
	digit=find_digit(number);
	if(check(number,digit)==number){
		printf("Equal\n");
	}
	else{
		printf("Not Equal\n");
	}
}
int check(int number,int digit){
	int ans=0;
	if(number >= 1){
		ans=check(number/10,digit)+(pow_r(number%10,digit));
		return ans;
	}
	else{
		return 0;
	}
}

int find_digit(int number){
	int digit=0;
	if(number >= 1){
		digit=1+find_digit(number/10);
	}
	return digit;
}

int pow_r(int base,int exponent){
	if(exponent==0){
		return 1;
	}
	else{
		return base*pow_r(base,exponent-1);
	}
}
/*end of part4*/
void part5(){
	char string_from_user[SIZE],c;
	printf("Enter the string without spaces :\n");
	scanf(" %[^\n]s",string_from_user);
	c=find_the_first_capital_letter(string_from_user);
	if(c=='a'){
		printf("There isn't any uppercasae letter!!\n");
	}
	else{
		printf("%c\n", c);
	}
}

char find_the_first_capital_letter(char string[SIZE]){
//	printf("%c\n", string[0]);
	if(!(string[0]>='A' && string[0]<='Z') && string[0]!='\0'){//if it is not a uppercasae letter .
		return find_the_first_capital_letter(++string);
	}
	else if((string[0]>='A' && string[0]<='Z')){
		return string[0];
	}
	else{
		return 'a';
	}
}
/*end of part5*/