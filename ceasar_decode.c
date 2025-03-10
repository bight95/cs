#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAXN 1000

char * ceasar_decipher(char* cipher, int key){
    int length = strlen(cipher);
    char * plaintext = (char*)malloc(sizeof(char)*(length+1));
    for(int i =0; i<length; i++){
        if(cipher[i]>='a' && cipher[i]<='z'){
            plaintext[i]=((cipher[i]-'a')-key+26) %26 + 'a';
        }
        else  if(cipher[i]>='A' && cipher[i]<='Z'){
            plaintext[i]=((cipher[i]-'A')-key+26) %26 + 'A';
        }
        else  if(cipher[i]>='0' && cipher[i]<='9'){
            plaintext[i]=((cipher[i]-'0')-key+10) %10 + '0';
        }
        else{
            plaintext[i]=cipher[i];
        }
    }
    return plaintext;
}
int read_cipher(char*filename, char* cipher){
    FILE *fp = fopen(filename,"r");
    if(fp==NULL){
        printf("Error opening the file");
        return EXIT_FAILURE;
    }
    if(fgets(cipher, MAXN, fp)==NULL){
        printf("Error reading the file");
        return EXIT_FAILURE;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

void write_file(char*filename, char* text){
    FILE *fp = fopen(filename,"wb");
    fprintf(fp, "%s", text);
    fclose(fp);
}

int main(){
    char filename[MAXN];
    scanf("%s", &filename);
    char cipher[MAXN];
    read_cipher(filename, cipher);
    
    int key;
    scanf("%d", &key);
    char* plaintext = ceasar_decipher(cipher, key);
    printf("%s\n", plaintext);
    write_file("plaintext.txt", plaintext);
    free(plaintext);
    return EXIT_SUCCESS;
}