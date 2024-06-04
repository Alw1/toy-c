/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/TCglobals.h"
#include "../include/CGJasmin.h"
#include "../include/ASprogram.h"

#define MAX_LOCALS 4
#define MAX_STACK  3

/*
    Most code for generating code is contained in 
    the corresponding absract syntax files, with functions
    provided to generate code for each specific syntax tree
*/


void generateJasminDirectives(FILE *f, char *source_name,char *output_name){
    fprintf(f,".source %s\n",source_name); 
    fprintf(f,".class  public %s\n",output_name); 
    fprintf(f,".super  java/lang/Object\n\n\n");      
}

void generateConstructor(FILE *f){
    fprintf(f,".method public <init>()V\n");
    fprintf(f,"\taload_0\n");
    fprintf(f,"\tinvokenonvirtual java/lang/Object/<init>()V\n");
    fprintf(f,"\treturn\n");
    fprintf(f,".end method\n\n");
}

void generateJasminCode(FILE *f, ProgramST ast){
    generateJasminDirectives(f, source_filename,output_filename);
    generateConstructor(f);
    generateProgramCode(f,ast);
}
