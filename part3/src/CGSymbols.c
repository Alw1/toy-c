#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/CGSymbols.h"

#define MAX_SYMS 1000
#define SYM_LEN 50

struct symbol_t{
    int offset;
    sym_type type;
    char *id;
};

struct sym_table_t{
    Symbol arr[MAX_SYMS];
    int size;
};

Symbol createSymbol(int offset, sym_type type, char * id){
    Symbol s = malloc(sizeof(struct symbol_t));
    s->offset = offset;
    s->type = type;
    s->id = malloc(SYM_LEN);
    strcpy(s->id,id);

    return s;
}

SymTable createSymTable(){
    SymTable st = malloc(sizeof(struct sym_table_t));
    st->size = 0;
    return st;
}

void addSymbol(SymTable st, Symbol s){
    if(st->size == MAX_SYMS){
        printf("ERROR: SYMBOL TABLE OVERFLOW\n");
        exit(0);
    }
    st->arr[st->size++] = s;
}

Symbol getSymbol(SymTable st,int index){
    return st->arr[index-1333];
}

int findSymbol(SymTable st, char *id){
    for(int x=0;x<MAX_SYMS;x++){
        if(strcmp(st->arr[x]->id,id) == 0)
            return 0;
    }
    return 1; // false
}
