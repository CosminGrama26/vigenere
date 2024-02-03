#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "analysis.h"

char* frequency_analysis(char* text, int kl)
{
    char** sub_texts;
    sub_texts = text_divider(text, kl);
    char* key = malloc(sizeof(char)*(kl +1));
    return key;
}

char** text_divider(char* text, int p)
{
    int tl = strlen(text);
    //initilise array of strings
    //making room for the exta '\0' of each substring;
    char** texts = calloc(p, sizeof(int));
    for (int i = 0; i < p; i++)
    {
        char* sub_text = calloc((tl/p) + 2, sizeof(char));
        int k = 0;
        for (int j = i; j < tl; j += p, k++)
            sub_text[k] = text[j];

        sub_text[k+1] = '\0';
        texts[i] = sub_text;
    }
    //printf("|||%s|||\n", texts[0]);
    return texts;
}