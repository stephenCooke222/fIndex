#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



char * readFile ( char * filename);
void removeEndLine(char * contents);
int findWords(char * contents);
int findSyllables(char * contents);
int findSentences(char * contents);
int calculateFleschIndex(int syllables, int words, int sentences);
void outputFormattedFleschScores(int syllables, int words,
int fleshIndex, int sentenceCount);

#endif
