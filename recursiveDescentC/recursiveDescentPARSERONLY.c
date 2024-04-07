// D. Resler 2/24

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 40
#define DEBUG true

char sym;
char buffer[BUFSIZE];
int currentSym = 0;

char getNextToken();
void loadSym();
void accept(char);
void entering(char*);
void exiting(char*);
void A();
void B();
void C();
void D();

int main(void) {
  printf("input: "); scanf("%s",buffer);
  strcat(buffer,"$");
  sym = getNextToken(); A();
  printf("Successful parse\n");
}

char getNextToken() {
  char ch = buffer[currentSym++];
  if(DEBUG) printf("[SCANNER] %c\n",ch);
  return ch;
}

void load_sym() { sym = getNextToken(); }
void accept(char terminal) {
  if (sym == terminal) load_sym();
  else printf("syntax error\n");
}

void entering(char *production) {
  if(DEBUG) printf("[PARSER] entering %s\n",production);
}

void exiting(char *production) {
  if(DEBUG) printf("[PARSER] exiting %s\n",production);
}

void A() {
  entering("A"); B(); accept('.'); exiting("A");
}

void B() {
  entering("B");
  switch(sym) {
  case 'x': load_sym(); break;
  case '(': load_sym(); C(); accept(')'); break;
  case '[': load_sym(); B(); accept(']'); break;
  case ')': case ']': case '+': case '.':
    // followers of B - do nothing
    break;
  default: printf("syntax error\n");
  }
  exiting("B");
}

void C() {
  entering("C");
  B(); D();
  exiting("C");
}

void D() {
  entering("D");
  while(sym == '+') {
    load_sym(); B();
  }
  exiting("D");
}
