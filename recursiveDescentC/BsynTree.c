// // D. Resler 2/24

// #include <stdlib.h>
// #include <string.h>
// #include "pretty.h"

// #include "synTree.h"
// static void DEBUGprintProd(enum prod);

// // enum prod { ID,C,B,epsilon };
// struct BsynTreeType {
//    enum prod type;
//    union {
//      char id;
//      csynTree ctree;
//      bsynTree btree;
//    };
// };

// bsynTree createBsynTree(enum prod t,void* tree) {
//   bsynTree bst = malloc(sizeof(struct BsynTreeType));
//   bst->type = t;
//   switch(t) {
//   case ID: bst->id = 'x'; break;
//   case Cprod:  bst->ctree = (csynTree)tree; break;
//   case Bprod:  bst->btree = (bsynTree)tree; break;
//   case epsilon: break;
//   default:
//     printf("internal error\n");
//     exit(EXIT_FAILURE);
//   }
//   return bst;
// }

// char *BsynTreeToString(bsynTree bst) {
//   char *s = malloc(500);
//   strcpy(s,spaces());
//   strcat(s,"B(\n");
//   indent();
//   switch(bst->type) {
//   case ID:
//     strcat(s,spaces());    
//     strcat(s,"x\n");
//     break;
//   case Cprod:   strcat(s,CsynTreeToString(bst->ctree)); break;
//   case Bprod:   strcat(s,BsynTreeToString(bst->btree)); break;
//   case epsilon:
//     strcat(s,spaces());        
//     strcat(s,"[empty]\n"); 
//     break;
//   default:      strcat(s,"[error]\n"); break;       
//   }
//   outdent(); strcat(s,spaces());
//   strcat(s,")\n");
//   return s;
// }

// static void DEBUGprintProd(enum prod p){
//   char *s = malloc(10);
//   switch(p) {
//   case ID:      strcpy(s,"ID");    break;
//   case Cprod:   strcpy(s,"Cprod"); break;
//   case Bprod:   strcpy(s,"Bprod"); break;
//   case epsilon: strcpy(s,"epsilon"); break;
//   default:      strcpy(s,"[error]"); break;
//   }
//   printf("[DEBUG] prod = %s\n",s);
// }

