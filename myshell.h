#include <stdbool.h>
#include <stdio.h>


//Constants used as returns for command functions.
#define CONTINUE 1
#define ERROR 0




void display();
char* readInput(FILE *batch_file);
char** parseInput(char* input, bool* dont_wait);
void checkForRedirection(char** args,char** input_file, char** output_file, int* typeOfRedirection);
int runCommand(char** args, char* input_file, char* output_file, int typeOfRedirection,bool dont_wait);

int dir(char* directory, char* output_file, int typeOfRedirection);
int cd(char* directory);
int env(char* output_file, int typeOfRedirection);
int quit();
int clr();
int echo(char** args, char* output_file, int typeOfRedirection);
int help();
int pause();


