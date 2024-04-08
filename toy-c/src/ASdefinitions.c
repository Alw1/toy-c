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
    SymTable global_st;
    Token id;
    Token type;
    VarDefST vardef_tree[1000];
    int vardef_index;
    BlockStateST block_state;
};

struct VarDefST_t {
    Token id;
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

FuncDefST createFuncDefST(Token type, Token id, SymTable global_st){
    FuncDefST ast = malloc(sizeof(struct FuncDefST_t));
    ast->id = id;
    ast->type = type;
    ast->block_state = NULL;
    ast->vardef_index = 0;
    ast->sym_table = createSymTable();
    ast->global_st = global_st;
    return ast;
}

VarDefST createVarDefST(Token type, Token id){
    VarDefST ast = malloc(sizeof(struct VarDefST_t));
    ast->id = id;
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
  //for(int x=0;x<ast->id_index;x++){
  strcat(s,spaces()); strcat(s,"ID("); strcat(s, ast->id->lexeme); strcat(s,")\n");
  
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
  //addSymbol(ast->sym_table,createSymbol(VAR,getVarDef_ID(def)));
  ast->vardef_tree[ast->vardef_index++] = def;
}

void printFuncSymTable(FuncDefST ast){
   printf("\n%s Symbol Table\n",ast->id->lexeme);
   printSymTable(ast->sym_table);
   printf("\n");
}

char *getVarDef_ID(VarDefST st){
    return toString_ID(st->id);
}

void checkFuncDefSemantics(FuncDefST ast){

    for(int x=0;x<ast->vardef_index;x++)
      addSymbol(ast->sym_table,createSymbol(VAR,getVarDef_ID(ast->vardef_tree[x])));

    //checkBlockStateSemantics(ast->sym_table, st->block_state);
}

// void checkVarDefSemantics(VarDefST st){
//     addSymbol(ast->sym_table,createSymbol(VAR,getVarDef_ID(def)));    
// }

char *generateDefinitionCode(DefinitionST st){
  switch(st->def_type){
    case VarDef:
      return generateVarDefCode(st->VarDef_tree);
    case FuncDef:
      return generateFuncDefCode(st->FuncDef_tree);
  }
}

char *generateVarDefCode(VarDefST st){
    return "NOTHING YET";
}

char *generateFuncDefCode(FuncDefST st){
    checkFuncDefSemantics(st);

    
    for(int x=0;x<st->vardef_index;x++)
      generateVarDefCode(st->vardef_tree[x]);

    generateBlockSTCode(st, st->block_state);
    

    return "NOTHING YET";
}