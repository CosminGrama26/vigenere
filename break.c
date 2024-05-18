#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "break.h"
#include "analysis.h"

void break_cypher(char* text)
{
    //create linked list for bigrams
    node *b_list = NULL;
    char bigram[2] = {'a', 'a'};
    bigrams_check(text, bigram, &b_list);
    int* b_divisors = calloc(MAX_KEY, sizeof(int));
    if (b_divisors == NULL)
    {
        free(text);
        free_list(b_list);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }   
    
    find_divisors(b_list, b_divisors);
    free_list(b_list);

    //create linked list for trigrams
    node *t_list = NULL;
    char trigram[3] = {'a', 'a', 'a'};
    trigrams_check(text, trigram, &t_list);
    int* t_divisors = calloc(MAX_KEY, sizeof(int));
    if (t_divisors == NULL)
    {
        free(text);
        free(b_divisors);
        free_list(t_list);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }  

    find_divisors(t_list, t_divisors);
    free_list(t_list);

    //create linked list for fourgrams
    node *f_list = NULL;
    char fourgram[4] = {'a', 'a', 'a', 'a'};
    trigrams_check(text, fourgram, &f_list);
    int* f_divisors = calloc(MAX_KEY, sizeof(int));
    if (f_divisors == NULL)
    {
        free(text);
        free(b_divisors);
        free(t_divisors);
        free_list(f_list);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }  

    find_divisors(f_list, f_divisors);
    free_list(f_list);

    int* divisors[3]= {b_divisors, t_divisors, f_divisors};
    int kl = manage_divsors(divisors);
    free(b_divisors);
    free(t_divisors);
    free(f_divisors);

    frequency_analysis(text, kl);
}

void bigrams_check(char* text, char* bigram, node **b_list)
{
    //initializing counters and node
    int position = 0;
    int occurence = 0;
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(text);
        free(b_list);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }   

    for (int i = 0; i < strlen(text) - 2; i++)
    {
        //check for bigram presence in text
        if (bigram[0] == text[i] && bigram[1] == text[i+1])
        {
            occurence ++;
            // if occurence > 1, we can start mesuring distances
            if (occurence >= 2)
                n->distances[occurence - 2] = i - position;
            position = i;
        }
    }
    // if we have at least 1 distance we link the node to the list
    if (occurence >= 2)
    {    
        n->lenght = occurence - 1;
        n->next = NULL;
        n->next = *b_list; // point to where b_list previously pointed
        *b_list = n; //b_list now points to n
    }
    //else we free the node
    else
        free(n);

    //update bigram with next alphabet letter
    bigram[1] ++;
        if (bigram[1] == 123)
        {
            bigram[1] = 97;
            bigram[0] ++;
                //went through all bigrams, exiting
                if (bigram[0] == 123)
                    return;          
        }
    // recursively call itself with updated bigram and list
    bigrams_check(text, bigram, b_list);
}

void trigrams_check(char* text, char* trigram, node **t_list)
{
    int position = 0;
    int occurence = 0;
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(text);
        free(t_list);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }   

    for (int i = 0; i < strlen(text) - 2; i++)
    {
        if (trigram[0] == text[i] && trigram[1] == text[i+1] && trigram[2] == text[i+2])
        {
            occurence ++;
            if (occurence >= 2)
                n->distances[occurence - 2] = i - position;
            position = i;
        }
    }

    if (occurence >= 2)
    {    
        n->lenght = occurence - 1;
        n->next = NULL;
        n->next = *t_list;
        *t_list = n;
    }
    else
        free(n);

    trigram[2] ++;
    if (trigram[2] == 123)
    {
        trigram[2] = 97;
        trigram[1] ++;
        if (trigram[1] == 123)
        {
            trigram[1] = 97;
            trigram[0] ++;
            if (trigram[0] == 123)
                return;   
        }                    
    }

    trigrams_check(text, trigram, t_list);
}

void fourgrams_check(char* text, char* fourgram, node **f_list)
{
    int position = 0;
    int occurence = 0;
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(text);
        free(f_list);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }   

    for (int i = 0; i < strlen(text) - 2; i++)
    {
        if (fourgram[0] == text[i] && fourgram[1] == text[i+1] &&
            fourgram[2] == text[i+2] && fourgram[3] == text [1+3])
        {
            occurence ++;
            if (occurence >= 2)
                n->distances[occurence - 2] = i - position;
            position = i;
        }
    }

    if (occurence >= 2)
    {    
        n->lenght = occurence - 1;
        n->next = NULL;
        n->next = *f_list;
        *f_list = n;
    }
    else
        free(n);

    fourgram[3] ++;
    if (fourgram[3] == 123)
    {
        fourgram[3] = 97;
        fourgram[2] ++;
        if (fourgram[2] == 123)
        {
            fourgram[2] = 97;
            fourgram[1] ++;
            if (fourgram[1] == 123)
            {
                fourgram[1] = 97;
                fourgram[0] ++;
                if (fourgram[0] == 123)
                    return;   
            }                    
        }
    }

    fourgrams_check(text, fourgram, f_list);
}

void find_divisors(node *list, int* void_divisors)
{
    //extract divisors from linked list
    node *ptr = list;
    while (ptr != NULL)
    {
        for (int i = 0; i < ptr->lenght; i++)
        {
            int distance = ptr->distances[i];
            for (int j = 1; j < MAX_KEY; j++)
            {
                if (distance % j == 0)
                    void_divisors[j] ++;
            }
        }
        ptr = ptr->next;
    }
    free(ptr);
}

int manage_divsors(int** divisors)
{
    int most_likely[3][TOP_PICKS];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < TOP_PICKS; j++)
            most_likely[i][j] = 0;

    for (int h = 0; h < 3; h++)
    {   
        int* current_div = divisors[h];
        int top[TOP_PICKS];
        long int top_v[TOP_PICKS];
        for (int i = 0; i < TOP_PICKS; i++)
        {
            top[i] = 0;
            top_v[i] = 0;
        }
        
        int type = h + 2;
        //loops through divisors of current array (of 3)
        for (int i = 2; i < MAX_KEY; i++)
        {
            //array position = divisor; value = occurences
            int occurences = current_div[i];  
            long int value = pow(occurences, 1.35) * i;

            for (int j = 0; j < TOP_PICKS; j++)
            {
                if (value > top_v[j])
                {
                    //moving smaller list elements
                    for (int k = TOP_PICKS - 2; k >= j; k--)
                    {
                        top[k + 1] = top[k];
                        top_v[k + 1] = top_v[k];
                    }
                    //insert new element in his position
                    top[j] = i;
                    top_v[j] = value;
                    break;
                }
            }
        }
        //populating 2d array of picks
        for (int i = 0; i < TOP_PICKS; i++)
            most_likely[h][i] = top[i];  
    }

    //initialising array of guesses
    guess guesses[15];
    for (int i = 0; i < 15; i++)
    {
        guesses[i].divisor = 0;
        guesses[i].points = 0;
    }

    //put all different top guesses into a single array
    //best score is the lowest
    int guess_counter = 0;
    bool present = 0;
    for (int h = 0; h < 3; h++)
    {
        int type = h + 2;
        for (int i = 0; i < TOP_PICKS; i++)
        {
            present = 0;
            for (int j = 0; j < 15; j++)
            {
                if (most_likely[h][i] == guesses[j].divisor)
                {
                    guesses[j].points += type * (i + 1);
                    present = 1;
                    break;
                }
            }
            if (!present)
            {
                guesses[guess_counter].divisor = most_likely[h][i];
                guesses[guess_counter].points += pow(type, 5) * (i + 1);
                guess_counter ++;
            }
        }      
    }
    //bubble sort in asc order
    for (int h = 0; h < guess_counter - 1; h++)
    { 
        for (int i = 0; i < guess_counter - 1 - h; i++)
        {
            if (guesses[i].points > guesses[i+1].points)
            {
                guess temp = guesses[i+1];
                guesses[i+1] = guesses[i];
                guesses[i] = temp;
            }
        }
    }

    //returning best guess
    return guesses[0].divisor;
}

void free_list(node *list)
{
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}