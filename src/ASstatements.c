/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pretty.h"
#include "../include/TCtokens.h"
#include "../include/TCparser.h"
#include "../include/ASprogram.h"
#include "../include/ASexpressions.h"
#include "../include/ASdefinitions.h"
#include "../include/ASstatements.h"
 


struct StatementST_t {
  enum statement_prod type;
  union{
    ExpressionStateST expr_tree;
    BreakStateST break_tree;
    BlockStateST block_tree;
    IfStateST if_tree;
    NullStateST null_tree;
    ReturnStateST return_tree;
    ReadStateST read_tree;
    WriteStateST write_tree;
    WhileStateST while_tree;
    NewlineStateST newline_tree;
  };
};

struct ExpressionStateST_t{
    ExpressionST expr;
};

struct BreakStateST_t{
    
};

struct BlockStateST_t{
    VarDefST vardef_tree[1000];
    int vardef_index;
    StatementST statement_tree[1000];
    int statement_index;
};

struct IfStateST_t{
    ExpressionST expr_tree;
    StatementST  if_tree;
    StatementST  else_tree;
};

struct NullStateST_t{
    
};

struct ReturnStateST_t{
    ExpressionST expr_tree;
};

struct WhileStateST_t{
    ExpressionST expr_tree;
    StatementST statement_tree;
};

struct NewlineStateST_t{

};

struct ReadStateST_t{
    Token ID[1000];
    int id_index;
};

struct WriteStateST_t{
    ExpressionST expr_tree[1000];
    int expr_index;
};


NewlineStateST createNewlineStateST(void){
    NewlineStateST ast = malloc(sizeof(struct NewlineStateST_t));
    return ast;
}

ReturnStateST createReturnStateST(void){
    ReturnStateST ast = malloc(sizeof(struct ReturnStateST_t));
    ast->expr_tree = NULL; 
    return ast;
}

WhileStateST createWhileStateST(ExpressionST expr, StatementST statement){
    WhileStateST ast = malloc(sizeof(struct WhileStateST_t));
    ast->expr_tree = expr;
    ast->statement_tree = statement;
    return ast;
}

ReadStateST createReadStateST(Token id){
    ReadStateST ast = malloc(sizeof(struct ReadStateST_t));
    ast->id_index = 0;
    ast->ID[ast->id_index++] = id;
    return ast;
}

WriteStateST createWriteStateST(void){
    WriteStateST ast = malloc(sizeof(struct WriteStateST_t));
    ast->expr_index = 0;
    return ast;
}

BlockStateST createBlockStateST(void){
    BlockStateST ast = malloc(sizeof(struct BlockStateST_t));
    ast->vardef_index = 0;
    ast->statement_index = 0;
    return ast;
}

BreakStateST createBreakStateST(void){
    BreakStateST ast = malloc(sizeof(struct BreakStateST_t));
    return ast;
}

NullStateST createNullStateST(void){
    NullStateST ast = malloc(sizeof(struct NullStateST_t));
    return ast;
}

ExpressionStateST createExpressionStateST(ExpressionST expr){
    ExpressionStateST ast = malloc(sizeof(struct ExpressionStateST_t));
    ast->expr = expr;
    return ast;
}

IfStateST createIfStateST(ExpressionST expr, StatementST statement){
  IfStateST ast = malloc(sizeof(struct IfStateST_t));
  ast->expr_tree = expr;
  ast->if_tree = statement;
  return ast;
}

StatementST createStatementST(enum statement_prod type, void *tree) {
  StatementST ast = malloc(sizeof(struct StatementST_t));
  ast->type = type;

  switch(ast->type) {
    case EXPR_STATE:  ast->expr_tree = (ExpressionStateST)tree; break;
    case BREAK_STATE:  ast->break_tree = (BreakStateST)tree; break;
    case BLOCK_STATE:  ast->block_tree = (BlockStateST)tree; break;
    case IF_STATE:  ast->if_tree = (IfStateST)tree; break;
    case NULL_STATE:  ast->null_tree = (NullStateST)tree; break;
    case RETURN_STATE:  ast->return_tree = (ReturnStateST)tree; break;
    case WHILE_STATE:  ast->while_tree = (WhileStateST)tree; break;
    case READ_STATE:  ast->read_tree = (ReadStateST)tree; break;
    case WRITE_STATE:  ast->write_tree = (WriteStateST)tree; break;
    case NEWLINE_STATE:  ast->newline_tree = (NewlineStateST)tree; break;
  default:
    printf("internal error\n");
    exit(EXIT_FAILURE);
  }

  return ast;
}

char *ExpressionStateST_ToString(ExpressionStateST ast){
  char *s = malloc(1000); 
  strcpy(s,"exprState(\n");
  indent(); 
  strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr));
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

char *BreakStateST_ToString(BreakStateST ast){ 
  char *s = malloc(1000); 
  strcpy(s,"breakState()\n");
  return s;
}

char *BlockStateST_ToString(BlockStateST ast){    
  char *s = malloc(1000); 
  strcpy(s,"blockState(\n");
  indent();
  for(int x=0;x<ast->vardef_index;x++)
  {
    strcat(s,spaces());
    strcat(s,VarDefST_ToString(ast->vardef_tree[x]));
  }
  for(int x=0;x<ast->statement_index;x++){
    strcat(s,spaces());
    strcat(s,StatementST_ToString(ast->statement_tree[x]));
  }
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

char *IfStateST_ToString(IfStateST ast){
  char *s = malloc(1000); 
  strcpy(s,"ifState(\n");
  indent();
  strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr_tree));
  strcat(s,spaces()); strcat(s,StatementST_ToString(ast->if_tree));
  if(ast->else_tree != NULL){
    strcat(s,spaces()); strcat(s,StatementST_ToString(ast->else_tree));
  }
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

char *NullStateST_ToString(NullStateST ast){ 
  char *s = malloc(1000); 
  strcpy(s,"nullState()\n");
  return s;
}

char *ReturnStateST_ToString(ReturnStateST ast){
  char *s = malloc(1000); 
  strcpy(s,"returnState(");
  if(ast->expr_tree != NULL){
    indent(); strcat(s,"\n"); strcat(s,spaces());strcat(s,ExpressionST_ToString(ast->expr_tree));
    outdent(); strcat(s,spaces());
  }
  strcat(s,")\n");
  return s;
}

char *ReadStateST_ToString(ReadStateST ast){
  char *s = malloc(1000); 
  strcpy(s,"readState(");
  for(int x=0;x<ast->id_index-1;x++){
    strcat(s,ast->ID[x]->lexeme); strcat(s,",");
  }
  strcat(s,ast->ID[ast->id_index-1]->lexeme); 
  strcat(s,")\n");
  return s;
}

char *WriteStateST_ToString(WriteStateST ast){
  char *s = malloc(1000); 
  strcpy(s,"writeState(\n");
  indent();
  for(int x=0;x<ast->expr_index-1;x++)
  {
    strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr_tree[x]));
  }
   strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr_tree[ast->expr_index-1]));
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

char *WhileStateST_ToString(WhileStateST ast){
  char *s = malloc(1000); 
  strcpy(s,"whileState(\n");
  indent();
  strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr_tree));
  strcat(s,spaces()); strcat(s,StatementST_ToString(ast->statement_tree));
  outdent(); strcat(s,spaces());
  strcat(s,")\n");
  return s;

}

char *NewlineStateST_ToString(NewlineStateST ast){ 
  char *s = malloc(1000); 
  strcpy(s,"newlineState()\n");
  return s;
}

char *StatementST_ToString(StatementST ast){
  switch(ast->type) {
    case EXPR_STATE: return ExpressionStateST_ToString(ast->expr_tree); 
    case BREAK_STATE:  return BreakStateST_ToString(ast->break_tree); 
    case BLOCK_STATE:  return BlockStateST_ToString(ast->block_tree); 
    case IF_STATE: return  IfStateST_ToString(ast->if_tree);
    case NULL_STATE:  return NullStateST_ToString(ast->null_tree);
    case RETURN_STATE: return ReturnStateST_ToString(ast->return_tree);
    case WHILE_STATE: return WhileStateST_ToString(ast->while_tree);
    case READ_STATE: return ReadStateST_ToString(ast->read_tree);
    case WRITE_STATE: return WriteStateST_ToString(ast->write_tree);
    case NEWLINE_STATE: return NewlineStateST_ToString(ast->newline_tree);
  default:
    printf("INTERNAL ERROR IN StatementST_ToString()\n");
    exit(EXIT_FAILURE);
  }
}

enum statement_prod getType(StatementST ast){
  return ast->type;
}

void addElseStateST(IfStateST ast, StatementST statement){
  ast->else_tree = statement;
}

void addReturnExpressionST(ReturnStateST ast, ExpressionST expr){
  ast->expr_tree = expr;
}

void addReadStateIDST(ReadStateST ast, Token id){
    ast->ID[ast->id_index++] = id;
}

void addWriteStateExpressionST(WriteStateST ast, ExpressionST expr){
  ast->expr_tree[ast->expr_index++] = expr;
}

void addBlockStateVarDefST(BlockStateST ast, VarDefST def){
  ast->vardef_tree[ast->vardef_index++] = def;
}

void addBlockStateStatementST(BlockStateST ast, StatementST statement){
  ast->statement_tree[ast->statement_index++] = statement;
}

void addFuncSymbols(SymTable st, BlockStateST ast){
  for(int x=0;x<ast->vardef_index;x++)
      addSymbol(st, createSymbol(VAR,getVarDef_ID(ast->vardef_tree[x])));
}

void generateStatementSTCode(FILE *f, FuncDefST func_st, StatementST ast){

      switch(ast->type) {
        case EXPR_STATE: generateExpressionStateSTCode(f, func_st, ast->expr_tree); break;
        case BREAK_STATE: generateBreakSTCode(f, func_st, ast->break_tree); break;
        case BLOCK_STATE: generateBlockSTCode(f, func_st, ast->block_tree); break;
        case IF_STATE: generateIFSTCode(f, func_st, ast->if_tree); break;
        case NULL_STATE: generateNullSTCode(f, func_st, ast->null_tree); break;
        case RETURN_STATE: generateReturnSTCode(f, func_st, ast->return_tree); break;
        case WHILE_STATE: generateWhileSTCode(f, func_st, ast->while_tree); break;
        case READ_STATE: generateReadSTCode(f, func_st, ast->read_tree); break;
        case WRITE_STATE: generateWriteSTCode(f, func_st, ast->write_tree); break;
        case NEWLINE_STATE: generateNewlineSTCode(f, func_st, ast->newline_tree); break;
      default:
        printf("INTERNAL ERROR IN generateStatementSTCode()\n");
        exit(EXIT_FAILURE);
    }
}

void generateBlockSTCode(FILE *f, FuncDefST func_st, BlockStateST ast){
    for(int x=0;x<ast->statement_index;x++){
      generateStatementSTCode(f, func_st, ast->statement_tree[x]);
    }
}

void generateExpressionStateSTCode(FILE *f,FuncDefST func_st,ExpressionStateST ast){
    generateExpressionSTCode(f,func_st,ast->expr);
}

void generateBreakSTCode(FILE * f, FuncDefST func_st, BreakStateST ast){
    //fprintf(f,"\tgoto break\n");
}

void generateIFSTCode(FILE *f, FuncDefST func_st, IfStateST ast){
    static int x = 0;
    generateExpressionSTCode(f,func_st,ast->expr_tree);
    fprintf(f,"\ticonst_0\n");
    fprintf(f,"\tif_icmpeq if_label%d\n",x);
    if(ast->else_tree != NULL)
      generateStatementSTCode(f,func_st,ast->else_tree);
    fprintf(f,"if_label%d:\n",x);
    generateStatementSTCode(f,func_st,ast->if_tree);
    x++;
}

void generateNullSTCode(FILE *f, FuncDefST func_st, NullStateST ast){
    //Useless, dont worry about this
}

void generateReturnSTCode(FILE* f, FuncDefST func_st, ReturnStateST ast){

    setFuncReturn(func_st);
    if(ast->expr_tree == NULL){
        printf("ERROR: control reaches end of non-void function\n");
        exit(0);
    }

    //Checks if returned expression evaluates to an integer before generating code
    generateReturnExpressionSTCode(f,func_st,ast->expr_tree);

    if(isMainFunction(func_st) == 0)
       fprintf(f,"\treturn\n");
    else 
      fprintf(f,"\tireturn\n");
}

void generateWhileSTCode(FILE* f, FuncDefST func_st, WhileStateST ast){
    static int loop_start = 0;
    static int loop_end = 0;
    fprintf(f,"loop%d:\n",loop_start);
    generateExpressionSTCode(f, func_st,ast->expr_tree);
    fprintf(f,"\ticonst_0\n");
    fprintf(f,"\tif_icmpne end_loop%d\n",loop_end);
    if(ast->statement_tree != NULL)
      generateStatementSTCode(f,func_st,ast->statement_tree);
    fprintf(f,"\tgoto loop%d\n",loop_start);
    fprintf(f,"end_loop%d:\n",loop_end);
   // fprintf(f,"break:\n");
}


void generateReadSTCode(FILE* f, FuncDefST func_st, ReadStateST ast){
  for(int x=0;x<ast->id_index;x++){
    if(getScannerOffset(func_st) < 4)
      fprintf(f,"\taload_%d\n",getScannerOffset(func_st));
    else 
      fprintf(f,"\taload %d\n",getScannerOffset(func_st));
    fprintf(f,"\tinvokevirtual java/util/Scanner/nextInt()I\n");

    if(findFunctionSymbol(func_st,ast->ID[x]->lexeme) == -1){ 
      printf("ERROR: Trying to read into undefined variable\n");
      exit(0);
    }

    int offset = findFunctionSymbol(func_st,ast->ID[x]->lexeme);
    if(offset == -1)
        printf("ERROR: assignment to undeclared variable %s\n",ast->ID[x]->lexeme);
    else if(offset <= 3)
          fprintf(f,"\tistore_%d\n",findFunctionSymbol(func_st,ast->ID[x]->lexeme));
    else 
        fprintf(f,"\tistore %d\n",findFunctionSymbol(func_st,ast->ID[x]->lexeme));
  }
}

void generateWriteSTCode(FILE* f, FuncDefST func_st, WriteStateST ast){
    for(int x=0;x<ast->expr_index;x++){
        fprintf(f,"\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        generateWriteExpressionSTCode(f, func_st, ast->expr_tree[x]);
        fprintf(f,"\tinvokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
    }
}

void generateNewlineSTCode(FILE* f, FuncDefST func_st, NewlineStateST ast){
  fprintf(f,"\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
  fprintf(f,"\tldc \"\\n\"\n");
  fprintf(f,"\tinvokevirtual java/io/PrintStream.print(Ljava/lang/String;)V\n");
}




