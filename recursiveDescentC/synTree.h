// D. Resler 2/24

#include <stdio.h>

#ifndef SYNTREE
#define SYNTREE

typedef struct AsynTreeType *asynTree;
typedef struct BsynTreeType *bsynTree;
typedef struct CsynTreeType *csynTree;
typedef struct DsynTreeType *dsynTree;

enum prod { ID,Cprod,Bprod,epsilon }; // for production B

asynTree createAsynTree(bsynTree);
bsynTree createBsynTree(enum prod,void*);
csynTree createCsynTree(bsynTree,dsynTree);
dsynTree createDsynTree(bsynTree,dsynTree);

char *AsynTreeToString(asynTree);
char *BsynTreeToString(bsynTree);
char *CsynTreeToString(csynTree);
char *DsynTreeToString(dsynTree);

#endif

