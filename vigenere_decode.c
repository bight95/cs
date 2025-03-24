#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "files.h"

char * vigenere_decode(char* cipher, char * key){
    int text_length = strlen(cipher);
    int key_length = strlen(key);

    char * plaintext = (char*)malloc(sizeof(char) * (text_length+1));
    memset(plaintext, '\0', sizeof(char) * (text_length+1));
    int shift = 0;
    char * key_ptr = key;
    for(int i = 0; i<text_length; i++){
        if(isalpha(cipher[i])){
            shift = tolower(*key_ptr) - 'a';
            if(islower(cipher[i])){
                plaintext[i] = 'a' + (cipher[i] - 'a' - shift + 26) %26;
            }
            else{
                plaintext[i] = 'A' + (cipher[i] - 'A' - shift + 26) %26;
            }
            key_ptr++;

        }
        else{
            plaintext[i] = cipher[i];
        }
        if(*key_ptr == '\0')
        key_ptr=key;
    }
    plaintext[text_length] = '\0';
    return plaintext;
}

void read_cipher_from_stdin(){
    char cipher[MAXN];
    char key[MAXN];

    fgets(cipher,MAXN,stdin);
    fgets(key,MAXN,stdin);

    char* last = strrchr(cipher, '\n');
    *last = '\0';

    last = strrchr(key, '\n');
    *last = '\0';

    char * plaintext = vigenere_decode(cipher ,key);
    puts(plaintext);

    free(plaintext);
}

int main(){
    read_cipher_from_stdin();
    return EXIT_SUCCESS;
}

void read_cipher_from_file(){
    char cipher[MAXN];
    char key[MAXN];

    read_input_file(read_filename_stdin(), cipher);
    read_input_file(read_filename_stdin(), key);
    char * plaintext = vigenere_decode(cipher ,key);
    puts(plaintext);
    write_text("vigenere_decoded.txt", plaintext);

    free(plaintext);
}