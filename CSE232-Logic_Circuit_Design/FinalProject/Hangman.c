#include <stdio.h>

int main(){

    char *theWord = "RAHAB000";

    int numberOfCharacters = 5;

    int i = 0;

    int foundedLetter = 0;

    int mistakes = 0;

    int isFound = 0;

    char temp[] = "00000000";

    char input;

    printf("numberOfCharacters : %d\n",numberOfCharacters);

    while(mistakes<10 && foundedLetter<numberOfCharacters ){
        printf("mistakes : %d, foundedWord : %d\n",mistakes,foundedLetter);
        scanf(" %c",&input);
        isFound = 0;
        i=0;
        while(i<numberOfCharacters){
            if(theWord[i]==input){
                temp[i] = input;
                ++foundedLetter;
                isFound = 1;
            }
            ++i;
        }
        if(!isFound){
            ++mistakes;
        }

        i = numberOfCharacters - 1 ;
        while(i>=0){
            if(temp[i] != '0')
                printf(" %c ",temp[i]);
            else
                printf(" _ ");
            --i;
        }
        printf("\n");

    }

    if(foundedLetter == numberOfCharacters){
        printf("Win\n");
    }
    else{
        printf("Lost\n");
    }
}
