#include "myshell.h"
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

    bool dont_wait= false;

    //TRUE for > FALSE for >>
    //0 for no redirection 1 for > 2 for >>
    int typeOfRedirection = 0;

    FILE *batch_file = NULL;
    

    // Check if a command line argument is provided
    if (argc == 2) {
        // Open the specified file for reading
        batch_file = fopen(argv[1], "r");
        if (batch_file == NULL) {
            perror("Error opening file");
            return ERROR;
        }
    } else if (argc > 2) {
        printf("Usage: %s [batchfile]\n", argv[0]);
        return ERROR;
    }



    do{
        

        display();


        input = readInput(batch_file);
        if (input == NULL){
            break;
        }
        
        args = parseInput(input, &dont_wait);

        checkForRedirection(args, &input_file, &output_file, &typeOfRedirection);


        status = runCommand(args,input_file,output_file,typeOfRedirection, dont_wait);

        
        free(input);
        free(args);



    }while(status);


    return 0;
}