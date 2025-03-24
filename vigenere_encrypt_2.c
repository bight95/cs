#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "files.h"

char * vigenere_encrypt(char* plaintext, char * key){
    int text_length = strlen(plaintext);
    int key_length = strlen(key);

    char * cipher = (char*)malloc(sizeof(char) * (text_length+1));
    memset(cipher, '\0', sizeof(char) * (text_length+1));
    int shift = 0;
    char * key_ptr = key;
    for(int i = 0; i<text_length; i++){
        if(isalpha(plaintext[i])){
            //shift = tolower(key[i%key_length]) - 'a';
            shift = tolower(*key_ptr) - 'a';
            if(islower(plaintext[i])){
                cipher[i] = 'a' + (plaintext[i] - 'a' + shift) %26;
            }
            else{
                cipher[i] = 'A' + (plaintext[i] - 'A' + shift) %26;
            }
            key_ptr++;
            if(*key_ptr == '\0')
                key_ptr=key;
        }
        else{
            cipher[i] = plaintext[i];
        }
    }
    cipher[text_length] = '\0';
    return cipher;
}



int main(){
    
    char text[MAXN];
    char key[MAXN];

    //scanf("%s",text);
    read_input_file(read_filename_stdin(), text);
    read_input_file(read_filename_stdin(), key);

    //scanf("%s",key);

    char * cipher = vigenere_encrypt(text ,key);
    puts(cipher);
    write_text("vigenere_cypher.txt", cipher);

    free(cipher);

    return EXIT_SUCCESS;

    // Напишете програма, която прочита текстов файл със съобщение за шифриране и друг текстов файл с ключ за шифриране. 
    // Програмата да създава текстов файл с шифъра, който е получен.


}