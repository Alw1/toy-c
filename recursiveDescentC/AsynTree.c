// D. Resler 2/24

#include <stdlib.h>
#include <string.h>

#include "synTree.h"
#include "pretty.h"

struct AsynTreeType {
  bsynTree btree;
};

asynTree createAsynTree(bsynTree bst) {
  asynTree ast = malloc(sizeof(struct AsynTreeType));
  ast->btree = bst;
  return ast;
}

char *AsynTreeToString(asynTree ast) {
  char *s = malloc(1000); 
  strcpy(s,spaces());
  strcat(s,"A(\n");
  indent();
  strcat(s,BsynTreeToString(ast->btree));
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}
