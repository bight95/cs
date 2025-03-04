#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000
#define EN_SMALL_START 97
#define EN_CAPITAL_START 65
#define EN_LEN 26
#define EN_SMALL_END EN_SMALL_START + EN_LEN
#define EN_CAPITAL_END EN_CAPITAL_START + EN_LEN

char letter_occur_english[EN_LEN] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'o', 'z'};
int letter_count[EN_LEN];

void print_help()
{
        puts("Usage: <shift> <input>");
}

char *ceasar_cipher(char *str, int shift)
{
        int length = strlen(str);
        char *cipher = (char *)malloc(sizeof(char) * length);

        for (int i = 0; i < length; i++)
        {
                if (str[i] >= EN_SMALL_START && str[i] <= EN_SMALL_END)
                {
                        cipher[i] = ((str[i] - EN_SMALL_START) + shift) % EN_LEN + EN_SMALL_START;
                }
                else if (str[i] >= EN_CAPITAL_START && str[i] <= EN_CAPITAL_END)
                        cipher[i] = ((str[i] - EN_CAPITAL_START) + shift) % EN_LEN + EN_CAPITAL_START;
                else if (str[i] >= '0' && str[i] <= '9')
                        cipher[i] = ((str[i] - '0') + shift) % 10 + '0';
                else
                        cipher[i] = str[i];
        }
        return cipher;
}
bool check_deciphered(char *str)
{
        puts(str);
        puts("------Is it correct [y/n] ?");
        int answer = getchar();
        if (answer == '\n') answer = getchar();
        if (answer == 'y' || answer == 'Y')
                return true;
        else
                return false;
}
char count_letters(char *cipher_str)
{
        memset(letter_count, 0, sizeof(letter_count));
        int index = 0;
        int max_occurances = 0;
        int max_index = 0;
        for (char *i = cipher_str; *i != '\0'; i++)
        {
                if (*i > EN_CAPITAL_START && *i < EN_CAPITAL_END)
                {
                        index = *i - EN_CAPITAL_START;
                        letter_count[index]++;
                        if (letter_count[index] > max_occurances)
                        {
                                max_occurances = letter_count[index];
                                max_index = index;
                        }
                }

                else if (*i > EN_SMALL_START && *i < EN_SMALL_END)
                {
                        index = *i - EN_SMALL_START;
                        letter_count[index]++;
                        if (letter_count[index] > max_occurances)
                        {
                                max_occurances = letter_count[index];
                                max_index = index;
                        }
                }
        }
        return EN_SMALL_START + max_index;
}
int try_letter_occurrence(char *cipher)
{
        char most_common = count_letters(cipher);

        int atempts = 10;
        int shift = 0;
        for (int i = 0; i < atempts; i++)
        {
                shift = EN_LEN-(most_common - letter_occur_english[i]);
                printf("Shift = %d\n", shift);
                if (check_deciphered(ceasar_cipher(cipher, shift)))
                {
                        puts("SUCCESS");
                        exit(EXIT_SUCCESS);
                }
                else
                        continue;
        }
}

int try_brute_force(char *cipher)
{
        for (int i = 1; i < EN_LEN; i++)
        {
                printf("Shift = %d\n", -i);
                if (check_deciphered(ceasar_cipher(cipher, EN_LEN-i)))
                {
                        puts("SUCCESS");
                        exit(EXIT_SUCCESS);
                }
                else
                        continue;
        }
}

void decipher(char *cipher)
{
        try_letter_occurrence(cipher);
        try_brute_force(cipher);
}

int main(int argc, char *argv[])
{
        if (argc < 3)
        {
                print_help();
                return EXIT_SUCCESS;
        }
        char *buf = (char *)malloc((MAX_LEN + 1) * sizeof(char));
        memset(buf, '\0', MAX_LEN + 1);
        strncpy(buf, argv[2], strlen(argv[2]));
        int shift = atoi(argv[1]);

        char *cipher = ceasar_cipher(buf, shift);
        puts(cipher);
        decipher(cipher);
}