#ifndef BREAK_H
#define BREAK_H

#define MAX_KEY 25
#define TOP_PICKS 5

typedef struct node
{
    char name[5];
    int distances[50];
    int lenght;
    struct node *next;
} node;

typedef struct
{
    int divisor;
    int points;
} guess;


void break_cypher(char* text);
void bigrams_check(char* text, char* bigram, node **b_list);
void trigrams_check(char* text, char* trigram, node **t_list);
void fourgrams_check(char* text, char* fourgram, node **f_list);
void find_divisors(node *list, int* void_divisors);
int* manage_divsors(int** divisors); //da meglio definire
void free_list(node *list);
char* frequency_analysis(char* text, int kl);

#endif

