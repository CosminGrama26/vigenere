#ifndef ANALYSIS_H
#define ANALYSIS_H

#define ALPHABET 26

char* frequency_analysis(char* text, int kl);
char** split_text(char* text, int p);
char analyze(char* text, const float target_alphabet[ALPHABET]);

#endif