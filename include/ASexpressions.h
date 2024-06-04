/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef ASEXPR_H
#define ASEXPR_H

#include "TCtokens.h"
#include "ASprogram.h"
#include "ASdefinitions.h"

#include "ASstatements.h"

enum expr_prod {NUM_EXPR,ID_EXPR, CHAR_EXPR, STRING_EXPR, FUNC_CALL_EXPR, EXPR_EXPR, MINUS_EXPR, NOT_EXPR};

typedef struct ExpressionST_t *ExpressionST;
typedef struct NotST_t *NotST;
typedef struct MinusST_t *MinusST;
typedef struct ExprST_t *ExprST;
typedef struct NumberST_t *NumberST;
typedef struct IdST_t *IdST;
typedef struct CharST_t *CharST;
typedef struct StringST_t *StringST;
typedef struct FuncCallST_t *FuncCallST;
typedef struct OperatorST_t *OperatorST;

ExpressionST createExpressionST(void *, enum expr_prod);
NotST createNotST(ExpressionST);
MinusST createMinusST(ExpressionST);
ExprST createExprST(OperatorST, ExpressionST, ExpressionST);
NumberST createNumberST(Token);
CharST createCharST(Token);
StringST createStringST(Token);
OperatorST createOperatorST(Token);
IdST createIdST(Token);
FuncCallST createFuncCallST(IdST);

char *ExpressionST_ToString(ExpressionST);
char *ExprST_ToString(ExprST);
char *NotST_ToString(NotST);
char *MinusST_ToString(MinusST);
char *NumberST_ToString(NumberST);
char *IdST_ToString(IdST);
char *CharST_ToString(CharST);
char *StringST_ToString(StringST);
char *FuncCallST_ToString(FuncCallST);
char *OperatorST_ToString(OperatorST);

void addFuncCallExpressionST(FuncCallST, ExpressionST);


// //Semantic Check Functions
// void checkExpressionSTSemantics(ExpressionST ast);
// void checkExprStSemantics(ExprST ast);
// void checkNotSTSemantics(NotST ast);
// void checkMinusSTSemantics(MinusST ast);
// void checkNumberSTSemantics(NumberST ast);
// void checkIdSTSemantics(IdST ast);
// void checkCharSTSemantics(CharST ast);
// void checkStringSTSemantics(StringST ast);
// void checkFuncCallSTSemantics(FuncCallST ast);
// void checkOperatorSTSemantics(OperatorST ast);


// //Code Generation Functions
void generateExpressionSTCode(FILE *f, FuncDefST func_st, ExpressionST ast);
void generateWriteExpressionSTCode(FILE *f, FuncDefST func_st, ExpressionST ast); //Handles typecasting for ints to string
void generateReturnExpressionSTCode(FILE *f,FuncDefST func_st,ExpressionST ast);
void generateExprSTCode(FILE *f, FuncDefST func_st,ExprST ast);
void generateNotSTCode(FILE *f, FuncDefST func_st,NotST ast);
void generateMinusSTCode(FILE *f, FuncDefST func_st,MinusST ast);
void generateNumberSTCode(FILE *f, FuncDefST func_st,NumberST ast);
void generateIdSTCode(FILE *f, FuncDefST func_st,IdST ast);
void generateCharSTCode(FILE *f, FuncDefST func_st,CharST ast);
void generateStringSTCode(FILE *f, FuncDefST func_st,StringST ast);
void generateFuncCallSTCode(FILE *f, FuncDefST func_st,FuncCallST ast);
void generateOperatorSTCode(FILE *f, FuncDefST func_st,OperatorST ast);

void evaluateExpressionST(ExpressionST ast);
void evaluateExprST(ExprST ast);

#endif