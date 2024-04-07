/*
    Created by Alex Wyatt Spring 2023
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

#endif