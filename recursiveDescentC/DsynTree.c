// D. Resler 2/24

#include <stdlib.h>
#include <string.h>

#include "synTree.h"
#include "pretty.h"

struct DsynTreeType {
  bsynTree btree; // if NULL, D -> epsilon
  dsynTree dtree;
};

dsynTree createDsynTree(bsynTree bst,dsynTree dsTree) {
  dsynTree dst = malloc(sizeof(struct DsynTreeType));
  dst->btree = bst; dst->dtree = dsTree;
  return dst;
}

char *DsynTreeToString(dsynTree dst) {
  char *s = malloc(1000);
  strcpy(s,spaces());
  strcat(s,"D(\n");
  if(dst->btree != NULL) {
    indent();
    strcat(s,BsynTreeToString(dst->btree));
    strcat(s,DsynTreeToString(dst->dtree));
  } else {
    indent(); strcat(s,spaces());
    strcat(s,"[empty]\n");
  }
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}
