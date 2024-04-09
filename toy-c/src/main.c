/*
    Created by Alex Wyatt Spring 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/TCscanner.h"
#include "../include/TCtokens.h"
#include "../include/TCparser.h"
#include "../include/TCglobals.h"
#include "../include/CGJasmin.h"

//Global Variables
int debug_scanner = 0; 
int debug_file = 0;
int debug_parser = 0;
int debug_symbol = 0;
int debug_abstract = 0;
int debug_code_gen = 0;
int verbose = 0;
int help = 0;

char version[100] = "Toy-C Version -99.9";
char class_filename[100] = "";
char output_filename[100] = "";
char source_filename[100] = "";

//Command Line Argument Functions
void parseArguments(int argc,char* argv[]);
void printHelpMessage();

int main(int argc, char *argv[]){

    parseArguments(argc,argv);
   
    FILE *source_file = fopen(source_filename,"r");    

    if(source_file == NULL){
        printf("ERROR: FILE NOT FOUND\n");
        exit(0);
    }

    if(help)
        printHelpMessage();

    Scanner scanner = createScanner(source_file);
    ProgramST program_ast = Program(scanner);  

    if(debug_scanner)
        printf("[SCANNER] total tokens: %d\n", scanner->token_tot-1);

    if(debug_abstract)
        printf("<<Abstract Syntax Tree>>\n %s",ProgramST_ToString(program_ast));

    if(debug_file || verbose)
        printFile(scanner->source_file);

    FILE *output = fopen("testing.j","w");

    if(debug_code_gen)
        generateJasminCode(output, program_ast);


    fclose(source_file); 
    
    return 0;
}

void parseArguments(int argc, char* argv[]){

    for(int x=1; x<argc; x++){
        if(strcmp(argv[x],"-version") == 0)
            printf("%s\n",version);
        else if(strcmp(argv[x],"-help") == 0){
            help = 1;
        }
        else if(strcmp(argv[x],"-debug") == 0){
            if(x+1 == argc){
                printf("ERROR: -debug <option>\n");
                exit(0);
            }
            
            if(strcmp(argv[x+1],"0") == 0){
                debug_scanner = 1;
                debug_parser = 1;
                debug_file = 1;
                debug_code_gen = 1;
                x++;
            }
            else if(strcmp(argv[x+1],"1") == 0){
                debug_scanner = 1;
                x++;
            }
            else if(strcmp(argv[x+1],"2") == 0){
                debug_parser = 1;
                x++;
            }
            else{
                printf("ERROR: -debug <option> option = 0,1, or 2\n");
                exit(0);
            }
        }
        else if(strcmp(argv[x],"-verbose") == 0)
            verbose = 1;
        else if(strcmp(argv[x],"-abstract") == 0)
            debug_abstract = 1;
        else if(strcmp(argv[x],"-code") == 0)
            debug_code_gen = 1;
        else if(strcmp(argv[x],"-class") == 0){
            if(x+1 == argc){
                printf("ERROR: -class <filename>\n");
                exit(0);
            }
            x++;
            strcpy(class_filename,argv[x]);
        }
        else if(strcmp(argv[x],"-output") == 0){
            if(x+1 == argc){
                printf("ERROR: -output <filename>\n");
                exit(0);
            }
            x++;
            strcpy(output_filename,argv[x]);
        }
        else if(strcmp(argv[x],"-symbol") == 0)
            debug_symbol = 1;
        else 
              strcpy(source_filename,argv[x]);  
    }

   

}

void printHelpMessage(){
    printf("\nUsage: make run flags=""\"options\""" source=""\"source file\"""\n");
    printf("Example: make run flags=""\"-verbose\""" source=""\"test/test.tc\"""\n\n");
    printf("\t\tOptions\n");
    printf("+-----------------------------------------+\n");
    printf("-help\tdisplay usage message\n");
    printf("-output <file>\tspecify target file name\n");
    printf("-class  <file>\tspecify class file name\n");
    printf("-debug  <level>\tdisplay debug messages\n");
    printf("\t<level> options:\n");
    printf("\t    0 - all messages\n");
    printf("\t    1 - scanner messages only\n");
    printf("\t    2 - parser messages only\n");
    printf("-abstract\tprint the abstract syntax tree\n");
    printf("-symbol\t\tprint the symbol table\n");
    printf("-code\t\tdump the generated  program\n");
    printf("-verbose\tdisplay all information\n");
    printf("-version\tdisplay the program version\n");
    printf("+-----------------------------------------+\n");
}