#include <stdbool.h>




#define CONTINUE 1
#define ERROR 0

#define MAX_COMMAND_LENGTH 1024


void display();
char* readInput();
char** parseInput(char* input, bool* dont_wait);
void checkForRedirection(char** args,char** input_file, char** output_file, int* typeOfRedirection);
int runCommand(char** args, char* input_file, char* output_file, int typeOfRedirection,bool dont_wait);
int sleepy();
//int dir(char** args);
//int cd(char* directory);
//int env();
//int quit();
//int clr();
