/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef ASEXPR_H
#define ASEXPR_H

#include "TCtokens.h"
#include "ASprogram.h"
#include "ASdefinitions.h"
#include "ASexpressions.h"
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


//Semantic Check Functions
void checkExpressionSTSemantics(ExpressionST ast);
void checkExprStSemantics(ExprST ast);
void checkNotSTSemantics(NotST ast);
void checkMinusSTSemantics(MinusST ast);
void checkNumberSTSemantics(NumberST ast);
void checkIdSTSemantics(IdST ast);
void checkCharSTSemantics(CharST ast);
void checkStringSTSemantics(StringST ast);
void checkFuncCallSTSemantics(FuncCallST ast);
void checkOperatorSTSemantics(OperatorST ast);


//Code Generation Functions
char *generateExpressionSTcode(ExpressionST ast);
char *generateExprSTcode(ExprST ast);
char *generateNotSTcode(NotST ast);
char *generateMinusSTcode(MinusST ast);
char *generateNumberSTcode(NumberST ast);
char *generateIdSTcode(IdST ast);
char *generateCharSTcode(CharST ast);
char *generateStringSTcode(StringST ast);
char *generateFuncCallSTcode(FuncCallST ast);
char *generateOperatorSTcode(OperatorST ast);

#endif