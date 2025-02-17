#include<stdbool.h>
#include<math.h>
#include<stdio.h>

bool isPrime(int num){
    double end=sqrt((double)num);
    for(int i=2; i<end; i++){
        if(num%i==0) return false;
    }
    return true;
}

int main(){
    int num;
    scanf("%d",&num);

    if(isPrime(num)){
        puts("It's prime");
    }
    else{
        puts("It's not prime");
    }

}
