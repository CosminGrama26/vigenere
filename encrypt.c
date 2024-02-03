#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "break.h"
#include "analysis.h"

void encrypt(char* text, char* key);
void remove_symbol(char *s, char mode);
bool is_alpha(char* str);
char* load_file(char* textfile_loc);
void print_text(char* text);


int main(int argc, char* argv[])
{
    //check correct number of args
    if (argc != 3 && argc != 4)
    {
        printf("Usage: ./encrypt [FILE] mode (key)\n");
        printf("Modes: e = encrypt, d = decrypt; b = break\n");
        return 1;
    }

    //check validity of key and mode
    if (argv[2][0] != 'b' && argv[2][0] != 'd' && argv[2][0] != 'e')
    {
        printf("Invalid mode.\n");
        return 1;
    } 
    char mode = argv[2][0];

    //loading file
    char* textfile_loc = argv[1];
    char* text = load_file(textfile_loc);
    if (text == NULL)
    {
        printf("Could not locate/load file\n");
        return 1;
    }

    //stip the text of non-alphanumerical chars
    remove_symbol(text, mode);

    //if we go in break mode we don't process argv 3
    if (mode == 'b')
    {
        break_cypher(text);
        print_text(text);
        free(text);   
        return 0;
    }  

    //check key validity
    int key_l = strlen(argv[3]);
    if (key_l > MAX_KEY)
    {
        printf("Maximum key lenght = 25\n");
        return 1;
    }
    if (! is_alpha(argv[3]))
    {
        printf("Key must be alphabetical!\n");
        return 1;
    }
    if (argv[3] == NULL)
    {
        printf("Please provide a key!\n");
        return 1;
    }
      
    //assagning command line argument to variable
    char *key = argv[3];
    
    //key to lower case
    for (int i = 0; i < key_l; i++)
        key[i] = tolower(key[i]);
    


    if (mode == 'e')
        encrypt(text, key);
    
    else if (mode == 'd')
    {   
        //reversing the key for decryption
        char reverse_key [key_l + 1];
            for (int i = 0; i < key_l; i++)
                reverse_key[i] = key[i] - (key[i] - 96) * 2;
        reverse_key[key_l] = '\0';
        encrypt(text, reverse_key);
    }
        
    print_text(text);
    free(text);
    
    return 0;
}

void encrypt(char* text, char* key)
{
    /* initialize key's independent counter,    
     * because is not used for white spaces, symbols or numbers*/
    int k = 0;
    int key_length = strlen(key);
    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        
        // for redeability
        unsigned char c = text[i];
        // Uppercase characters
        if (c >= 65 && c <= 90)
        {
            c += (key[k % key_length] - 96);
            k++;
            if (c > 90)     //wrap-around
                c -= 26;
            else if (c < 65) //wrap-around for decryption
                c += 26;
        }
        // lowercase charactes
        else if (c >= 97 && c <= 122)
        {
            c += (key[k % key_length] - 96);
            k++;
            if (c > 122)     
                c -= 26;
            else if (c < 97)
                c += 26;
        }        
        text[i] = c;    
    }
    
}

void remove_symbol(char *str, char mode)
{
    int new = 0, old = 0;
    
    //in break mode we also have to get rid of numbers from text
    if (mode == 'b')
    {
        while (str[old])
        {
        if ((str[old] >= 65 && str[old] <= 90)
         || (str[old] >= 97 && str[old] <= 122))
            str[new++] = str[old];
        old++;       
        }
    }
    else
    {
        while (str[old])
        {
            if ((str[old] >= 65 && str[old] <= 90)
            || (str[old] >= 97 && str[old] <= 122)
            || (str[old] >= 48 && str[old] <= 57))
                str[new++] = str[old];
            old++;       
        }        
    }
    str[new]=0;
}

bool is_alpha(char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] < 65 || (str[i] > 90 && str[i] < 97) || str[i] > 122)
            return false;
    }
    return true;
}

char* load_file(char* textfile_loc)
{
    FILE *textfile_l = fopen(textfile_loc, "rb");
    if (textfile_l == NULL)
        return NULL;

    fseek(textfile_l, 0, SEEK_END); // seeks EoF
    long f_size = ftell(textfile_l); // tell position in bytes
    fclose(textfile_l);

    FILE *textfile = fopen(textfile_loc, "r");
    if (textfile == NULL)
        return NULL;
    
    char* text = malloc(f_size + 1);
    fread(text, 1, f_size, textfile);
    text[f_size] = '\0';
    fclose(textfile);
    return text;
}

void print_text(char* text)
{
    //char* filename = malloc(sizeof(char) * 100);
    //filename = strcat("output_", name);
    FILE *output = fopen("output.txt", "w");
    fwrite(text, strlen(text), 1, output);
    fclose(output);
}
