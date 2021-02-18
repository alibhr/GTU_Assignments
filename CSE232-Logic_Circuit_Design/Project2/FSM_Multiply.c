#include <stdio.h>

int main(){

    int a ;
    int b ;
    int mult;
    int signBit;

    signBit = 0;   // one bit
    a = -4 ;    // a = a_i;
    b = 5 ;     // b = b_i;
    mult = 0;

    if(a < 0){
        a = ~a;
        ++a;
        signBit = 1;
    }

    while(a > 0){
        mult = mult + b;
        a = a-1;
    }

    if(signBit){
        mult = ~mult;
        ++mult;
    }

    printf("%d\n",mult);

    return 0;
}