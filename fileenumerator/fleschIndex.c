#include "fleschIndex.h"

/******
 readFile: file opening attempted, if failed returns NULL, otherwise file pointer returned
 In: char * fileName
 Out: char * fileContents
 Post: NULL or contents of txt file returned
 *******/
char *readFile (char * fileName) 
{
    char * fileContents;
    int memoryNeeded;
    int i = 0;
    char buffer;
    
    FILE * fp = fopen(fileName, "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return (NULL);
    }
    
    fseek(fp, 0, SEEK_END);
    memoryNeeded = ftell(fp);
    
    fileContents = malloc (sizeof (char) * memoryNeeded);
    
    fseek(fp, 0, SEEK_SET);
    
    while((buffer = fgetc(fp)) != EOF)
    {
        if(buffer == '\n')
        {
            buffer = ' ';
        }
        fileContents[i++] = buffer;   
    }
    fileContents[i] = '\0';
    
    return fileContents;
}

/******
 findSyllables: counts all syllables in each word. groups of adjacent vowels counts as 1, 'e' at the ends of words does not count, words must have minimum 1 syllable
 In: char * string
 Out: int syllableCount
 Post: the total number of syllables of the words in the string is found and returned
 *******/
int findSyllables(char * string)
{
    char vowel [12]= {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
    int syllableCount = 0;
    int currentSyllables = 0;
    int consecutiveVowel;
    int foundVowel;
    
    for (int g = 0; g<strlen(string); g++)
    {
        consecutiveVowel = 0;
        foundVowel = 0;
        for (int p = 0; p < strlen(vowel); p++)
        {
            if (string[g + 1] == vowel [p])
            {
                consecutiveVowel = 1;
            }
            if (string[g] == vowel [p])
            {
                foundVowel = 1;
            }
        }
        
        if (consecutiveVowel == 0 && foundVowel == 1)
        {
            if(string[g] == 'e' && !isalpha(string[g+1]))
            {    
            }
            else{
                currentSyllables++;
            }
        }
        
        if((string[g]==' ' && string[g+1]!=' ') || string[g]=='\0' || string[g]== '\n')
        {    
            if(currentSyllables == 0){
                currentSyllables = 1;
            }
            syllableCount += currentSyllables;
            currentSyllables = 0;
        }
    }
    return syllableCount;
}

/******
 findWords: counts the number of words in a string. Words are characters delimited by white space or the end of a sentence
 In: char * string
 Out: int wordCount
 Post: the total number of words in the string is returned
 *******/
int findWords(char * string)
{
    int wordCount = 0;
    for (int g = 0; g<strlen(string); g++)
    {
        if((string[g]==' ' && string[g+1]!=' ') || string[g]=='\0')
        {    
            wordCount ++;
        }
    }
    return wordCount;
}

/******
 findWords: counts the number of sentences in a string. sentences are groups of words terminated by '.', ':', ';', '?', '!' (multiples are treated as end of single sentence)
 In: char * string
 Out: int sentenceCount
 Post: the total number of sentences in the string is returned
 *******/
int findSentences(char * string)
{
    char punctuation [5]= {'.', ':', ';', '?', '!'};
    int sentenceCount = 0;
    int consecutivePunct;
    int foundPunct;
    for (int g = 0; g<strlen(string); g++)
    {
        consecutivePunct = 0;
        foundPunct = 0;
        for (int p = 0; p < strlen(punctuation); p++)
        {
            if (string[g + 1] == punctuation [p])
            {
                consecutivePunct = 1;
            }
            if (string[g] == punctuation [p])
            {
                foundPunct = 1;
            }
        }
        if (consecutivePunct == 0 && foundPunct == 1)
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}

/******
 calculateFleschIndex: calculates the flesch index number based on syllables, words, and sentences in the string
 In: int syllables, int words, int sentences
 Out: int index
 Post: the index is calculated and returned as a rounded integer
 *******/
int calculateFleschIndex(int syllables, int words, int sentences)
{
    float index;
    index = 206.835 - (84.6 * (syllables/words)) - (1.015 * (words/sentences));
    return round(index);
}

/******
 outputFormattedFleschScores: outputs the flesch index, syllables, words, and sentence count of a string
 In: int syllables, int words, int fleshIndex, int sentenceCount
 Out: void
 Post: All parameters are printed in proper formatting
 *******/
void outputFormattedFleschScores(int syllables, int words, int fleshIndex, int sentenceCount)
{
    printf("Flesch Index = %d\n", fleshIndex);
    printf("Syllable Count = %d\n", syllables);
    printf("Word Count = %d\n", words);
    printf("Sentence Count = %d\n", sentenceCount);
}
