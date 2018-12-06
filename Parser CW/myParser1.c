#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int sizeOfArray(char **array);
char ** parseTree(char **tree, int height, int wordLength, bool printTree);
char ** nextTree(char **tree);
void printArray(char **array, int height, int wordLength);
char ** outputOf(char input);
int getNewTreeSize(char **tree);
char ** generateNodesFor(char *node);
grammar myGrammar();

int main(int argc, char** argv){

  char* word = argv[1];
  int wordLength = strlen(word);
  int treeHeight = (2 * wordLength) - 1;

  char *tree0[100] = {"->S", NULL};
  
 char **tree = parseTree(tree0, treeHeight, wordLength, true);
 bool acceptWord = false;
  //printf("here\n");
  for (int i = 0; i < sizeOfArray(tree); i++) {
      //printf("node: %s\n", tree[i]);
      if (tree[i] != NULL) {
          //printf("%ld\n", strlen(tree[i]));
          if (strlen(tree[i])) {
               char *subnode = malloc(sizeof(char*));
                subnode = strrchr(tree[i], '>') + 1;
                if (subnode != NULL) {
                    if (!strcmp(subnode, word)) {
        			 acceptWord = true;
        			 printf("\nWord is accepted:\n\n");
        			 printf("%s\n\n\n", tree[i]);
        			 return 1;
                  }
            }
	     }
      }
   }
   printf("\nWord is rejected.\n");
//   printf("here\n");
//   if (acceptWord) {
// 	   printf("\nWord is accepted:\n\n");
// 		printArray(tree0, treeHeight, wordLength);
// 	    parseTree(tree0, treeHeight, wordLength, true);
//   } else {
// 	   printf("\nWord is rejected.\n");
//   }

  return 0;

}

 char ** parseTree(char **tree, int height, int wordLength, bool printTree) {
   // Get the next tree
   
   //printf("***TREE***\n");
   //printArray(tree, 1, 1);
   //printf("***\n");
   //printf("   \n");
   char **newTree = nextTree(tree);
   //printf("really after\n");
   // Remove duplicates
   for (int i = 0; i < sizeOfArray(newTree); i++) {
       for (int j = 0; j < sizeOfArray(newTree); j++) {
           //printf("Comparing %s at %d to %s at %d with result %d\n", newTree[i], i, newTree[j], j, strcmp(newTree[i], newTree[j]));
           if (newTree[i] != NULL && newTree[j] != NULL) {
               if (strlen(newTree[i]) > 0 && strlen(newTree[j]) > 0)
               if (!strcmp(newTree[i], newTree[j]) && i != j) {
               //printf("Removing the latter\n");
                 newTree[j] = "";
           }
           }
       }
   }
   
  if (height > 1) {
    height--;
    // Print it
   if (printTree) {
 	   printArray(newTree, height, wordLength);
   }
   //printf("***NEWTREE***\n");
   //printArray(newTree, 1, 1);
   //printf("***\n");
   
   // Remove words that are too long
   for (int i = 0; i < sizeOfArray(newTree); i++) {
       //printf("Hello\n");
       //printf("node= %s\n", newTree[i]);
       if (newTree[i] != NULL) {
            if (strlen(newTree[i]) > 0) {
                char *subnode = malloc(sizeof(char*));
                 subnode = strrchr(newTree[i], '>') + 1;
               if (strlen(subnode) > wordLength) {
                   newTree[i] = "";
               }
            }
       }
   }
    //printf("before\n");
    return parseTree(newTree, height, wordLength, printTree);
  }
   
   // Remove words that are too long
   for (int i = 0; i < sizeOfArray(newTree); i++) {
       //printf("Hello\n");
       //printf("node= %s\n", newTree[i]);
       if (newTree[i] != NULL) {
            if (strlen(newTree[i]) > 0) {
                char *subnode = malloc(sizeof(char*));
                 subnode = strrchr(newTree[i], '>') + 1;
               if (strlen(subnode) > wordLength) {
                   newTree[i] = "";
               }
            }
       }
   }
   //height--;
   // Print it
//   if (printTree) {
 	   printArray(newTree, height, wordLength);
//   }

   
  return newTree;
}

char ** nextTree(char **tree) {
    
  int newTreeSize = getNewTreeSize(tree);

  char ** newTree = malloc((newTreeSize + 1) * 100 * sizeof(char*));
  
  int k = 0;
  // For each node on the tree
  for (int i = 0; i < sizeOfArray(tree); i++) {
    char *node = tree[i];
    char **newNodes;
    if (node != NULL) {
        if (strlen(node) > 0) {
            newNodes = generateNodesFor(node);   
        }
    }
    
    //printf("Size = %d\n", sizeOfArray(newNodes));
    
    // For each output that that node generates
    for(int j = 0; j < sizeOfArray(newNodes); j++) {
      // Add to the new tree
      newTree[k] = newNodes[j];
      k++;
    }
  }
  newTree[k] = NULL;
  return newTree;
}

char ** generateNodesFor(char *node) {

  char *subnode = malloc(sizeof(char*));
  subnode = strrchr(node, '>') + 1;
  int newNodeSize = 0;
  for (int j = 0; j < strlen(subnode); j++) {
	  if (outputOf(subnode[j]) != NULL) {
		  newNodeSize = newNodeSize + sizeOfArray(outputOf(subnode[j]));
	  }
  }
  //printf("Number of nodes: %d\n", newNodeSize);
  char **newNodes = malloc((newNodeSize) * sizeof(char*));

  char activeChar;
  char **output;
  int l = 0;
  //Get the position of the last ->
    //printf("section: %s of node: %s\n", subnode, node);
  for(int i = 0; i < strlen(subnode); i++) {
    activeChar = subnode[i];
    output = outputOf(activeChar);
    //printf("%d For letter %c in node %s Got an output\n",i, node[i], node);
    //printf("%d\n", activeChar == 'P');
	if (output != NULL) {
	    
	  for (int j = 0; j < sizeOfArray(output); j++) {
		  //printf("Dealing with %s\n", output[j]);
		  char *newNode = malloc(100*sizeof(char));
		  //printf("Appending %s to %s\n", node, newNode);
		  strcpy(newNode,node);
		  strcat(newNode,"->");
		  //printf("Old node looks like %s\n", newNode);
		  for(int k = 0; k < strlen(subnode); k++) {
		      //printf("Adding the item related to %c\n", subnode[k]);
			if (i == k) {
			  strcat(newNode,output[j]);
			} else {
			  char tempString[2];
			  tempString[0] = subnode[k];
			  tempString[1] = '\0';
			  strcat(newNode,tempString);
			}
			//printf("New node currently looks like %s\n", newNode);
		  }
		  //printf("New node looks like %s\n", newNode);
		  newNodes[l] = newNode;
		  l++;
		}
	}
	newNodes[l] = NULL;
  }
  return newNodes;
}

int getNewTreeSize(char **tree) {
  int newTreeSize = 0;
  for (int i = 0; i < sizeOfArray(tree); i++) {
    char *node = tree[i];
    for (int j = 0; j < strlen(node); j++) {
	  if (outputOf(node[j]) != NULL) {
		  newTreeSize = newTreeSize + sizeOfArray(outputOf(node[j]));
	  }
    }
  }
  return newTreeSize;
}

int sizeOfArray(char **array) {
  int i = 0;
  if (array == NULL) {
      return 0;
  }
  while(array[i] != NULL) {
    i++;
  }
  return i;
}

void printArray(char **array, int height, int wordLength) {
    
  for (int i = 0; i < sizeOfArray(array); i++) {
    if (i == sizeOfArray(array) - 1) {
      printf("%s", array[i]);
    } else {
        if (strlen(array[i]) > 0) {
            printf("%s \n", array[i]);
        }
    }
  }
  printf("\n");
  printf("\n");
}

char ** outputOf(char input) {
    
  //grammar g = myGrammar();
    
  for (int i = 0; i < 11; i++) {
    if (input == myGrammar().rules[i].input) {
      return myGrammar().rules[i].outputs;
    }
  }
  return NULL;
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
