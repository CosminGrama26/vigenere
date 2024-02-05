# VIGENÈRE CIPHER

By Florin Cosmin Grama

### Video Demo:  <URL HERE>
## Description:
This C program is designed to encryp and decrypt a text if provided with a key, using the Vigenère polyalphabetic cipher. <https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher>

Additionally, it can also break an encrypt text without knoweledge of the key, by applying cryptanalysis. The different behaviours of the program are selected with command line argument, which defines the mode: `e`, for "encrypt", `d`, for "decrypt", and `b`, for "break".

## Project Components

The project is composed of multiple files:

- `encrypt.c`: Main file, takes and verifies user input, encrypt and decrypts text with a key, or calls the `break_cypher` in `break.c`;
- `break.c`: Finds the lenght of the key by finding repetitions of characters in the text and calculating the most common divisors of the distances of the aformentioned repetitions. This procedure is known as "Kasiski examination". <https://en.wikipedia.org/wiki/Kasiski_examination>;
- `analysis.c`: Splits the text in as many part as the length of the key, perfors a frequency analysis on each subtext and prints the key used to encrypt the text;
- `break.h`: Header file for `break.c`;
- `analysis.h`: Header file for `analysis.c`;
- `Makefile`: Makefile for compilation with gcc.

### Entities in `encrypt.c`

- `main()`: reads command line arguments, validates them and assigns them to variables, which are then passed to other functions. All the other functions in this file are colled by `main()`. In case of decryption, it reverses the values of the provided key. In case the user wants to break the cypher, it calls `break_cypher()` from `break.c`.
- `is_alpha()`: short boolean function used to validate the key.
- `load_file()`: loads the input file binary mode, then uses ftell the measure the length of the text inside the file. Subsequently, closes the file and reaopens it in order to load the text to malloc'd string. Returns the string to `main()`.
- `remove_symbol()`: it removes all non-alphanumeric chars from the input text. In break mode, numerical chars are also removed.
- `encrypt()`: encrypts the text by summing the ASCII value of the plaintext letter with that of the key letter, for the lenght of the text. The key repeats itself if shorter that the text. This function is also called for decryption, but with a reversed key. It modifies the string `text`, which is passed to it by reference, therefore the function doesn't have to return anything, ad it is indeed of type "void".
- `print_text()`: prints the text to an output file.

### Entities in `break.h`
- `node`: struct used by `break.c` for storing data on character repetition as a linked list.
- `guess`: struct used by `break.c` for assigning points to divisors and ranking them.
- This file also defines the constant variables `MAX_KEY` and `TOP_PICKS`.

### Entities in `break.c`
- `beak_cypher()`: this is the "main" function of this file, reponsible for calling the other functions in this file. Once the key lenght is found, it frees all the memory allocated in this file and passes the key lenght value to the  `frequency_analysis()` function in `analysis.c`. 
- `bigrams_check()`: for each possible bigram, if it is repeated in the text, records all the distances between repetions and saves everything on a linked list.
- `trigrams_check()`: same, but for trigrams.
- `fourgrams_check()`: same, but for four-grams.
- `find_divisors()`: from a of repetition distances, extracts the divisors of each distance and stores the data on an array where the index is the divisor, and the value is the numbers of time said divisor has appeared.
- `manage_divisors()`: starting from a 2d array with all divisor occurecies, guesses the most likely key length. In order to do this, calculations are perfomed based on the divisor's value, its occurrencies, and the type of n-gram that generated it. After some testing, we decide to apply the formula used is (divisor value) * (occurencies ^ 2) * (type ^ 5) for divisor point assignement. This formula is broken down in multiple parts of the code, though. The function ultimately returns it's best guess as an "int".
- `free_list()`: fees linked list of distances.

### Entities in `analysis.h`
- This file defines the `ALPHABET` constant. It is set to 26, but it couold be eventually be changed in case of implementation of special characters.

### Entities in `analysis.c`
- The constant arrays `ALPHABET_ENG` and `ALPHABET_ITA` represent the frequency of each alphabet letter in English and Italian language. Other languages might be added.
- `frequency_analysis()`: it is the main function of this file. It calls the other functions, asks the user to pick a language,  and prints the guessed key.
- `split_text()`: splits the text in such a way that each sub-text is composed of all the chars that were coded by a single letter of the key. It returns those sub-texts as an array of pointers. Memory alloc'd in this function is freed by the caller. This split allows us to trea the Vigenère cypher as an array of Ceasar cyphers, and apply frequency analysis to each of them.
- `analyze()`: analyzes each sub-text as Ceasar cypher, by comparing frequency of text letters with that of the plaintext's supposed language. Finds the distance that most accurately represents the frequency shift and returns it as a char.

## Intended use and limitations

#### Text dimensions
If used in encryption or decryption mode, the programs is capable of handling very long texts without any significant delay. 

On the other hand, the break mode should not be used on text thas is longer than approximately 750 words, otherwise the program would run for some seconds before guessing the key. Moreover, if one n-gram repeats itself more than 200 times, it could lead to a segmentation fault. This could easely happen if the user tries to break a long text that was encrypted with a short key. 

#### Attacking capabilities
Usually a 200 word text is more than enough to break the cypher and find the key. Please note though, that as the size of the key is encreased and the one of the text decreased, the probability of finding the key get progressively lower. The ratio at which it can be safely assumed that a cypher is breakable by this program is somewhere around 5 words of text for each letter of the key.

## Future Development
This project could by expanded by adding:
- a manual break mode, in which the user, when presented with analytical data from the program, would have the option to pick different solutions;
- more languages.

