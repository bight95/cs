#include<stdbool.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

bool isPrime(int num){
    double end=sqrt((double)num);
    for(int i=2; i<end; i++){
        if(num%i==0) return false;
    }
    return true;
}

bool* eratosten(int n){
    bool* seive = (bool*)malloc(sizeof(bool) * (n+1));
    memset(seive, false, sizeof(bool) * (n+1));
    for(int i=2; i<=n; i++){
        if(seive[i]==false){
            for(int j=i+i; j<=n; j+=i){
                seive[j]=true;
            }
        }
    }
    return seive;
}
void print_numbers(bool * seive, int n){
    for(int i=2; i<=n; i++){
        if(!seive[i])
            printf("%2d ", i);
    }
    puts("");
}

int main(){
    int n;
    scanf("%d", &n);

    if(isPrime(n)){
        puts("It's prime");
    }
    else{
        puts("It's not prime");
    }

    bool* seive = eratosten(n);
    print_numbers(seive,n);
    free(seive);
    return EXIT_SUCCESS;
}