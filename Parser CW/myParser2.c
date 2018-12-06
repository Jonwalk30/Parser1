#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum { false, true } bool;

typedef struct {
    char input;
    char *outputs[8];
} rule;

typedef struct {
    char *terminals;
    char *nonTerminals;
    rule *rules;
} grammar;



void parseTree(char *word);
int sizeOfArray(char **array);
void printTable(char ***table, int wordLength);
grammar myGrammar();

int main(int argc, char** argv){

  //char* word = argv[1];
  char* word = "x+x";

  parseTree(word);

  //printf("%s %c\n", myGrammar.rules[7].output, myGrammar.nonTerminals[3]);

  return 0;

}

void parseTree(char *word) {

  int wordLength = strlen(word);
  
  char ***table = malloc(wordLength * wordLength * sizeof(char*));
  for (int i = 0; i < wordLength; i++) {
        table[i] = malloc(wordLength * sizeof(char*));
        for (int j = 0; j < wordLength; j++) {
            table[i][j] = malloc(sizeof(char*));
        }
    }

  // Subwords of length 1 for initial table
  for (int i = 0; i < wordLength; i++) {
    char* subword = malloc(1*sizeof(char));
    strncpy(subword, word+i, 1);
    //printf("%s\n", subword);

    for (int NT = 0; NT < 11; NT++) {
      for (int T = 0; T < sizeOfArray(myGrammar().rules[NT].outputs); T++) {
        if (!strcmp(myGrammar().rules[NT].outputs[T], subword)) {
          //printf("WOO\n");
          char tempString[2];
		  tempString[0] = myGrammar().rules[NT].input;
		  tempString[1] = '\0';
          strcat(table[i][i], tempString);
          //printf("Added %s\n",table[sw][sw]);
        }
      }
    }
  }
  
  //printTable(table, wordLength);

  // Subwords of length 2 for creating parse tree
  for (int l = 2; l <= wordLength; l++) {
    //printf("Dealing with subwords of length %d\n", i);

    // For each subword
    for (int i = 0; i < wordLength - (l-1); i++) {
      int j = i + (l-1);
      //printf("l=%d sw=%d j=%d\n", l, sw, j);
      
      // For each letter in that subword
      for (int k = i; k < j; k++) {
        //printf("l=%d i=%d j=%d k=%d\n", l, i, j, k);
        char* subword = malloc(l*sizeof(char));
        strncpy(subword, word+i, l);
        //printf("Subword: %s\n", subword);
        // For every input
        for (int NT = 0; NT < 11; NT++) {
            // For every output
            for (int T = 0; T < sizeOfArray(myGrammar().rules[NT].outputs); T++) {
                // For every part of the output
                bool containsAll = true; 
                
                if (strlen(myGrammar().rules[NT].outputs[T]) > 1) {
                    printf("Word: %s Letter: %c Contains?: %d\n", table[i][k], myGrammar().rules[NT].outputs[T][0], strchr(table[i][k], myGrammar().rules[NT].outputs[T][0]) != NULL);
                    printf("and Word: %s Letter: %c Contains?: %d\n", table[k+1][j], myGrammar().rules[NT].outputs[T][1], strchr(table[k+1][j], myGrammar().rules[NT].outputs[T][1]) != NULL);
                    if (strchr(table[i][k], myGrammar().rules[NT].outputs[T][0]) != NULL &&
                        strchr(table[k+1][j], myGrammar().rules[NT].outputs[T][1]) != NULL) {
                        //printf("Got in here\n");
                      char tempString[2];
            		  tempString[0] = myGrammar().rules[NT].input;
            		  tempString[1] = '\0';
            		  printf("Putting %s in\n", tempString);
                      strcat(table[i][j], tempString);
                      //printf("Cell now looks like %s\n", table[i][j]);
                    }
                }
             }
        }
      }
      //printf("%s\n", subword);
    }
  }
  if (strchr(table[0][wordLength-1], 'S')) {
     printf("Word is accepted:\n\n");
     printTable(table, wordLength);
  } else {
      printf("Word is rejected.\n");
  }

}

int sizeOfArray(char **array) {
  int i = 0;
  while(array[i] != NULL) {
    i++;
  }
  return i;
}

void printTable(char ***table, int wordLength) {

    for (int i = 0; i < wordLength; i++) {
        for (int j = 0; j < wordLength; j++) {
            if (strcmp(table[i][j], "")) {
                printf("%s       ", table[i][j]);
            } else {
                printf("         ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

grammar myGrammar() {

  char *nonTerminals = "SETFZYXVUQP";
  char *terminals = "()+*x";

  rule rule1 = {.input = 'S', .outputs = {"EZ", "TY", "VX", "x"}};
  rule rule2 = {.input = 'E', .outputs = {"EZ", "TY", "VX", "x"}};
  rule rule3 = {.input = 'T', .outputs = {"TY","VX", "x"}};
  rule rule4 = {.input = 'F', .outputs = {"VX", "x"}};
  rule rule5 = {.input = 'Z', .outputs = {"UT"}};
  rule rule6 = {.input = 'Y', .outputs = {"QF"}};
  rule rule7 = {.input = 'X', .outputs = {"EP"}};
  rule rule8 = {.input = 'V', .outputs = {"("}};
  rule rule9 = {.input = 'U', .outputs = {"+"}};
  rule rule10 = {.input = 'Q', .outputs = {"*"}};
  rule rule11 = {.input = 'P', .outputs = {")"}};
  rule rule12 = {.input = 'a', .outputs = {"b"}};
  //rule rule13 = {.input = 'c', .outputs = {"d"}};

  rule rules[12] = {rule1,
    rule2,
    rule3,
    rule4,
    rule5,
    rule6,
    rule7,
    rule8,
    rule9,
    rule10,
    rule11,
    rule12
    //,
    //rule13
  };

  grammar myGrammar = {.terminals = terminals, .nonTerminals = nonTerminals, .rules = rules};

  return myGrammar;

}
