/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef TCTOKEN_H
#define TCTOKEN_H

#include "TCscanner.h"
#include "stdio.h"

//Every possible toy C token
typedef enum{
    INT,
    CHAR,
    RETURN,
    IF,
    ELSE,
    FOR,
    DO,
    WHILE,
    SWITCH,
    CASE, 
    DEFAULT,
    WRITE,
    READ,
    CONTINUE,
    BREAK,
    NEWLINE,
    ID,
    NUMBER,
    CHARLITERAL,
    STRING,
    RELOP,
    ADDOP,
    MULOP,
    ASSIGNOP,
    LPAREN,
    RPAREN,
    LCURLY,
    RCURLY,
    LBRACKET,
    RBRACKET,
    COMMA,
    SEMICOLON,
    NOT,
    COLON,
    ENDFILE
} tokens_t;


struct tokenType{
  tokens_t token_type;
  char *lexeme;
};

typedef struct tokenType* Token;

Token createToken(tokens_t, char*);

//Token Functions
int isKeyword(char*);
void printToken(Token s);
char *printTokenName(Token);
int getTokenType(Token);
char* getLexeme(tokens_t);
char* toString_ID(Token t);

#endif