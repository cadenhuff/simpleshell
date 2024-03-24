#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    char* input;
    char** args;
    int status;

    char* input_file;
    char* output_file;

    //TRUE for > FALSE for >>
    //0 for no redirection 1 for > 2 for >>
    int typeOfRedirection = 0;

    do{
        display();

        input = readInput();
        printf("%s", input);
        args = parseInput(input);

        checkForRedirection(args, &input_file, &output_file, &typeOfRedirection);
        printf("%d",typeOfRedirection);

        printf("%s\n",input_file);
        printf("%s\n",output_file);

        status = runCommand(args,input_file,output_file,typeOfRedirection);

        
        free(input);
        free(args);

    }while(status);


    return 0;
}