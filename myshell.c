#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>









int main(int argc, char *argv[]){
    //String that holds user input.
    char* input;
    //Array of strings that holds the tokenized input. 
    char** args;
    
    //Used to determine if main shell loop should continue to run. If status is not 0, main shell loop will continue to run.
    int status;

    //Strings that hold names of input and output files used for redirection.
    char* input_file;
    char* output_file;

    //Boolean that holds whether shell should return to the command line prompt immediately after launching that program.
    bool dont_wait= false;

    
    //Integer that holds if there is output redirection and if so what  type: 0 for no redirection 1 for > 2 for >>
    int typeOfRedirection = 0;

    //Pointer to file used for batch mode.
    FILE *batch_file = NULL;
    

    //If statement checks whether a second argument was fed to terminal after ./shell. If a second argument is present we assume that this is 
    //the batch file in which the program should read from for instructions
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


    /*Main loop that simulates shell. In essence, this shell will display a prompt, take in input, 
      tokenize/parse the input, determine if there is I/O redirection, then finally 
      run the given command. After running the command, memory that was dynamically allocated for the 
      input and args will be freed and as long as the command returned with a continuing
      status(I.E. an INT 1), the program will continue to run and restart the shell simulation loop.*/
    do{
        display();

        input = readInput(batch_file);
        //Error handling on input string, also needed for batch file running
        if (input == NULL){
            break;
        }
        
        args = parseInput(input, &dont_wait);

        checkForRedirection(args, &input_file, &output_file, &typeOfRedirection);

        //Run command then return status
        status = runCommand(args,input_file,output_file,typeOfRedirection, dont_wait);

        //Free dynamically allocated memory
        free(input);
        free(args);

    }while(status);


    return 0;
}