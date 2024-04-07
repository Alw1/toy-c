/*
    Created by Alex Wyatt Spring 2023
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
#include "../include/TCSymbols.h" 
#include "../include/ASprogram.h"
#include "../include/ASexpressions.h"
#include "../include/ASdefinitions.h"
#include "../include/ASstatements.h"

struct DefinitionST_t {
  enum definition_prods def_type;
  union {
     VarDefST VarDef_tree;
     FuncDefST FuncDef_tree;
   };
};

struct FuncDefST_t {
    SymTable sym_table;
    Token id;
    Token type;
    VarDefST vardef_tree[1000];
    int vardef_index;
    BlockStateST block_state;
};

struct VarDefST_t {
    Token id[1000];
    int id_index;
    Token type;
};

DefinitionST createDefinitionST(enum definition_prods type, void *tree) {
  DefinitionST ast = malloc(sizeof(struct DefinitionST_t));
  ast->def_type = type;
  switch(type) {
  case FuncDef:  ast->FuncDef_tree = (FuncDefST)tree; break;
  case VarDef:   ast->VarDef_tree = (VarDefST)tree; break;
  default:
    printf("internal error in createDefinitionST()\n");
    exit(EXIT_FAILURE);
  }
  return ast;
}

FuncDefST createFuncDefST(Token type, Token id){
    FuncDefST ast = malloc(sizeof(struct FuncDefST_t));
    ast->id = id;
    ast->type = type;
    ast->block_state = NULL;
    ast->vardef_index = 0;
    ast->sym_table = createSymTable();
    return ast;
}

VarDefST createVarDefST(Token type, Token id){
    VarDefST ast = malloc(sizeof(struct VarDefST_t));
    ast->id_index = 0;
    ast->id[ast->id_index++] = id;
    ast->type = type;

    return ast; 
}

char *DefinitionST_ToString(DefinitionST ast) {
  char *s = malloc(1000); 
  strcpy(s,spaces());
  indent();
  if(ast->def_type == VarDef)
    strcat(s,VarDefST_ToString(ast->VarDef_tree));
  else if(ast->def_type == FuncDef)
    strcat(s,FuncDefST_ToString(ast->FuncDef_tree));
  else{
    printf("internal error in DefinitionST_ToString\n");
    exit(0);
  }
  outdent(); strcat(s,spaces());
  return s;
}

char *FuncDefST_ToString(FuncDefST ast){
  char *s = malloc(1000); 
  strcpy(s,"funcDef(\n");
  indent(); indent(); indent();
  strcat(s,spaces()); strcat(s,"ID("); strcat(s, ast->id->lexeme); strcat(s,")\n");
  strcat(s,spaces()); strcat(s,"Type("); strcat(s, ast->type->lexeme); strcat(s,")\n");
  for(int x=0;x<ast->vardef_index;x++){
  strcat(s,spaces()); strcat(s,VarDefST_ToString(ast->vardef_tree[x]));
  }
  strcat(s,spaces()); strcat(s,BlockStateST_ToString(ast->block_state));
  outdent(); outdent(); outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

char *VarDefST_ToString(VarDefST ast){;
  char *s = malloc(1000); 
  strcpy(s,"varDef(\n");
  indent(); indent(); strcat(s,spaces());
  strcat(s,"Type("); strcat(s, ast->type->lexeme); strcat(s,")\n");
  for(int x=0;x<ast->id_index;x++){
   strcat(s,spaces()); strcat(s,"ID("); strcat(s, ast->id[x]->lexeme); strcat(s,")\n");
  }
  outdent(); outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

void addBlockStateFuncDefST(FuncDefST ast, BlockStateST block){
    //For Symbol Table of Functions
    addFuncSymbols(ast->sym_table,block);
    ast->block_state = block;
}

void addFuncDefVarDefST(FuncDefST ast, VarDefST def){
//addSymbol(ast->sym_table,createSymbol(VAR,toString_ID(def->id[0])));
  ast->vardef_tree[ast->vardef_index++] = def;
}

void printFuncSymTable(FuncDefST st){
   printSymTable(st->sym_table);
}

char *getVarDef_ID(VarDefST st){
    return toString_ID(st->id[0]);
}