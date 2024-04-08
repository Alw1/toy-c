/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/pretty.h"
#include "../include/TCscanner.h"
#include "../include/TCtokens.h"
#include "../include/TCparser.h"
#include "../include/TCglobals.h"
#include "../include/ASprogram.h"
#include "../include/ASexpressions.h"
#include "../include/ASdefinitions.h"
#include "../include/ASstatements.h"

struct ProgramST_t {
  DefinitionST def_tree[1000];
  int index;
};

ProgramST createProgramST(void) {
  ProgramST ast = malloc(sizeof(struct ProgramST_t));
  ast->index = 0;
  return ast;
}

char *ProgramST_ToString(ProgramST ast) {
  char *s = malloc(1000); 
  strcpy(s,spaces());
  strcat(s,"Program(\n");
  indent();
  for(int x=0;x<ast->index;x++)
  {
    strcat(s,spaces()); strcat(s,DefinitionST_ToString(ast->def_tree[x]));
  }
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

void addDefinition(ProgramST ast, DefinitionST def){
     ast->def_tree[ast->index++] = def;
}

char *generateProgramCode(ProgramST st){
    for(int x=0;x<st->index;x++)
      generateDefinitionCode(st->def_tree[x]);

    return "NOTHING YET";
}

