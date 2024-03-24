#include <stdbool.h>
void display();
char* readInput();
char** parseInput(char* input);
char* checkForRedirection(char** args,char** input_file, char** output_file, int* typeOfRedirection);
int runCommand(char** args, char* input_file, char* output_file, int typeOfRedirection);
//int dir(char** args);
//int cd(char* directory);
//int env();
//int quit();
//int clr();
