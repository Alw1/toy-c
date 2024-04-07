#include <stdio.h>
#include "../include/CGJasmin.h"

#define MAX_LOCALS 4
#define MAX_STACK  3

void printJasmineDirectives(FILE *f,char *source_name,char *output_name){
    fprintf(f,".source %s\n",source_name); 
    fprintf(f,".class  public %s\n",output_name); 
    fprintf(f,".super  java/lang/Object\n");       
}

void printMethodHeader(FILE *f, char *label,char *params){
     fprintf(f,".method public static %s(%s)V\n",label,params); 
     fprintf(f,"\t.limit locals %d",MAX_LOCALS);     
     fprintf(f,"\t.limit stack %d",MAX_STACK);     
}




