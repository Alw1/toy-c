/*
    Created by Alex Wyatt Spring 2023
*/

#include <stdio.h>
#include "../include/CGJasmin.h"
#include "../include/ASprogram.h"

#define MAX_LOCALS 4
#define MAX_STACK  3

void writesJasmineDirectives(FILE *f,char *source_name,char *output_name){
    fprintf(f,".source %s\n",source_name); 
    fprintf(f,".class  public %s\n",output_name); 
    fprintf(f,".super  java/lang/Object\n");       
}

void writeMethodHeader(FILE *f,char *label,char *params){
     fprintf(f,".method public static %s(%s)V\n",label,params); 
     fprintf(f,"\t.limit locals %d",MAX_LOCALS);     
     fprintf(f,"\t.limit stack %d",MAX_STACK);     
}

void writeMethodReturn(FILE *f, ReturnStateST st){
     //fprintf(f,"\treturn %s",label,params); 
     fprintf(f,".end method");     
}

// void generateJasminCode(ProgramST st){
//     //Create FILE HERE
//     FILE *output_file
//     writeJasmineDirectives()
// }

void writeIntegerAssignment(FILE *f, int num, int frame){
    fprintf(f,"iconst_%d\n",num); 
    fprintf(f,"istore_%d\n",frame); 
}



