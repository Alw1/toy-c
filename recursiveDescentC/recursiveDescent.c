// D. Resler 2/24
// modified from a version in
// "Programming Language Translation"
// by Pat Terry (Addison-Wesley, 1986)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "synTree.h"

#define BUFSIZE 80
#define DEBUG true

char sym;
char buffer[BUFSIZE];

int currentSym = 0;

char getNextToken();
void loadSym();
void accept(char);
void entering(char*);
void exiting(char*);

asynTree A(void);
bsynTree B(void);
csynTree C(void);
dsynTree D(void);

int main(void) {
  printf("input: "); scanf("%s",buffer);
  strcat(buffer,"$"); 
  sym = getNextToken();
  asynTree ast = A();
  printf("successful parse\n");
  printf("abstract syntax tree:\n");
  printf("%s",AsynTreeToString(ast));
}

char getNextToken() {
  char ch = buffer[currentSym++];
  if(DEBUG) printf("[SCANNER] %c\n",ch);
  return ch;
}

void load_sym() { sym = getNextToken(); }
void accept(char terminal) {
  if (sym == terminal) load_sym();
  else {
    printf("syntax error\n");
    exit(EXIT_FAILURE);
  }
}

void entering(char *production) {
  if(DEBUG) printf("[PARSER] entering %s\n",production);
}

void exiting(char *production) {
  if(DEBUG) printf("[PARSER] exiting %s\n",production);
}


asynTree A(void) {
  entering("A");
  bsynTree bt = B();
  accept('.'); exiting("A");
  return createAsynTree(bt);
}

bsynTree B(void) {
  void *t;
  enum prod p;
  entering("B");
  switch(sym) {
  case 'x': load_sym();
            p = ID; t = NULL;
	    break;
  case '(': load_sym();
            p = Cprod; t = C();
            accept(')'); break;
  case '[': load_sym();
            p = Bprod; t = B();
            accept(']'); break;
  case ')': case ']': case '+': case '.': 
    // followers of B - do nothing
    p = epsilon;
    break;
  default: printf("syntax error\n"); break;
  }
  exiting("B");
  return createBsynTree(p,t);;
}

csynTree C(void) {
  entering("C");
  bsynTree bt = B(); dsynTree dt = D();
  exiting("C");
  return createCsynTree(bt,dt);
}

dsynTree D(void) {
  dsynTree dst;
  entering("D");
  if(sym == '+') {
    load_sym();
    bsynTree bsTree = B(); dsynTree dsTree = D();
    dst = createDsynTree(bsTree,dsTree);
  } else {
    dst = createDsynTree(NULL,NULL);
  }
  /*
  while(sym == '+') {
    load_sym(); B();
  }
  */
  exiting("D");
  return dst;
}

