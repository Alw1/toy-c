/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/TCtokens.h"
#include "../include/TCscanner.h"

Scanner createScanner(FILE *source){
    Scanner temp = malloc(sizeof(struct ScannerType));
    temp->source_file = source;
    temp->line_num = 0;
    temp->line_pos = 1;
    temp->token_tot = 0;
    temp->curr_token = NULL;
    next_line(temp);
    return temp;
}

void printFile(FILE *source_file){
    char *curr_line = NULL;
    size_t buffer_len = 0;
    int line_num = 1;
    rewind(source_file);
    while(getline(&curr_line, &buffer_len ,source_file) != -1){  
        printf("Line %d: %s",line_num,curr_line);
        line_num++;
    }
    printf("\n");
}


void next_line(Scanner s){
    s->line_num++;
    s->line_pos = 0;

    strcpy(s->curr_line,"");
    if(fgets(s->curr_line, 1000 ,s->source_file) == NULL)
        s->line_pos = -99;
}

char getNextChar(Scanner s){

    if(s->line_pos == -99)
        return -99;

    char c = s->curr_line[s->line_pos++];

    if(c == '\0')
        next_line(s);
    
    return c;
}

char peek_char(Scanner s){
    return s->curr_line[s->line_pos];
}

Token getRELOP(Scanner s, char curr_char){
    char *lexeme = malloc(sizeof(char) * 5);
    strcpy(lexeme,"");
    strncat(lexeme,&curr_char,1);
    char peek = peek_char(s);

    if(curr_char == '=' && peek != '=')
        return createToken(ASSIGNOP, lexeme);
    else if(curr_char == '!' && peek != '=')
        return createToken(NOT,lexeme);
    else if(peek != '=')
        return createToken(RELOP, lexeme);
    
    peek = getNextChar(s);
    strncat(lexeme,&peek,1);
    return createToken(RELOP, lexeme);
}

Token getADDOP(Scanner s, char curr_char){
    char *lexeme = malloc(sizeof(char) * 5);
    strcpy(lexeme,"");
    strncat(lexeme,&curr_char,1);

    char c = peek_char(s);

    if(c == '|'){
        strncat(lexeme,&c,1);
        c = getNextChar(s);
    }
    else{
        printf("WARNING: INVALID CHARACTER '|'\n");
        return NULL;
    }

    return createToken(ADDOP, lexeme);
}

Token getMULOP(Scanner s, char curr_char){
    char *lexeme = malloc(sizeof(char) * 5);
    strcpy(lexeme,"");
    strncat(lexeme,&curr_char,1);

    char c = peek_char(s);

    if(c == '&'){
        strncat(lexeme,&c,1);
        c = getNextChar(s);
    }
    else{
        printf("WARNING: INVALID CHARACTER '&'\n");
        return NULL;
    }


    return createToken(ADDOP, lexeme);
}

Token getID(Scanner s, char curr_char){
    char *lexeme = malloc(sizeof(char) * 100);
    strcpy(lexeme,"");
    strncat(lexeme,&curr_char,1);

    while(isalpha(peek_char(s)) || isdigit(peek_char(s))){
        char c = getNextChar(s);
        strncat(lexeme,&c,1);

        char peek = peek_char(s);
        if(isKeyword(lexeme) != -99 && !isalpha(peek))
            return createToken(isKeyword(lexeme),lexeme);
    }

    return createToken(ID,lexeme);
}

Token getNUMBER(Scanner s, char curr){
    char *lexeme = malloc(sizeof(char) * 100);
    strcpy(lexeme,"");
    strncat(lexeme,&curr,1);

    int state = 0;

    while(1){

        char curr_char = peek_char(s);

        switch(state){
            case 0:
                if (isdigit(curr_char))
                    strncat(lexeme, &curr_char, 1);
                else if (curr_char == '.') {
                    strncat(lexeme, &curr_char, 1);
                    state = 1;
                } 
                else if (curr_char == 'E') {
                    strncat(lexeme, &curr_char, 1);
                    state = 2;
                } 
                else 
                    return createToken(NUMBER, lexeme);
            break;
            case 1:
                if (isdigit(curr_char))
                    strncat(lexeme, &curr_char, 1);
                else if(curr_char == 'E'){
                    strncat(lexeme, &curr_char, 1);
                    state = 2;
                }
                else
                    return createToken(NUMBER, lexeme);
            break;
            case 2:
                if (curr_char == '+' || curr_char == '-') {
                    strncat(lexeme, &curr_char, 1);
                    state = 3;
                }
                else 
                    state = 3;
            break;
            case 3:
                if (isdigit(curr_char))
                    strncat(lexeme, &curr_char, 1);
                else 
                    return createToken(NUMBER, lexeme);
            break;
        }

         curr_char = getNextChar(s);
    }
}

void multiLinedComment(Scanner s){
    int comment_count = 0;
    int state = 0;
    
    while(1){
        char curr_char = getNextChar(s);

        if(curr_char == -99){
            printf("ERROR: unterminated comment\n");
            exit(0);
        }

        switch(state){
            case 0:
                if(curr_char == '*'){
                    comment_count++;
                    state = 1;
                }
                else
                    return;
            break;
            case 1:
                if(curr_char == '*')
                    state = 2;
                else if(curr_char == '/')
                    state = 4;
            break;
            case 2:
                if(curr_char == '/'){
                    comment_count--;
                    if(comment_count == 0)
                        return;
                    state = 1;
                }
            break;
            case 4:
                if(curr_char == '*')
                    comment_count++;              
                state = 1;
            break;
         
        }
    }
}

Token getSTRINGLITERAL(Scanner s, char curr_char){
    char *lexeme = malloc(sizeof(char) * 500);
    strcpy(lexeme,"");
    strncat(lexeme,&curr_char,1);

    char c = getNextChar(s);
    while(c != '"'){
        if(c == '\n'){
            printf("ERROR: unterminated string on line %d\n", s->line_num);
            exit(0);
        }
         strncat(lexeme,&c,1);
         c = getNextChar(s);
    }

    if(c != '"'){
        printf("ERROR: unterminated string on line %d\n", s->line_num);
        exit(0);
    }
    else
        strncat(lexeme,&c,1);

    return createToken(STRING, lexeme);
}

Token getCHARLITERAL(Scanner s){
    char *lexeme = malloc(sizeof(char) * 5);
    strcpy(lexeme,"");

    char c = getNextChar(s);
    if(c == '\'')
     return createToken(CHARLITERAL, "''");

    strncat(lexeme,&c,1);
    c = getNextChar(s);
 
    if(c != '\''){
        printf("ERROR: unterminated charliteral on line %d\n", s->line_num);
        exit(0);
    }

    return createToken(CHARLITERAL, lexeme);
}

Token getNextToken(Scanner scanner){
    while(1){

        Token token = NULL;
        char curr_char = getNextChar(scanner);

        if(curr_char == -99){
            scanner->curr_token = createToken(ENDFILE,"EOF");
            scanner->token_tot++;
            return scanner->curr_token;
        }
    
        switch(curr_char){
            case '(': token = createToken(LPAREN,"("); break;
            case ')': token = createToken(RPAREN,")"); break;
            case '[': token = createToken(LBRACKET,"["); break;
            case ']': token = createToken(RBRACKET,"]"); break;
            case '{': token = createToken(LCURLY,"{"); break;
            case '}': token = createToken(RCURLY,"}"); break;
            case ';': token = createToken(SEMICOLON,";"); break;
            case ':': token = createToken(COLON,":"); break;
            case ',': token = createToken(COMMA,","); break;
            case '+': token = createToken(ADDOP,"+"); break;
            case '-': token = createToken(ADDOP,"-"); break;
            case '*': token = createToken(MULOP,"*"); break;
            case '%': token = createToken(MULOP,"%"); break;
            case '|': token = getADDOP(scanner,curr_char); break;
            case '&': token = getMULOP(scanner,curr_char); break;
            case '\'': token = getCHARLITERAL(scanner); break;
            case '"': token = getSTRINGLITERAL(scanner, curr_char); break; 
            case '<': case '>': case '=': case '!': token = getRELOP(scanner,curr_char); break;
            case '/':
                if(peek_char(scanner) == '*')
                    multiLinedComment(scanner);
                else if(peek_char(scanner) == '/')
                    next_line(scanner);
                else 
                    token = createToken(MULOP,"/");
            break;
            case ' ': case '\n': case '\0': break;
            default:
                if(isalpha(curr_char))
                    token = getID(scanner,curr_char);
                else if(isdigit(curr_char))
                    token = getNUMBER(scanner,curr_char);
                else
                    printf("WARNING: INVALID CHARACTER %c\n",curr_char);
            break;
        }

        if(token != NULL){
            scanner->curr_token = token;
            scanner->token_tot++;
            return token;   
        } 
    }
}
