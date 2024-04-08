/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef ASSTMT_H
#define ASSTMT_H

#include "TCtokens.h"
#include "ASprogram.h"
#include "ASexpressions.h"
#include "ASstatements.h"
#include "ASdefinitions.h"
#include "TCSymbols.h"

enum statement_prod {EXPR_STATE, BREAK_STATE, BLOCK_STATE, IF_STATE, NULL_STATE, RETURN_STATE, WHILE_STATE, READ_STATE, WRITE_STATE, NEWLINE_STATE, NO_STATE};

typedef struct StatementST_t *StatementST;
typedef struct ExpressionStateST_t *ExpressionStateST;
typedef struct BreakStateST_t *BreakStateST;
typedef struct BlockStateST_t *BlockStateST;
typedef struct IfStateST_t *IfStateST;
typedef struct NullStateST_t *NullStateST;
typedef struct ReturnStateST_t *ReturnStateST;
typedef struct ReadStateST_t *ReadStateST;
typedef struct WriteStateST_t *WriteStateST;
typedef struct WhileStateST_t *WhileStateST;
typedef struct NewlineStateST_t *NewlineStateST;

typedef struct ExpressionST_t *ExpressionST;
typedef struct VarDefST_t *VarDefST;
typedef struct FuncDefST_t *FuncDefST;

StatementST createStatementST(enum statement_prod type, void *tree);
IfStateST createIfStateST(ExpressionST expr, StatementST statement);
WhileStateST createWhileStateST(ExpressionST expr, StatementST statement);
ExpressionStateST createExpressionStateST(ExpressionST expr);
BreakStateST createBreakStateST(void);
BlockStateST createBlockStateST(void);
NullStateST createNullStateST(void);
ReturnStateST createReturnStateST(void);
ReadStateST createReadStateST(Token id);
WriteStateST createWriteStateST(void);
NewlineStateST createNewlineStateST(void);

char *StatementST_ToString(StatementST ast);
char *ExpressionStateST_ToString(ExpressionStateST ast);
char *BreakStateST_ToString(BreakStateST ast);
char *BlockStateST_ToString(BlockStateST ast);
char *IfStateST_ToString(IfStateST ast);
char *NullStateST_ToString(NullStateST ast);
char *ReturnStateST_ToString(ReturnStateST ast);
char *ReadStateST_ToString(ReadStateST ast);
char *WriteStateST_ToString(WriteStateST ast);
char *WhileStateST_ToString(WhileStateST ast);
char *NewlineStateST_ToString(NewlineStateST ast);

enum statement_prod getType(StatementST);

void addElseStateST(IfStateST, StatementST);
void addReturnExpressionST(ReturnStateST, ExpressionST);
void addReadStateIDST(ReadStateST, Token);
void addBlockStateVarDefST(BlockStateST, VarDefST);
void addBlockStateStatementST(BlockStateST, StatementST);
void addWriteStateExpressionST(WriteStateST, ExpressionST);
void addElseStateST(IfStateST, StatementST);
void addReturnExpressionST(ReturnStateST, ExpressionST);
void addReadStateIDST(ReadStateST, Token);

//For Function Symbol tables 
void addFuncSymbols(SymTable st, BlockStateST ast);

//Code Generation Functions
char *generateBlockSTCode(FuncDefST func_st, BlockStateST ast);
char *generateBreakSTCode(FuncDefST func_st, BreakStateST ast);
char *generateIFSTCode(FuncDefST func_st, IfStateST ast);
char *generateNullSTCode(FuncDefST func_st, NullStateST ast);
char *generateReturnSTCode(FuncDefST func_st, ReturnStateST ast);
char *generateWhileSTCode(FuncDefST func_st, WhileStateST ast);
char *generateReadSTCode(FuncDefST func_st, ReadStateST ast);
char *generateWriteSTCode(FuncDefST func_st, WriteStateST ast);
char *generateNewlineSTCode(FuncDefST func_st, NewlineStateST ast);

//Semantic Check Functions
void checkBlockSTSemantics(FuncDefST func_st, BlockStateST ast);
void checkBreakSTSemantics(FuncDefST func_st, BreakStateST ast); 
void checkIFSTSemantics(FuncDefST func_st, IfStateST ast);
void checkNullSTSemantics(FuncDefST func_st, NullStateST ast);
void checkReturnSTSemantics(FuncDefST func_st, ReturnStateST ast); //Return type must match func type
void checkWhileSTSemantics(FuncDefST func_st, WhileStateST ast);
void checkReadSTSemantics(FuncDefST func_st, ReadStateST ast);
void checkWriteSTSemantics(FuncDefST func_st, WriteStateST ast);
void checkNewlineSTSemantics(FuncDefST func_st, NewlineStateST ast);

#endif