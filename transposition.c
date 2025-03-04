#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    char * key = argv[1];
    int key_length = strlen(key);

    char * plaintext = argv[2];
    int text_len = strlen(plaintext) + 1;

    uint8_t * column_order = malloc(key_length*sizeof(uint8_t));
    uint8_t * column = column_order;

    char* ch_ptr= NULL;
    for(char ch = 'a'; ch<='z'; ch++){
        ch_ptr = strchr(key,ch);
        if(ch_ptr!=NULL){
            *column = ch_ptr - key;
            column++;
        }
        else
        {
        ch_ptr = strchr(key,toupper(ch));
        if(ch_ptr!=NULL){
            *column = ch_ptr - key;
            column++;
        }
        }
    }


    int row_count = text_len % key_length == 0?
                        text_len / key_length:
                        text_len / key_length + key_length-(text_len%key_length);
    char * cipher = malloc(row_count * key_length * sizeof(char));
    memset(cipher, 0, text_len);
    ch_ptr=cipher;
    for(int i =0; i<key_length;i++)
    {
        for(int j = 0; j<row_count; j++){
            *ch_ptr = plaintext[column_order[i]+(j*key_length)];
            ch_ptr++;
        }
    }
    puts(cipher);
}

