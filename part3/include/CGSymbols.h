#ifndef CGSYM_H
#define CGSYM_H

typedef enum {VAR, LABEL, OFFSET, NO_TYPE} sym_type;

typedef struct symbol_t *Symbol;
typedef struct sym_table_t *SymTable;

Symbol createSymbol(int offset, sym_type type, char * id);
SymTable createSymTable();

void addSymbol(SymTable st, Symbol s);
Symbol getSymbol(SymTable st,int index);

int findSymbol(SymTable st, char *id);

void throwSemanticError(Symbol s);

#endif