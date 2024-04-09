#ifndef TCSYM_H
#define TCSYM_H

#include <stdbool.h>
//typedef enum {VAR,LABEL, OFFSET, NO_TYPE} sym_type;

typedef enum {VAR, FUNC, ASSIGNMENT, NO_TYPE} sym_type;

typedef struct symbol_t *Symbol;
typedef struct sym_table_t *SymTable;

Symbol createSymbol(sym_type type, char *id);
SymTable createSymTable();

void addSymbol(SymTable st, Symbol s);
Symbol getSymbol(SymTable st,int index);

int findSymbol(SymTable st, char *id);

void printSymbol(Symbol s);
void printSymTable(SymTable st);

//Move error functions into parser 
void throwSemanticError(Symbol s);

#endif