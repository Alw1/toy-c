/*
    Created by Alex Wyatt Spring 2024
*/

#ifndef ASPROG_H
#define ASPROG_H

#include "TCtokens.h"
#include "ASprogram.h"
#include "ASdefinitions.h"
#include "ASexpressions.h"
#include "ASstatements.h"

typedef struct ProgramST_t *ProgramST;

ProgramST createProgramST(void);
void addDefinition(ProgramST, DefinitionST);
char *ProgramST_ToString(ProgramST);

//Code Generation Function 
void generateProgramCode(FILE *f, ProgramST ast);

#endif