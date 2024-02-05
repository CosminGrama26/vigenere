# VIGENERE CIPHER
## Video Demo:  <URL HERE>
## Description:
This C program is designed to encryp and decrypt a text, using the Vigenère polyalphabetic cipher. Additionally, it can also break an encrypt text without knoweledge of the key, by applying cryptanalysis.

### Project Components

The project is composed of multiple files:

- `encrypt.c`: Main file, takes and verifies user input, encrypt and decrypts text with a key, or calls the `break_cypher` in `break.c`;
- `break.c`: Finds the lenght of the key by finding repetitions of characters in the text and calculating the most common divisors of the distances of the aformentioned repetitions. This procedure is known as "Kasiski examination". <https://en.wikipedia.org/wiki/Kasiski_examination>;
- `analysis.c`: Splits the text in as many part as the length of the key, perfors a frequency analysis on each subtext and prints the key used to encrypt the text;
- `break.h`: Header file for `break.c`;
- `analysis.h`: Header file for `analysis.c`;
- `Makefile`: Makefile for compilation with gcc.

#### Encrypt.c

