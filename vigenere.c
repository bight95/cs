#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EN_SMALL_START 97
#define EN_CAPITAL_START 65
#define EN_LEN 26
#define EN_SMALL_END EN_SMALL_START + EN_LEN
#define EN_CAPITAL_END EN_CAPITAL_START + EN_LEN

char *extend_key(char *orig_key, int length)
{
        char *result = malloc(length * sizeof(char));
        char *ptr = orig_key;
        for (int i = 0; i < length; i++)
        {
                if (*ptr == '\0')
                        ptr = orig_key;
                result[i] = tolower(*ptr);
                ptr++;
        }
        return result;
}

int main(int argc, char *argv[])
{
        char *key = argv[1];
        char *plaintext = argv[2];

        int text_len = strlen(plaintext);
        char *full_key = extend_key(key, text_len);
        char *cipher = malloc((strlen(plaintext) + 1) * sizeof(char));
        char * cipher_ptr=cipher;

        int shift = 0;

        while (*plaintext != '\0')
        {
                if (*plaintext >= EN_SMALL_START && *plaintext <= EN_SMALL_END)
                {
                        shift = *full_key - EN_SMALL_START;
                        *cipher_ptr = ((*plaintext - EN_SMALL_START) + shift) % EN_LEN + EN_SMALL_START;
                        full_key++;
                }
                else if (*plaintext >= EN_CAPITAL_START && *plaintext <= EN_CAPITAL_END)
                {
                        shift = *full_key - EN_SMALL_START;
                        *cipher_ptr = ((*plaintext - EN_CAPITAL_START) + shift) % EN_LEN + EN_CAPITAL_START;
                        full_key++;
                }

                else
                        *cipher_ptr = *plaintext;

                cipher_ptr++;
                plaintext++;
        }

        puts(cipher);
        exit(EXIT_SUCCESS);
}
