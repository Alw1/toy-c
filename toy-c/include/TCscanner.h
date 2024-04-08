/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef TCSCANNER_H
#define TCSCANNER_H

#include "TCscanner.h"
#include "stdio.h"

typedef struct tokenType* Token;

struct ScannerType{
    FILE *source_file;    //Program source file
    char curr_line[1000]; //Buffer for current line
    int line_num;         //Current line number
    int line_pos;         //Current character on the line
    Token curr_token;     //Current token
    int token_tot;        //Total tokens
};

typedef struct ScannerType* Scanner;

Scanner createScanner(FILE *);

//Print file for debug 
void printFile(FILE *source_file);

//Token Scanning Functions
Token getNextToken(Scanner);
Token getRELOP(Scanner, char);
Token getADDOP(Scanner, char);
Token getMULOP(Scanner, char);
Token getNUMBER(Scanner, char);
Token getID(Scanner, char);
Token getSTRINGLITERAL(Scanner, char);
Token getCHARLITERAL(Scanner);
void multiLinedComment(Scanner);

//File Scanning Functions
char getNextChar(Scanner);
void next_line(Scanner);

#endif