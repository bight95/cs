#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXN 1024
#define FILENAME_MAXN 1024

int read_input_file(char* filename, char* text)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error opening file.");
        return EXIT_FAILURE;
    }

    if(fgets(text, MAXN, fp) == NULL)
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

char * read_filename_stdin(){
    char * filename = malloc(sizeof(char) * (FILENAME_MAXN+1));
    memset(filename, '\0', sizeof(char) * (FILENAME_MAXN+1));
    //fgets(filename, FILENAME_MAXN, stdin);
    scanf("%s", filename);
    return filename;
}