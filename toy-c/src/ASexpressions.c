/*
    Created by Alex Wyatt Spring 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pretty.h"
#include "../include/TCtokens.h"
#include "../include/ASprogram.h"
#include "../include/ASexpressions.h"
#include "../include/ASdefinitions.h"
#include "../include/ASstatements.h"

struct ExpressionST_t{
    enum expr_prod type;
    union{
        IdST id;
        NumberST num;
        StringST str;
        CharST chr;
        FuncCallST func_call;
        ExprST expr_tree;
        MinusST minus_tree;
        NotST not_tree;
    };
};

struct NotST_t{
    ExpressionST expr;
};

struct MinusST_t{
    ExpressionST expr;
};

struct ExprST_t{
    OperatorST op;
    ExpressionST expr1;
    ExpressionST expr2;
};

struct FuncCallST_t{
    IdST id;
    ExpressionST expr_tree[1000];
    int expr_index;
};

struct StringST_t{
    Token str;
};

struct CharST_t{
    Token chr;
};

struct IdST_t{
    Token id;
};

struct NumberST_t{
    Token num;
};

struct OperatorST_t{
    Token op;
};

OperatorST createOperatorST(Token op){
    OperatorST ast = malloc(sizeof(struct OperatorST_t));
    ast->op = op;
    return ast;
}

ExpressionST createExpressionST(void *expr, enum expr_prod type){
    ExpressionST ast = malloc(sizeof(struct ExpressionST_t));
    ast->type = type;
       switch(ast->type){
        case NUM_EXPR: ast->num = (NumberST)expr; break;
        case ID_EXPR:  ast->id  = (IdST)expr; break;
        case CHAR_EXPR: ast->chr = (CharST)expr; break;
        case STRING_EXPR: ast->str = (StringST)expr; break;
        case FUNC_CALL_EXPR: ast->func_call = (FuncCallST)expr; break;
        case EXPR_EXPR:     ast->expr_tree = (ExprST)expr; break;
        case MINUS_EXPR:    ast->minus_tree = (MinusST)expr; break;
        case NOT_EXPR:      ast->not_tree  = (NotST)expr; break;
        default:
        printf("INTERNAL ERROR IN: createExpressionST()\n");
        exit(0);
    }
    return ast;
}

StringST createStringST(Token str){
    StringST ast = malloc(sizeof(struct StringST_t));
    ast->str = str;
    return ast;
}

CharST createCharST(Token chr){
    CharST ast = malloc(sizeof(struct CharST_t));
    ast->chr = chr;
    return ast;
}

NumberST createNumberST(Token num){
    NumberST ast = malloc(sizeof(struct NumberST_t));
    ast->num = num;
    return ast;
}

IdST createIdST(Token id){
    IdST ast = malloc(sizeof(struct IdST_t));
    ast->id = id;
    return ast;
}

NotST createNotST(ExpressionST expr){
    NotST ast = malloc(sizeof(struct NotST_t));
    ast->expr = expr;
    return ast;
}

MinusST createMinusST(ExpressionST expr){
    MinusST ast = malloc(sizeof(struct MinusST_t));
    ast->expr = expr;
    return ast;
}

ExprST createExprST(OperatorST op, ExpressionST expr1, ExpressionST expr2){
    ExprST ast = malloc(sizeof(struct ExprST_t));
    ast->op = op;
    ast->expr1 = expr1;
    ast->expr2 = expr2;
    return ast;
}

FuncCallST createFuncCallST(IdST id){
    FuncCallST ast = malloc(sizeof(struct FuncCallST_t));
    ast->id = id;
    ast->expr_index = 0;
    return ast;
}

char *ExpressionST_ToString(ExpressionST ast){
    switch(ast->type){
        case NUM_EXPR: return NumberST_ToString(ast->num); break;
        case ID_EXPR:  return IdST_ToString(ast->id); break;
        case CHAR_EXPR: return CharST_ToString(ast->chr); break;
        case STRING_EXPR: return StringST_ToString(ast->str); break;
        case FUNC_CALL_EXPR: return FuncCallST_ToString(ast->func_call); break;
        case EXPR_EXPR: return ExprST_ToString(ast->expr_tree); break;
        case MINUS_EXPR: return MinusST_ToString(ast->minus_tree); break;
        case NOT_EXPR: return NotST_ToString(ast->not_tree); break;
        default:
        printf("INTERNAL ERROR IN ExpressionST_ToString()\n");
        exit(0);
    }
}

char *NotST_ToString(NotST ast){
  char *s = malloc(1000); 
  strcpy(s,"not(\n");
  indent();
   strcat(s,spaces());
  strcat(s,ExpressionST_ToString(ast->expr));
  outdent();
  strcat(s,spaces());
  strcat(s,")\n");
  return s;
}

char *MinusST_ToString(MinusST ast){
  char *s = malloc(1000); 
  strcpy(s,"minus(\n"); indent();
  strcat(s,spaces());
  strcat(s,ExpressionST_ToString(ast->expr));
  outdent(); strcat(s,spaces());strcat(s,")\n");
  return s;
}

char *NumberST_ToString(NumberST ast){
  char *s = malloc(1000); 
  strcpy(s,"Number(");
  strcat(s,ast->num->lexeme);
  strcat(s,")\n");
  return s;
}

char *IdST_ToString(IdST ast){
  char *s = malloc(1000); 
  strcpy(s,"Identifier(");
  strcat(s,ast->id->lexeme);
  strcat(s,")\n");
  return s;
}

char *CharST_ToString(CharST ast){
  char *s = malloc(1000); 
  strcpy(s,"CharLiteral(");
  strcat(s,ast->chr->lexeme);
  strcat(s,")\n");
  return s;
}

char *StringST_ToString(StringST ast){
  char *s = malloc(1000); 
  strcpy(s,"StringLiteral(");
  strcat(s,ast->str->lexeme);
  strcat(s,")\n");
  return s;
}

char *ExprST_ToString(ExprST ast){
    char *s = malloc(1000); 
    strcpy(s,"expr(\n"); indent();
    strcat(s,spaces()); strcat(s,OperatorST_ToString(ast->op));
    strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr1));
    strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr2));
    outdent();  strcat(s,spaces()); strcat(s,")\n");
    return s;
}

char *FuncCallST_ToString(FuncCallST ast){
  char *s = malloc(1000); 
  strcpy(s,"funcCall(\n");
  indent();
  strcat(s,spaces()); strcat(s,IdST_ToString(ast->id));
  for(int x=0;x<ast->expr_index;x++){
     strcat(s,spaces()); strcat(s,ExpressionST_ToString(ast->expr_tree[x]));
  }
   
  outdent();
  strcat(s,spaces()); strcat(s,")\n");
  return s;
}

char *OperatorST_ToString(OperatorST ast){
 char *s = malloc(1000); 
  strcpy(s,"op(");
  strcat(s,ast->op->lexeme);
  strcat(s,")\n");
  return s;
}

void addFuncCallExpressionST(FuncCallST ast, ExpressionST expr){
    ast->expr_tree[ast->expr_index++] = expr;
}
