/*
    Created by Alex Wyatt Spring 2023
*/

#ifndef ASSTMT_H
#define ASSTMT_H

#include "TCtokens.h"
#include "ASprogram.h"
#include "ASexpressions.h"
#include "ASstatements.h"
#include "ASdefinitions.h"


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

void addWriteStateExpressionST(WriteStateST, ExpressionST);

void addBlockStateVarDefST(BlockStateST, VarDefST);
void addBlockStateStatementST(BlockStateST, StatementST);


#endif