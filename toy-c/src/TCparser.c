/*
    Created by Alex Wyatt Spring 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/TCscanner.h"
#include "../include/TCtokens.h"
#include "../include/TCparser.h"
#include "../include/TCglobals.h"
#include "../include/ASprogram.h"
#include "../include/ASexpressions.h"
#include "../include/ASdefinitions.h"
#include "../include/ASstatements.h"
#include "../include/CGSymbols.h" 

SymTable global_st; //Global Symbol Table (Initialized in the Program() prod)

void throwParseError(Scanner s,char *error_type, char *message){
    printf("\nERROR: %s\n", error_type);
    printf("%d: %s",s->line_num,s->curr_line);
    
    for(int x=0;x<s->line_pos+2;x++)
        printf(" ");

    printf("^ '%s' expected\n",message);
    exit(0);
}

void load_sym(Scanner s){ 
  if(debug_scanner || verbose)
    printToken(s->curr_token);
  getNextToken(s); 
}

void match(tokens_t terminal, Scanner s) {
  if (s->curr_token->token_type == terminal) 
     load_sym(s);
  else
    throwParseError(s,"", getLexeme(terminal));
}

void entering(char *production) {
  if(debug_parser || verbose) 
    printf("[PARSER] entering %s\n",production);
}

void exiting(char *production) {
  if(debug_parser || verbose) 
    printf("[PARSER] exiting %s\n",production);
}

ProgramST Program(Scanner s){
    entering("Program");

    global_st = createSymTable();
    getNextToken(s); //First token 
    
    ProgramST program = createProgramST();
    while(getTokenType(s->curr_token) != ENDFILE){
      DefinitionST def = Definition(s);
     // addSymbol(createSymbol(0, def-)) //All Symbols made here are global, function symbols should be made in the Function prod
      addDefinition(program,def);
    }
    
    match(ENDFILE, s);
    exiting("Program");
    return program;
}

DefinitionST Definition(Scanner s){
   entering("Definition");

   DefinitionST def = NULL;
   Token type = Type(s); 
   Token id = s->curr_token; match(ID,s);

    if(getTokenType(s->curr_token) == SEMICOLON)
    {
      match(SEMICOLON,s);
      def = createDefinitionST(VarDef,createVarDefST(type, id));
    } 
    else 
      def = createDefinitionST(FuncDef,FunctionDefinition(s,type,id));
    
    
    exiting("Definition");
    return def;
}

Token Type(Scanner s){
    entering("Type");
    Token t = NULL;
    switch(getTokenType(s->curr_token)){
      case INT: t = s->curr_token; match(INT,s); break;
      case CHAR: t = s->curr_token; match(CHAR,s); break;
      default: throwParseError(s,"Invalid Type","int or char");
    }
    exiting("Type");
    return t;
}

FuncDefST FunctionDefinition(Scanner s, Token id, Token type){

    //Create function symbol tables for local scope here
    
    entering("FunctionDefinition");
    FuncDefST def = createFuncDefST(id, type);
    FunctionHeader(s,def);
    FunctionBody(s,def);
    exiting("FunctionDefinition");
    return def;
}

void FunctionHeader(Scanner s, FuncDefST def){
   entering("FunctionHeader"); 
   match(LPAREN,s);  
   if(getTokenType(s->curr_token) != RPAREN)
     FormalParamList(s,def); 
   match(RPAREN,s); 
      
  exiting("FunctionHeader");
}

void FormalParamList(Scanner s, FuncDefST def){
    entering("FormalParamList");
    Token type;
    Token id;

    if(getTokenType(s->curr_token) != RPAREN){
       type = Type(s);
       id = s->curr_token; match(ID,s);
      addFuncDefVarDefST(def,createVarDefST(type,id));
    }
    if(getTokenType(s->curr_token) == COMMA){
      match(COMMA, s);
      FormalParamList(s,def);
    }
    
    exiting("FormalParamList");
}

void FunctionBody(Scanner s, FuncDefST def){
  entering("FunctionBody");
  addBlockStateFuncDefST(def,CompoundStatement(s)); 
  exiting("FunctionBody");
}

BlockStateST CompoundStatement(Scanner s){
    entering("CompoundStatement");
    BlockStateST block_state = createBlockStateST();
    match(LCURLY, s);

    while(getTokenType(s->curr_token) != RCURLY){
      if(getTokenType(s->curr_token) == INT){
        Token type = s->curr_token; match(INT, s);
        Token id = s->curr_token; match(ID, s);
        addBlockStateVarDefST(block_state, createVarDefST(type,id));
        match(SEMICOLON, s);
      }
      else if(getTokenType(s->curr_token) == CHAR){
        Token type = s->curr_token; match(CHAR, s);
        Token id = s->curr_token; match(ID, s);
        addBlockStateVarDefST(block_state, createVarDefST(type,id));
        match(SEMICOLON, s);
      }
      else{
        StatementST stmt = Statement(s);
        addBlockStateStatementST(block_state,stmt);
      }
    }

    match(RCURLY, s);
    exiting("CompoundStatement");
    return block_state;
}

StatementST Statement(Scanner s){
  entering("Statement");
  StatementST statement = NULL;
  switch(s->curr_token->token_type){
    case BREAK: statement = createStatementST(BREAK_STATE,BreakStatement(s)); break;
    case NEWLINE: statement = createStatementST(NEWLINE_STATE,NewLineStatement(s)); break;
    case IF: statement = createStatementST(IF_STATE,IfStatement(s)); break;
    case SEMICOLON: statement = createStatementST(NULL_STATE,NullStatement(s)); break;
    case RETURN: statement = createStatementST(RETURN_STATE,ReturnStatement(s)); break;
    case WHILE: match(WHILE,s); statement = createStatementST(WHILE_STATE,WhileStatement(s)); break;
    case READ: match(READ,s); statement = createStatementST(READ_STATE,ReadStatement(s)); break;
    case WRITE: match(WRITE,s); statement = createStatementST(WRITE_STATE,WriteStatement(s)); break;
    case LCURLY: statement = createStatementST(BLOCK_STATE,CompoundStatement(s)); break;
    case LPAREN: case ID: case NUMBER: case STRING: case CHARLITERAL: case NOT:
    statement = createStatementST(EXPR_STATE,ExpressionStatement(s)); break;
    default:
      if(strcmp(s->curr_token->lexeme,"-") == 0){
      load_sym(s); statement = createStatementST(EXPR_STATE,ExpressionStatement(s));
      }
      else
        throwParseError(s,"INVALID STATEMENT", "statement");
  }
  exiting("Statement");
  return statement;
}

BreakStateST BreakStatement(Scanner s){
    entering("BreakStatement");
    match(BREAK,s); 
    match(SEMICOLON, s);
    exiting("BreakStatement");
    return createBreakStateST();
}

NewlineStateST NewLineStatement(Scanner s){
    entering("NewlineStatement");
    match(NEWLINE,s);
    match(SEMICOLON, s);
    exiting("NewlineStatement");
    return createNewlineStateST();
}

NullStateST NullStatement(Scanner s){
    entering("NullStatement");
    match(SEMICOLON, s);
    exiting("NullStatement");
    return createNullStateST();
}

IfStateST IfStatement(Scanner s){
  entering("IfStatement");
  match(IF,s);
  ExpressionST expr = NULL;
  StatementST statement1 = NULL;
  StatementST statement2 = NULL;

  match(LPAREN,s); expr = Expression(s); match(RPAREN,s);
  statement1 = Statement(s);

  IfStateST if_state = createIfStateST(expr,statement1);
  if(getTokenType(s->curr_token) == ELSE){
    match(ELSE,s);
    statement2 = Statement(s);
    addElseStateST(if_state,statement2);
  }

  exiting("IfStatement");
  return if_state;
}

ReturnStateST ReturnStatement(Scanner s){
    entering("ReturnStatement");
    match(RETURN,s);

    ReturnStateST statement = createReturnStateST();

    if(getTokenType(s->curr_token) !=  SEMICOLON)
      addReturnExpressionST(statement,Expression(s));
    match(SEMICOLON, s);
    exiting("ReturnStatement");
    return statement;
}

ExpressionST Expression(Scanner s){
  entering("Expression");
  ExpressionST expr1 =  RelopExpression(s);

  while(getTokenType(s->curr_token) == ASSIGNOP){
      OperatorST op = createOperatorST(s->curr_token); match(ASSIGNOP,s);
      ExpressionST expr2 = SimpleExpression(s);
      expr1 = createExpressionST(createExprST(op,expr1,expr2),EXPR_EXPR);
  }

   exiting("Expression");
   return expr1;
}

ExpressionST RelopExpression(Scanner s){
    ExpressionST expr1 =  SimpleExpression(s);
    entering("RelopExpression");

    while(getTokenType(s->curr_token) == RELOP){
      OperatorST op = createOperatorST(s->curr_token); match(RELOP,s);
      ExpressionST expr2 = SimpleExpression(s);
      expr1 = createExpressionST(createExprST(op,expr1,expr2),EXPR_EXPR);
    }

    exiting("RelopExpression");
    return expr1;
}

ExpressionST SimpleExpression(Scanner s){
    entering("SimpleExpression");
    ExpressionST expr1 = Term(s);

    while(getTokenType(s->curr_token) == ADDOP){
      OperatorST op = createOperatorST(s->curr_token); match(ADDOP,s);
      ExpressionST expr2 = Term(s);
      expr1 = createExpressionST(createExprST(op,expr1,expr2),EXPR_EXPR);
    }

    exiting("SimpleExpression");
    return expr1;
}

ExpressionST Term(Scanner s){
    entering("Term");
    ExpressionST expr1 = Primary(s);
    while(getTokenType(s->curr_token) == MULOP){
      OperatorST op = createOperatorST(s->curr_token); match(MULOP,s);
      ExpressionST expr2 = Primary(s);
      expr1 = createExpressionST(createExprST(op,expr1,expr2),EXPR_EXPR);
    }
    exiting("Term");
    return expr1;
}

ExpressionST Primary(Scanner s){
  entering("Primary");
  ExpressionST expr = NULL;
  IdST temp_id = NULL;
  switch(getTokenType(s->curr_token)){
    case ID: 
        temp_id = createIdST(s->curr_token); match(ID,s); 
        if(getTokenType(s->curr_token) == LPAREN)
          expr = createExpressionST(FunctionCall(s,temp_id),FUNC_CALL_EXPR);
        else
          expr = createExpressionST(temp_id, ID_EXPR); 
    break;
    case NUMBER: expr = createExpressionST(createNumberST(s->curr_token),NUM_EXPR); match(NUMBER,s); break;
    case STRING: expr = createExpressionST(createStringST(s->curr_token),STRING_EXPR);  match(STRING,s); break;
    case CHARLITERAL: expr = createExpressionST(createCharST(s->curr_token),CHAR_EXPR); match(CHARLITERAL,s); break;
    case LPAREN: match(LPAREN,s); expr = Expression(s); match(RPAREN,s); break;
    case NOT: match(NOT,s); expr = createExpressionST(createNotST(Primary(s)),NOT_EXPR); break;
    default:
     if(strcmp(s->curr_token->lexeme,"-") == 0){
      load_sym(s);
      expr = createExpressionST(createMinusST(Primary(s)),MINUS_EXPR);
      }
      else
        throwParseError(s,"INVALID EXPRESSION","Expression");
  }

  exiting("Primary");
  return expr;
}

FuncCallST FunctionCall(Scanner s, IdST id){
  entering("FunctionCall");
  FuncCallST func_call = createFuncCallST(id);
  match(LPAREN,s);
  if(getTokenType(s->curr_token) != RPAREN)
    ActualParametersFuncCallST(s,func_call);
  match(RPAREN,s);
  exiting("FunctionCall");
  return func_call;
}

ReadStateST ReadStatement(Scanner s){
  entering("ReadStatement");

  match(LPAREN,s);
  ReadStateST statement = createReadStateST(s->curr_token);
  match(ID,s);

  while(getTokenType(s->curr_token) == COMMA){
      load_sym(s);
      addReadStateIDST(statement,s->curr_token);
      match(ID,s);
  }

  match(RPAREN,s);
  match(SEMICOLON,s);

  exiting("ReadStatement");
  return statement;
}

WriteStateST WriteStatement(Scanner s){
  entering("WriteStatement");
  WriteStateST statement = createWriteStateST();

  match(LPAREN,s);
  if(getTokenType(s->curr_token) == RPAREN)
    throwParseError(s,"MISSING WRITE EXPRESSION", "Expression");

  ActualParametersWriteStateST(s, statement);
  match(RPAREN,s);
  match(SEMICOLON,s);

  exiting("WriteStatement");
  return statement;
}

void ActualParametersWriteStateST(Scanner s, WriteStateST ast){
  entering("ActualParameters");

  if(getTokenType(s->curr_token) == RPAREN){
    exiting("ActualParameters");
    return;
  }
  else
    addWriteStateExpressionST(ast, Expression(s));
    
  while(getTokenType(s->curr_token) == COMMA){
      match(COMMA,s);
      if(getTokenType(s->curr_token) == RPAREN)
        break;
      addWriteStateExpressionST(ast, Expression(s));
  }
  exiting("ActualParameters");
}

void ActualParametersFuncCallST(Scanner s, FuncCallST ast){
  entering("ActualParametersFuncCall");
  if(getTokenType(s->curr_token) != RPAREN){
   addFuncCallExpressionST(ast, Expression(s));
  }
  while(getTokenType(s->curr_token) == COMMA && getTokenType(s->curr_token) != RPAREN){
      load_sym(s);
      addFuncCallExpressionST(ast, Expression(s));
  }
  exiting("ActualParametersFuncCall");
}

ExpressionStateST ExpressionStatement(Scanner s){
  entering("ExpressionStatement");
  ExpressionStateST expr = createExpressionStateST(Expression(s));
  match(SEMICOLON,s);
  exiting("ExpressionStatement");
  return expr;
}

WhileStateST WhileStatement(Scanner s){
    entering("WhileStatement");
    match(LPAREN,s);
    ExpressionST expr = Expression(s);
    match(RPAREN,s);
    StatementST statement = Statement(s);
    exiting("WhileStatement");
    return createWhileStateST(expr,statement);
}