#include<stdio.h>
#include<stdlib.h>

int euclid_extended(int a, int b){
    int remainder, quotient,
        x = 0, y = 1, 
        x_prev = 1, y_prev = 0, x_temp, y_temp, 
        dividend = a, divisor = b;

    if(b == 0) return a;
    if(a == 0) return b;
    quotient = dividend/divisor;
    remainder = dividend%divisor;

    x_temp = x;
    x = x_prev - x*quotient; 
    x_prev = x_temp;
    
    y_temp = y;
    y = y_prev - y*quotient;
    y_prev = y_temp;

    while(1){

        dividend=divisor;
        divisor=remainder;
        
        if(dividend%divisor == 0) break;

        quotient = dividend/divisor;
        remainder = dividend%divisor;

        x_temp = x;
        x = x_prev - x*quotient; 
        x_prev = x_temp;
        
        y_temp = y;
        y = y_prev - y*quotient;
        y_prev = y_temp;
    }

    printf("%d = %d*%d + %d*%d\n", remainder, x, a, y, b);
    return remainder;
}

int main(int argc, char* argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    int GCD = euclid_extended(a, b);
    printf("GCD = %d\n", GCD);
}