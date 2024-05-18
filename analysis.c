#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#include "analysis.h"

const float ALPHABET_ITA[ALPHABET] = {11.74, 0.92, 4.5, 3.73, 11.79,
    0.95, 1.64, 1.54, 11.28, 0, 0, 6.51, 2.51, 6.88, 9.83, 3.05,
    0.51, 6.37, 4.98, 5.62, 3.01, 2.1, 0, 0, 0, 0.49};

const float ALPHABET_ENG[ALPHABET] = {8.2, 1.5, 2.8, 4.3, 12.7,
    2.2, 2, 6.1, 7, 0.15, 0.77, 4.0, 2.4, 6.7, 7.5, 1.9,
    0.095, 6, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2, 0.074};

void frequency_analysis(char* text, int kl)
{      
    //text to lowe case
    for (int i = 0; i < strlen(text); i++)
        text[i] = tolower(text[i]);

    //create array of subtexts
    char** sub_texts;
    sub_texts = split_text(text, kl);
    char key[kl+1];

    const float *pAlphabet = NULL;
    char language[4];

    printf("What language do you expect the original text to be written in? (ITA / ENG): ");

    for (;;)
    {       
        scanf("%3s", language);
        char c;
        while ((c = getchar()) != '\n' && c != EOF);       //flushing input buffer;
       
        for (int i = 0; i < 3; i++)
            language[i] = toupper(language[i]);
        
        if (strcmp(language, "ITA") == 0)
        {
            pAlphabet = ALPHABET_ITA;
            break;
        }
        else if (strcmp(language, "ENG") == 0)
        {
            pAlphabet = ALPHABET_ENG;
            break;
        }   
        else printf("Please type ITA or ENG\n");
    }

    for (int i = 0; i < kl; i++)
    {
        key[i] = analyze(sub_texts[i], pAlphabet);
        free(sub_texts[i]);
    }

    free(sub_texts);
    key[kl] = '\0';

    printf("|||| KEY = %s ||||\n", key);
    printf("You can now run the program in decrypt mode providing the key.\n");
}

char** split_text(char* text, int p)
{
    //split the text in p parts, each part is coded by 1 of the keys letters

    int tl = strlen(text);
    //initilise array of strings
    char** texts = calloc(p, sizeof(char*));
    if (texts == NULL)
    {
        free(text);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < p; i++)
    {
        //each substring has the length of text/p
        char* sub_text = calloc((tl/p) + 2, sizeof(char));
        if (sub_text == NULL)
        {
            free(text);
            for (int m = 0; m < i; m++)
                free(texts[m]);
            free(texts);
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        int k = 0;
        for (int j = i; j < tl; j += p, k++)
            sub_text[k] = text[j];

        sub_text[k] = '\0';
        texts[i] = sub_text;
    }
    return texts;
}

char analyze(char* text, const float target_alphabet[ALPHABET])
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
    }

    float score[ALPHABET];   
    for (int i = 0; i < ALPHABET; i++)
        score[i] = 0;

    for (int i = 0; i < ALPHABET; i++)  //loops possible transaltion lenght (i.e alphabet)
    {
        float points = 0;
        int move = i + 1;       //char at position 0 (a) moves the text by 1, etc.
        for (int j = 0; j < ALPHABET; j++)  //loops frequency in target text
        {
            int shift = move + j;
            if (shift >= ALPHABET)       
                shift -= ALPHABET;      //wrap around

            float closeness = frequency[shift] - target_alphabet[j];
                if (closeness < 0)
                    closeness *= -1;
            points += closeness;
        }
        score[i] = points;
    }


    float best_result = pow(ALPHABET, 2);    //just an arbitrary very very bad score
    int best = 0;
    for (int i = 0; i < ALPHABET; i++)       //finding the lowest score
        if (score[i] < best_result)
        {
            best_result = score[i];
            best = i;
        }

    return ('a' + best);
}