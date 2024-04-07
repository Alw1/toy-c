// D. Resler 2/24

#include <stdlib.h>
#include <string.h>

#include "synTree.h"
#include "pretty.h"

struct CsynTreeType {
  bsynTree btree;
  dsynTree dtree;
};

csynTree createCsynTree(bsynTree bst,dsynTree dst) {
  csynTree cst = malloc(sizeof(struct CsynTreeType));
  cst->btree = bst; cst->dtree = dst;
  return cst;
}

char *CsynTreeToString(csynTree cst) {
  char *s = malloc(500);
  strcpy(s,spaces());
  strcat(s,"C(\n");
  indent();
  strcat(s,BsynTreeToString(cst->btree));
  strcat(s,DsynTreeToString(cst->dtree));
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}
