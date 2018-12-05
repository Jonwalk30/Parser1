#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char input;
    char *outputs[8];
} rule;

typedef struct {
    char *terminals;
    char *nonTerminals;
    rule *rules;
} grammar;

int sizeOfArray(char **array);
char ** parseTree(char **tree, int height);
char ** nextTree(char **tree);
void printArray(char **array);
char ** outputOf(char input);
int getNewTreeSize(char **tree);
char ** generateNodesFor(char *node);
char * concat(char *a, char *b);
grammar myGrammar();

int main(int argc, char** argv){

  //char* word = &argv;
  //int wordLength = argc;
  char* word = "x+x";
  int wordLength = 3;
  int treeHeight = (2 * wordLength) - 1;

  char *tree0[100] = {"SSS", "TTT", NULL};

  printf("%s\n", tree0[0]);

  parseTree(tree0, treeHeight);

  return 0;

}

 char ** parseTree(char **tree, int height) {

   // Get the next tree
   char **newTree = nextTree(tree);

   // Print it
   printArray(newTree);

  if (height > 0) {
    height--;
    return parseTree(newTree, height);
  }
  return newTree;
}

char ** nextTree(char **tree) {

  int newTreeSize = getNewTreeSize(tree);

  char ** newTree = malloc(newTreeSize * sizeof(char*));

  int k = 0;
  // For each node on the tree
  for (int i = 0; i < sizeOfArray(tree); i++) {
    char *node = tree[i];
    char **newNodes = generateNodesFor(node);
    // For each output that that node generates
    for(int j = 0; j < sizeOfArray(newNodes); j++) {
      // Add to the new tree
      newTree[k] = newNodes[j];
      k++;
    }
  }
  // Generate the branches it produces
  // Append them to the next tree
  // Return the next tree
  return newTree;
}

char ** generateNodesFor(char *node) {

  int newNodeSize = 0;
  for (int j = 0; j < strlen(node); j++) {
    newNodeSize = newNodeSize + sizeOfArray(outputOf(node[j]));
  }
  char **newNodes = malloc(newNodeSize * sizeof(char*));

  char activeChar;
  char **output;
  int l = 0;
  for(int i = 0; i < strlen(node); i++) {
    activeChar = node[i];
    output = outputOf(activeChar);
    for (int j = 0; j < sizeOfArray(output); j++) {
      //printf("%d\n", j);
      //char *newNode =;
      //strcpy(newNode,"");
      //printf("%s\n", newNode);
      //printArray(output);

      //memcpy(newNodeP1, node, i);
      //printf("%s", newNodeP1);
      for(int k = 0; k < strlen(node); k++) {

        //printf("i=%d j=%d k=%d", i, j, k);
        //printf("%d\n", k);
        if (i == k) {
          //printf("Adding %s\n", output[j]);
          //newNode = strcat(newNode, output[j]);
          //newNode = "a";
          //concat(newNode, output[j]);
          //sprintf(newNode, "%s%s", newNode, output[j]);
          //strcat(newNode,output[j]);
          //printf("Added %s\n", output[j]);
        } else {
          //char tempString[2];
          //tempString[0] = node[k];
          //tempString[1] = '\0';
          //printf("Adding %s\n", tempString);
          //strcat(newNode,tempString);
          //newNode = strcat(newNode, tempString);
        }
      }
      //printf("%s\n", newNode);
      newNodes[l] = "a";//newNode;
      l++;
    }
  }
  return newNodes;
}

int getNewTreeSize(char **tree) {
  int newTreeSize = 0;
  for (int i = 0; i < sizeOfArray(tree); i++) {
    char *node = tree[i];
    for (int j = 0; j < strlen(node); j++) {
      newTreeSize = newTreeSize + sizeOfArray(outputOf(node[j]));
    }
  }
  //printf("%d\n", newTreeSize);
  return newTreeSize;
}

int sizeOfArray(char **array) {
  int i = 0;
  while(array[i] != NULL) {
    i++;
  }
  return i;
}

void printArray(char **array) {
  for (int i = 0; i < sizeOfArray(array); i++) {
    if (i == sizeOfArray(array) - 1) {
      printf("%s", array[i]);
    } else {
      printf("%s, ", array[i]);
    }
  }
  printf("\n");
}

char ** outputOf(char input) {
  for (int i = 0; i < 11; i++) {
    if (input == myGrammar().rules[i].input) {
      return myGrammar().rules[i].outputs;
    }
  }
  return NULL;
}

char * concat(char *a, char *b) {
  return "x";
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

  rule rules[11] = {rule1,
    rule2,
    rule3,
    rule4,
    rule5,
    rule6,
    rule7,
    rule8,
    rule9,
    rule10,
    rule11
  };

  grammar myGrammar = {.terminals = terminals, .nonTerminals = nonTerminals, .rules = rules};

  return myGrammar;

}
