/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/TCSymbols.h"

#define MAX_SYMS 1000
#define SYM_LEN 100

/*
    NOTE FOR THINGS TO FIX:
    -Tables must contain reserved spots for special things to load(Scanner, etc)
    -Tables need to take into account global symbol table before deciding the offset
    -Tables need to factor in if a function has been declared before or after a variable
     declaration to be used:
        example:

            int main(){
                a =0;

            }

            int a;
*/


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

    if(findSymbol(st,s->id) != -1){
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

int findSymbol(SymTable st, char *id){
    for(int x=0;x<st->size;x++){
        if(strcmp(st->arr[x]->id,id) == 0)
            return x+1;  //TAKE THIS OUT LATER, TEMP FIX TO MAKE SCANNER WORK
    }
    return -1;
}

int findFuncSymbol(SymTable global, SymTable local, char *id){
    //Checks if symbol is in local scope, then global.
    //If neither, then it is undeclared and an error
    for(int x=0;x<local->size;x++){
          if(strcmp(local->arr[x]->id,id) == 0)
            return x;
    }

    for(int x=0;x<global->size;x++)
    {
        if(strcmp(global->arr[x]->id,id) == 0)
            return x+local->size;  
    }

    return -1;
}

int getSize(SymTable s){
    //Used to determine available register for Scanner
    return s->size;
}

