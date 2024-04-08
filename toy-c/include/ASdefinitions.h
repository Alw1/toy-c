/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef ASDEF_H
#define ASDEF_H

#include "TCtokens.h"
#include "ASprogram.h"
#include "ASdefinitions.h"
#include "ASexpressions.h"
#include "ASstatements.h"

enum definition_prods { FuncDef, VarDef }; 
typedef struct DefinitionST_t *DefinitionST;
typedef struct FuncDefST_t *FuncDefST;
typedef struct VarDefST_t *VarDefST;

DefinitionST createDefinitionST(enum definition_prods, void *);
FuncDefST createFuncDefST(Token, Token, SymTable global_st);//void *, enum statement_prod);
VarDefST createVarDefST(Token, Token);

void addFuncDefVarDefST(FuncDefST ast, VarDefST def);
void addBlockStateFuncDefST(FuncDefST ast, BlockStateST block);
char *DefinitionST_ToString(DefinitionST ast);
char *FuncDefST_ToString(FuncDefST ast);
char *VarDefST_ToString(VarDefST ast);

void printFuncSymTable(FuncDefST st);
char *getVarDef_ID(VarDefST st);


//Semantic Checks
void checkFuncDefSemantics(FuncDefST ast);
void checkVarDefSemantics(SymTable global_st, SymTable func_st,FuncDefST ast);

//Jasmin Code Generation
char *generateDefinitionCode(DefinitionST ast);
char *generateVarDefCode(VarDefST ast);
char *generateFuncDefCode(FuncDefST ast);



#endif