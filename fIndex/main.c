#include "fleschIndex.h"



int main(int argc, char *argv[]){
  char *fileContents;
  int lenght;
  int words;
  int syllables;
  int sentences;
  int index;
  //fileContents = (char*)malloc(sizeof(char)*str        len(re   adFile(argv[1])));
  //printf("Lost of text" );
  //printf("%s\n",argv[1] );

  lenght = strlen(readFile(argv[1])); //Get file info
  fileContents = (char*) malloc(lenght+1);
  strcpy(fileContents,readFile(argv[1]));
  fileContents[lenght] = '\0';


  removeEndLine(fileContents);
  words = findWords(fileContents);
  syllables = findSyllables(fileContents);
  sentences = findSentences(fileContents);
  index = calculateFleschIndex(syllables,words,sentences);
  outputFormattedFleschScores(syllables,  words,
   index,  sentences);
  //printf("WORDS %d\n",words );
  //  printf("SYLLABES %d\n", syllables);
  //printf("sentences %d\n",sentences );

  //printf("INDEX %d\n",calculateFleschIndex(syllables, words,sentences));
  //printf(" %d\n",lenght );
  //printf("%s\n",fileContents);
  //  printf("WORD         S%d\n",findWords(fileContents));
  //readFile(argv[1]);
  return 0;
}
