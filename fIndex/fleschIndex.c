#include "fleschIndex.h"

//Prints the data to the console
void outputFormattedFleschScores(int syllables, int words,
int fleshIndex, int sentenceCount){
  printf("Flesch Index = %d\n", fleshIndex);
  printf("Syllable Index = %d\n", syllables);
  printf("Word Index = %d\n", words);
  printf("Sentence Index = %d\n", sentenceCount);
}

int calculateFleschIndex(int syllables, int words, int sentences){
  float local = 206.835 - 84.6 * ( syllables / words ) - 1.015 * (words / sentences);
  int score;
  if(local - (int)local > 0.50){ //take away all value except the decimal and compare
    score = (int)local + 1;
  }
  else{  //less then half doesnt require rounding up
    score = (int)local;
  }

  return score; //returns rounded and calcuated score
}


int findSentences(char * contents){
  int sentences = 0;
  int endSent = 0;

  for(int i = 0; i < strlen(contents);i++){
    if(contents[i] == '.'|| //search for sentence ending chars
       contents[i] == ';'||
       contents[i] == ':'||
       contents[i] == '?'||
       contents[i] == '!'){
      endSent++; //add to the amount of concurent sentence ending chars
    }else{
      endSent = 0; //reset amount of concurent ending chars
    }
    if(endSent == 1){
      sentences++; //add to sentences for a single group of ending chars
    }
  }
  //printf("%d\n",sentences );
  return sentences;
}

int findSyllables(char * contents){
  int syllables = 0;
  int syllable = 0;
  int vowel = 0;
  int local[strlen(contents)];

  for(int i = 0; i < strlen(contents); i++){ //break down into words
    if(contents[i] == ' '||                  //non-words are 0, words are 1
       contents[i] == ':'||
       contents[i] == ';'||
       contents[i] == '?'||
       contents[i] == ','||
       contents[i] == '.'||
       contents[i] == '!'){
         local[i] = 0;
       }else
       {
         local[i] = 1;
       }
  }


  for(int i = 0; i < strlen(contents); i++){ //Look for vowels
    if(contents[i] == 'a' ||contents[i] == 'A' ||
       contents[i] == 'e' ||contents[i] == 'E' ||
       contents[i] == 'i' ||contents[i] == 'I' ||
       contents[i] == 'o' ||contents[i] == 'O' ||
       contents[i] == 'u' ||contents[i] == 'U' ||
       contents[i] == 'y' ||contents[i] == 'Y'){
         vowel++; //add for a vowel
       }
       else{
         vowel = 0; //reset vowels to zero when a break occours out of vowel
       }
       if(vowel == 1){
         if(contents[i] == 'e' && local[i+1] == 0){
           //dont allow for vowel if e at end of sentence
         }
         else{
           syllable++; //add for a syllable
      //     printf("HERE %d\n",i );
         }
       }
       if(local[i] == 0){
         if(i >= 1 && local[i-1] == 1 && syllable == 0){
           syllable = 1; //no exsiting vowel syllable, add for a single anyways
    //       printf("THERE %d\n",i );
         }
         syllables += syllable;
         syllable = 0;
       }

  }
  //printf("SYLLAHBLES %d\n", syllables);
  return syllables;


}



int findWords(char * contents){
int words = 0;

  for(int i = 0; i < strlen(contents)-1; i++){ //look ahead for white space
    if((contents[i] != ' '&&                  // and other word breaks
       contents[i] != ':'&&
       contents[i] != ';'&&
       contents[i] != '?'&&
       contents[i] != ','&&
       contents[i] != '.'&&
       contents[i] != '!')
     &&
     (contents[i+1] == ' '||
        contents[i+1] == ':'||
        contents[i+1] == ';'||
        contents[i+1] == '?'||
        contents[i+1] == ','||
        contents[i+1] == '.'||
        contents[i+1] == '!')
   ){
     //printf("%c ",contents[i-1] );
     //printf("%c ",contents[i] );
     //printf("%c ",contents[i+1] );
     //printf("%d\n",i );
     words++; //add amount of words baised on previous conditions
   }
  }

  if(contents[strlen(contents)-1] != ' '&&
     contents[strlen(contents)-1] != ':'&&
     contents[strlen(contents)-1] != ';'&&
     contents[strlen(contents)-1] != '?'&&
     contents[strlen(contents)-1] != '!'){
       words++; // add word baised on end case
     }
  return words;
}

void removeEndLine(char * contents){
  for(int i = 0; i < strlen(contents);i++ ){
    if(contents[i] == '\n'){ //just replaces endline with a space
      contents[i] = ' ';
    }
  }
}


char * readFile ( char * filename){
  char * buffer; //buffer for fileContents
  long length;
  FILE *inFile;

  inFile = fopen(filename, "r"); //open file
  if(inFile == NULL){ //this if file opening fales
    printf("Failed to open file");
    printf(" %s not found in file location\n",filename);
    return NULL;
  }
  else{ //File is found
    fseek(inFile,0,SEEK_END); //go to end of file
    length = ftell(inFile); //lenght of chars in text file
    fseek(inFile,0,SEEK_SET);
    buffer = (char*)malloc(length+1); //allocate for stirng and end extra for null
    if(buffer){
      fread(buffer, 1, length, inFile); //read the file
    }
    fclose(inFile);
  }
  //printf("Length %d\n",length );
  buffer[length] = '\0'; //End the string in a NULL
  //printf("%c\n",buffer[44] );
  //printf("%s BROKEN BIT\n",buffer );
  return buffer;
}
