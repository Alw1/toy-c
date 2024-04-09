/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/TCSymbols.h"

#define MAX_SYMS 1000
#define SYM_LEN 100

struct symbol_t{
    sym_type type;
    char *id;
};

struct sym_table_t{
    Symbol arr[MAX_SYMS];
    int size;
};

Symbol createSymbol(sym_type type, char *id){
    Symbol s = malloc(sizeof(struct symbol_t));
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

void printSymTable(SymTable st){
    for(int x=0;x<st->size;x++){
        printSymbol(st->arr[x]);
    }
}

void printSymbol(Symbol s){
    switch(s->type){
        case VAR:
            printf("[SYMBOL] <VAR> %s\n", s->id);
            break;
        case FUNC:
            printf("[SYMBOL] <FUNC> %s\n", s->id);
            break;
        default:
            printf("INVALID SYMBOL TYPE");
            exit(0);
    }
}

void addSymbol(SymTable st, Symbol s){
    if(st->size == MAX_SYMS){
        printf("ERROR: SYMBOL TABLE OVERFLOW\n");
        exit(0);
    }

    if(findSymbol(st,s->id)){
        switch(s->type){
            case VAR:
                printf("Error: Variable %s already defined\n",s->id);
                break;
            case FUNC:
                printf("Error: Function %s already defined\n",s->id);
                break;
            default:
                exit(0);
        }
    }
    
    st->arr[st->size++] = s;
}

Symbol getSymbol(SymTable st,int index){
    if(index > st->size || index < 0){
        printf("ERROR: Index out of bounds\n");
        exit(0);
    }
    
    return st->arr[index-1];
}

bool findSymbol(SymTable st, char *id){
    for(int x=0;x<st->size;x++){
        if(strcmp(st->arr[x]->id,id) == 0)
            return true;
    }
    return false;
}

