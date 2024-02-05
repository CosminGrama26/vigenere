# VIGENERE CIPHER
## Video Demo:  <URL HERE>
## Description:
This C program is designed to encryp and decrypt a text if provided with a key, using the Vigenère polyalphabetic cipher. <https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher>

Additionally, it can also break an encrypt text without knoweledge of the key, by applying cryptanalysis. The different behaviours of the program are selected with command line argument, which defines the mode: `e`, for "encrypt", `d`, for "decrypt", and `b`, for "break".

### Project Components

The project is composed of multiple files:

- `encrypt.c`: Main file, takes and verifies user input, encrypt and decrypts text with a key, or calls the `break_cypher` in `break.c`;
- `break.c`: Finds the lenght of the key by finding repetitions of characters in the text and calculating the most common divisors of the distances of the aformentioned repetitions. This procedure is known as "Kasiski examination". <https://en.wikipedia.org/wiki/Kasiski_examination>;
- `analysis.c`: Splits the text in as many part as the length of the key, perfors a frequency analysis on each subtext and prints the key used to encrypt the text;
- `break.h`: Header file for `break.c`;
- `analysis.h`: Header file for `analysis.c`;
- `Makefile`: Makefile for compilation with gcc.

#### Entities in `encrypt.c`

- `main()`: reads command line arguments, validates them and assigns them to variables, which are then passed to other functions. All the other functions in this file are colled by `main()`. In case of decryption, it reverses the values of the provided key. In case the user wants to break the cypher, it calls `break_cypher()` from `break.c`.
- `is_alpha()`: short boolean function used to validate the key.
- `load_file()`: loads the input file binary mode, then uses ftell the measure the length of the text inside the file. Subsequently, closes the file and reaopens it in order to load the text to malloc'd string. Returns the string to `main()`.
- `remove_symbol()`: it removes all non-alphanumeric chars from the input text. In break mode, numerical chars are also removed.
- `encrypt()`: encrypts the text by summing the ASCII value of the plaintext letter with that of the key letter, for the lenght of the text. The key repeats itself if shorter that the text. This function is also called for decryption, but with a reversed key. It modifies the string `text`, which is passed to it by reference, therefore the function doesn't have to return anything, ad it is indeed of type "void".
- `print_text()`: prints the text to an output file.

#### Entities in `break.h`
- `node`: struct used by `break.c` for storing data on character repetition as a linked list.
- `guess`: struct used by `break.c` for assigning points to divisors and ranking them.

#### Entities in `break.c`
- `beak_cypher()`: this is the "main" function of this file, reponsible for calling the other functions in this file. Once the key lenght is found, it frees all the memory allocated in this file and passes the key lenght value to the  `frequency_analysis()` function in `analysis.c`. 
- `bigrams_check()`: for each possible bigram, if it is repeated in the text, records all the distances between repetions and saves everything on a linked list.
- `trigrams_check()`: same, but for trigrams.
- `fourgrams_check()`: same, but for four-grams.
- `find_divisors()`: from a of repetition distances, extracts the divisors of each distance and stores the data on an array where the index is the divisor, and the value is the numbers of time said divisor has appeared.
- `manage_divisors()`: TODO
- `free_list`: TODO