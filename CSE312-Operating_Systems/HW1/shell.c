#include <stdio.h>

int main(){
	int q=0;
	int selection = 0;

	while(!q){
		
		// print menu
		printf("\n%s%s%s%s", 
			"\t1 - Run ShowPrimes.asm\n",
			"\t2 - Run Factorize.asm\n",
			"\t3 - Run BubbleSort.asm\n",
			"\t0 - Exit\n"
		);

		//take input
		printf("your selection: ");
		scanf("%d", &selection);

		//make systemcall
		if(selection == 0){
			q = 1;
		}
		else if(selection == 1){
			// asm("li $t0, 1\n\tbeq $s0, $t0, _primes\n");
		}
		else if(selection == 2){
			// asm("li $t0, 2\n\tbeq $s0, $t0, _factorize\n");	
		}
		else if(selection == 3){
			// asm("li $t0, 3\n\tbeq $s0, $t0, _bubble_sort\n");
		}
		else{
			printf("invalid input\n");
		}

	}

	return 0;
}
