/*
Author Name: James Bunker
Course: CIS*2500
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char * readFile ( char * filename);
int calculateFleschIndex(int syllables, int words, int sentences);
void outputFormattedFleschScores(int syllables, int words, int fleshIndex, int sentenceCount);
int findSyllables(char * string);
int findWords(char * string);
int findSentences(char * string);
