#include<stdio.h>
#include<stdlib.h>

int euclid(int a, int b){
    int r;
    r=a%b;

    if(r==0)
        return b;

    while(1){
        a=b;
        b=r;

        if(a%b==0)
            return r;
        else r = a%b;
    }
}

int main(int argc, char* argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d\n",euclid(a,b));
}