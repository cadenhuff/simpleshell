#include <stdbool.h>




#define CONTINUE 1
#define ERROR 0


void display();
char* readInput();
char** parseInput(char* input);
void checkForRedirection(char** args,char** input_file, char** output_file, int* typeOfRedirection);
int runCommand(char** args, char* input_file, char* output_file, int typeOfRedirection);
int sleepy();
//int dir(char** args);
//int cd(char* directory);
//int env();
//int quit();
//int clr();
