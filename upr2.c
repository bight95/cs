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
char* cezar_cipher(char* str, int key)
{
    int length = strlen(str);
    char* cipher = (char*) malloc(sizeof(char) * (length + 1));
    for(int i = 0; i < length; i++)
    {
        cipher[i] = (str[i] - 'a' + key) % 26 + 'a';
    }
    cipher[length] = '\0';
    return cipher;
}
int read_input(char*filename, char* cipher){
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
    char input_text[MAXN];
    read_input(filename, input_text);
    
    int key;
    scanf("%d", &key);

    char option[4];
    char* text = NULL;
    
    while(1)
    {
        puts("[E]ncrypt, [D]ecrypt or END");
        scanf("%s", &option);

        if(strcmp(option, "D") == 0){
            text = ceasar_decipher(input_text, key);
            break;
        }
        else if(strcmp(option, "E")==0){
            text = cezar_cipher(input_text, key);
            break;
        }
        else if(strcmp(option, "END")==0){
            break;
        }
    }
    
    printf("%s\n", text);
    write_file("plaintext.txt", text);
    free(text);
    return EXIT_SUCCESS;
}