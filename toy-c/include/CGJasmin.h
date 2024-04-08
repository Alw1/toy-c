#ifndef CGJASMIN_H
#define CGJASMIN_H

#include "ASprogram.h"

void generateJasmineDirectives(FILE *f,char *source_name,char *output_name);
void generateMethodHeader(FILE *f, char *label,char *params);
void generateJasminCode(ProgramST st);
#endif