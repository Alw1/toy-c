/*
    Created by Alex Wyatt Spring 2023
*/

#ifndef TCPARSER_H
#define TCPARSER_H

#include "TCscanner.h"
#include "TCtokens.h"
#include "ASprogram.h"
#include "ASdefinitions.h"
#include "ASexpressions.h"
#include "ASstatements.h"

//Parse Functions
void load_sym(Scanner);
void match(tokens_t, Scanner);
void entering(char*);
void exiting(char*);
void throwParseError(Scanner s, char* error_type,char* message);

ProgramST Program(Scanner);
DefinitionST Definition(Scanner);
Token Type(Scanner);
VarDefST VariableDefinition(Scanner);
FuncDefST FunctionDefinition(Scanner, Token, Token);
void FunctionHeader(Scanner, FuncDefST);
void FunctionBody(Scanner, FuncDefST);
FuncCallST FunctionCall(Scanner, IdST);
void FormalParamList(Scanner, FuncDefST);

enum parameter_prod {WRITE_S, FUNC_S};
void ActualParametersFuncCallST(Scanner, FuncCallST);
void ActualParametersWriteStateST(Scanner s, WriteStateST ast);

//Statements
StatementST Statement(Scanner);
BlockStateST CompoundStatement(Scanner);
ExpressionStateST ExpressionStatement(Scanner);
BreakStateST BreakStatement(Scanner);
IfStateST IfStatement(Scanner);
NullStateST NullStatement(Scanner);
ReturnStateST ReturnStatement(Scanner);
WhileStateST WhileStatement(Scanner);
ReadStateST ReadStatement(Scanner);
WriteStateST WriteStatement(Scanner);
NewlineStateST NewLineStatement(Scanner);

//Expressions
ExpressionST Expression(Scanner);
ExpressionST RelopExpression(Scanner);
ExpressionST SimpleExpression(Scanner);
ExpressionST Term(Scanner);
ExpressionST Primary(Scanner);

#endif