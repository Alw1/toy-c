/*
    Created by Alex Wyatt Spring 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/TCtokens.h"
#include "../include/TCglobals.h"

Token createToken(tokens_t type, char *lexeme){
    Token temp = malloc(sizeof(struct tokenType));
    temp->lexeme = (char*)malloc(sizeof(char)*1000);
    strcpy(temp->lexeme,lexeme);
    temp->token_type = type;

    return temp;
}

void printToken(Token t){
      printf("[SCANNER] (<%s>,\"%s\")\n",printTokenName(t), t->lexeme);
}

char *printTokenName(Token t)
{
    char *tokenStr[] = {"INT", "CHAR",  "RETURN", "IF", "ELSE", "FOR",
                        "DO", "WHILE", "SWITCH", "CASE", "DEFAULT", "WRITE",
                        "READ", "CONTINUE", "BREAK", "NEWLINE", "ID", "NUMBER",
                        "CHARLITERAL", "STRING", "RELOP", "ADDOP", "MULOP", "ASSIGNOP",
                        "LPAREN", "RPAREN", "LCURLY", "RCURLY", "LBRACKET", "RBRACKET",
                        "COMMA", "SEMICOLON", "NOT", "COLON","EOF"};

    return tokenStr[t->token_type];
}

int isKeyword(char lexeme[])
{
    //Returns the enum number of the keyword if valid, -99 otherwise

    char *tokenStr[] = {"int", "char",  "return", "if", "else", "for",
                        "do", "while", "switch", "case", "default", "write",
                        "read", "continue", "break", "newline"};

    for(int x=0;x<16;x++){   
        if(strcmp(lexeme,tokenStr[x]) == 0)
            return x;
    }
    
    return -99; 
}


int getTokenType(Token t){
    return t->token_type;
}

char* getLexeme(tokens_t t){
    char *tokenStr[] = {"int", "char",  "return", "if", "else", "for",
                        "do", "while", "switch", "case", "default", "write",
                        "read", "continue", "break", "newline", "id", "number",
                        "char", "string", "relop", "addop", "mulop", "assignop",
                        "(", ")", "{", "}", "[", "]",",", ";", "not", ":","eof"};

    return tokenStr[t];
}

