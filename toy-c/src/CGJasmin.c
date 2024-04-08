/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdio.h>
#include "../include/CGJasmin.h"
#include "../include/ASprogram.h"

#define MAX_LOCALS 4
#define MAX_STACK  3

/*
    Most code for generating code is contained in 
    the corresponding absract syntax files, with functions
    provided to generate code for each specific syntax tree
*/


void generateJasminDirectives(FILE *f,char *source_name,char *output_name){
    fprintf(f,".source %s\n",source_name); 
    fprintf(f,".class  public %s\n",output_name); 
    fprintf(f,".super  java/lang/Object\n");       
}

void generateMethodHeader(FILE *f,char *label,char *params){
     fprintf(f,".method public static %s(%s)V\n",label,params); 
     fprintf(f,"\t.limit locals %d",MAX_LOCALS);     
     fprintf(f,"\t.limit stack %d",MAX_STACK);     
}

// void writeMethodReturn(FILE *f, ReturnStateST st){
//      //fprintf(f,"\treturn %s",label,params); 
//      fprintf(f,".end method");     
// }

void generateJasminCode(ProgramST st){
    //Create FILE HERE
    //FILE *output_file
    //writeJasmineDirectives();
    generateProgramCode(st);
}

void writeIntegerAssignment(FILE *f, int num, int frame){
    fprintf(f,"iconst_%d\n",num); 
    fprintf(f,"istore_%d\n",frame); 
}



