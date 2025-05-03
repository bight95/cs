#include<openssl/des.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define KEY_SIZE 8
#define MAXN 100
#define DATA_SIZE 100


int read_input_file(char* filename, char* text, size_t max_length)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error opening file.");
        return EXIT_FAILURE;
    }

    if(fgets(text, max_length, fp) == NULL)
    {
        printf("Error reading from file.");
        return EXIT_FAILURE;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

void write_text(char* filename, char* text)
{
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "%s", text);
    fclose(fp);
}

unsigned char hex_to_byte(const char * hex){
    /*
    unsigned int byte;
    sscanf(hex, "%2x", &byte);
    return (unsigned char) byte;
    */

    char sym1 = *hex;
    char sym2 = *(hex + sizeof(char));

    //not checking if symbol is valid hex symbol
    //symbol = symbol - 'a' +10
    if(sym1>='a') sym1 = sym1-87; else sym1=sym1-'0';
    if(sym2>='a') sym2 = sym2-87; else sym2=sym2-'0';

    unsigned char byte = (unsigned char) ((sym1<<4) | sym2); 
    return byte;
}

char * des_encrypt(const char * input, const char * key){
    unsigned int length = strlen(input);

    int padded_length = ((length+7)/8)*8;
    unsigned char padded_input[padded_length];
    unsigned char output[padded_length];

    memcpy(padded_input, input, length);
    memset(padded_input + length, padded_length-length, padded_length-length);

    DES_key_schedule key_schedule;
    DES_set_key ((DES_cblock*)key, &key_schedule);
    for(int i=0; i<padded_length; i+=8){
        DES_ecb_encrypt((DES_cblock*)(padded_input + i), (DES_cblock*)(output +i ),
         &key_schedule, DES_ENCRYPT);
    }
    char * encrypted_hex = (char*)malloc(padded_length*2 + 1);
    encrypted_hex[padded_length*2]='\0';
    for(int i=0; i<padded_length;i++){
        sprintf(&(encrypted_hex[i*2]), "%2x", output[i]);
    }
    return encrypted_hex;
}

char * des_decrypt(const char * input, const char * key){
    int hex_len = strlen(input);
    if(hex_len%2!=0){
        printf("invalid hex\n");
        return NULL;
    }

    int cipher_len =hex_len/2;
    unsigned char cipher[cipher_len];
    for(int i=0; i<cipher_len;i++){
        cipher[i] = hex_to_byte(&input[i*2]);
    }
    unsigned char decrypted[cipher_len];
    DES_key_schedule key_schedule;
    DES_set_key((DES_cblock*)key, &key_schedule);
    for(int i=0; i<cipher_len; i+=8){
        DES_ecb_encrypt((DES_cblock*)(cipher+i), (DES_cblock*)(decrypted+i), &key_schedule, DES_DECRYPT);
    }
    unsigned char pad_value = decrypted[cipher_len-1];
    if(pad_value>8){
        pad_value=0;
    }
    int original_len = cipher_len-pad_value;
    char * output = (char*)malloc(original_len + 1);
    output[original_len] = '\0';
    memcpy(output, decrypted, original_len);
    return output;
}

int main(int argc, char* argv[]){
    unsigned char key[KEY_SIZE];
    unsigned char input[MAXN];

    read_input_file(argv[1],input, MAXN);
    read_input_file(argv[2], key, KEY_SIZE);

    unsigned char * encrypted = des_encrypt(input, key);
    printf("Encrypted:\n%s\n", encrypted);
    char *decrypted = des_decrypt(encrypted, key);
    printf("Decrypted:\n%s\n", decrypted);

    write_text("des_encrypted.txt", encrypted);
    write_text("des_decrypted.txt", decrypted);

    free(encrypted);
    free(decrypted);

    return EXIT_SUCCESS;
}