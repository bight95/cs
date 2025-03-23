#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAXN 1000

char * ceasar_cipher(char* str, int key){
    int length = strlen(str);
    char * cipher = (char*)malloc(sizeof(char)*(length+1));
    for(int i =0; i<length; i++){
        if(str[i]>='a' && str[i]<='z'){
            cipher[i]=((str[i]-'a')+key) %26 + 'a';
        }
        else
            if(str[i]>='A' && str[i]<='Z')
                cipher[i]=((str[i]-'A')+key) %26 + 'A';
            else 
                if(str[i]>='0' && str[i]<='9')
                    cipher[i]=((str[i]-'0')+key) %10 + '0';
                else
                    cipher[i]=str[i];
    }
    return cipher;
}

int main(){
    char str[MAXN];
    fgets(str, MAXN-1, stdin);
    int key;
    scanf("%d", &key);
    char* cipher = ceasar_cipher(str, key);

    FILE *fptr;
    fptr = fopen("ceasar_output.txt", "w");
    fprintf(fptr, "%s", cipher);
    fclose(fptr);

    printf("%s\n", cipher);
    return EXIT_SUCCESS;
}
