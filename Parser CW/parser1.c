#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char input;
    char *output;
} rule;

typedef struct {
    char *terminals;
    char *nonTerminals;
    rule *rules;
} grammar;

int randomNumber(int maxNum);
void parseTree(int height);
void printLayer(char **layer);
char **moveDownLayer(char **layer);
char **handleBranch(char *branch);
char *continueBranch(char *branch, int i);


grammar myGrammar();

int main(int argc, char** argv){

  //char* word = &argv;
  //int wordLength = argc;
  char* word = "xyx";
  int wordLength = 3;
  int treeHeight = (2 * wordLength) - 1;

  parseTree(treeHeight);

  //printf("%s %c\n", myGrammar.rules[7].output, myGrammar.nonTerminals[3]);

  return 0;

}

void parseTree(int height) {

  char ** oldLayer = malloc(100 * sizeof(char*));
  for (int i =0 ; i < 10; ++i) {
      oldLayer[i] = malloc(100 * sizeof(char));
  }

  oldLayer[0] = "S";

  for (int layer = 1; layer <= height; layer++) {
    printLayer(oldLayer);
    oldLayer = moveDownLayer(oldLayer);

  }

}

char **moveDownLayer(char **layer) {

  char ** newLayer = malloc(100 * sizeof(char*));
  for (int i =0 ; i < 100; ++i) {
      newLayer[i] = malloc(100 * sizeof(char));
  }

  int progressInLayerCounter = 0;

  for (int i = 0; i < sizeof(layer)/sizeof(layer[0]); i++) {

    printf("%d\n", i);

    char ** newBranches = malloc(100 * sizeof(char*));
    for (int j =0 ; j < 100; ++j) {
        newBranches[j] = malloc(100 * sizeof(char));
    }

    newBranches = handleBranch(layer[i]);

    for(int j = 0; j < sizeof(newBranches)/sizeof(newBranches[0]); j++) {
      newLayer[progressInLayerCounter + j] = newBranches[j];
    }

    progressInLayerCounter = progressInLayerCounter + sizeof(newBranches)/sizeof(newBranches[0]);

  }

  return newLayer;
}

char **handleBranch(char *branch) {

  char ** newBranches = malloc(100 * sizeof(char*));
  for (int j =0 ; j < 100; ++j) {
      newBranches[j] = malloc(100 * sizeof(char));
  }

  int newBranchCnt = 0;
  for (int i = 0; i < strlen(branch); i++) {
    char *newBranch = continueBranch(branch, i);
    if (strlen(newBranch)) {
      newBranches[newBranchCnt] = newBranch;
      newBranchCnt++;
    }
  }

  return newBranches;
}

char *continueBranch(char *branch, int i) {
  return "TT";
}

void printLayer(char **layer) {
  for (int i = 0; i < sizeof(layer)/sizeof(layer[0]); i++) {
    printf("%s ", layer[i]);
  }
  printf("\n");
}

grammar myGrammar() {

  char *nonTerminals = "SETFZYXVUQP";
  char *terminals = "()+*x";

  rule rule1 = {.input = 'S', .output = "EZ"};
  rule rule2 = {.input = 'S', .output = "TY"};
  rule rule3 = {.input = 'S', .output = "VX"};
  rule rule4 = {.input = 'S', .output = "x"};
  rule rule5 = {.input = 'E', .output = "EZ"};
  rule rule6 = {.input = 'E', .output = "TY"};
  rule rule7 = {.input = 'E', .output = "VX"};
  rule rule8 = {.input = 'E', .output = "x"};
  rule rule9 = {.input = 'T', .output = "TY"};
  rule rule10 = {.input = 'T', .output = "VX"};
  rule rule11 = {.input = 'T', .output = "x"};
  rule rule12 = {.input = 'F', .output = "VX"};
  rule rule13 = {.input = 'F', .output = "x"};
  rule rule14 = {.input = 'Z', .output = "UT"};
  rule rule15 = {.input = 'Y', .output = "QF"};
  rule rule16 = {.input = 'X', .output = "EP"};
  rule rule17 = {.input = 'V', .output = "("};
  rule rule18 = {.input = 'U', .output = "+"};
  rule rule19 = {.input = 'Q', .output = "*"};
  rule rule20 = {.input = 'P', .output = ")"};

  rule rules[20] = {rule1,
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
    rule12,
    rule13,
    rule14,
    rule15,
    rule16,
    rule17,
    rule18,
    rule19,
    rule20,
  };

  grammar myGrammar = {.terminals = terminals, .nonTerminals = nonTerminals, .rules = rules};

  return myGrammar;

}
