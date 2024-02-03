#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "analysis.h"

char* frequency_analysis(char* text, int kl)
{
    //text to lowe case
    for (int i = 0; i < strlen(text); i++)
        text[i] = tolower(text[i]);

    //create array of subtexts
    char** sub_texts;
    sub_texts = text_divider(text, kl);
    char* key = malloc(sizeof(char)*(kl +1));

    for (int i = 0; i < kl; i++)
    {
        key[i] = analyze(sub_texts[i]);
    }

    free(sub_texts);
    key[kl] = '\0';
    return key;
}

char** text_divider(char* text, int p)
{
    //split the text in p parts, each part is coded by 1 of the keys letters

    int tl = strlen(text);
    //initilise array of strings
    char** texts = calloc(p, sizeof(char*));
    for (int i = 0; i < p; i++)
    {
        //each substring has the length of text/p
        char* sub_text = calloc((tl/p) + 2, sizeof(char));
        int k = 0;
        for (int j = i; j < tl; j += p, k++)
            sub_text[k] = text[j];

        sub_text[k+1] = '\0';
        texts[i] = sub_text;
    }
    return texts;
}

char analyze(char* text)
{
    /*compares alphabet frequencies to text frequencies
     *horizontal translation of distribution = key letter position in alphabet*/

    int tl = strlen(text);
    //initialising array of char frequency in text
    float frequency[ALPHABET];   
    for (int i = 0; i < ALPHABET; i++)
        frequency[i] = 0;

    for (char c = 'a'; c <= 'z'; c++)   //loops alphabet
    {
        int letter_n = c - 97;          //a = 0, b = 1, ...
        for (int i = 0; i < tl; i++)  //loops text
        {
            if (c == text[i])
                frequency[letter_n]++;    
        }
        frequency[letter_n] = frequency[letter_n] * 100 / tl;
        printf("Char: %c -- Frequency: %2f\n", c, frequency[letter_n]);
    }
    printf("\n");
    return 'a';
}