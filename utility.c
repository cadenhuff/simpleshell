#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "myshell.h"
extern char **environ;




void display() {
    // Buffer to hold the current working directory path
    char cwd[1024]; 

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s ", cwd); 
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }

    char *prompt = "==>";
    fputs(prompt, stdout); 
}




char* readInput(FILE *batch_file){
    char* input = malloc(100); // Allocate memory for input buffer
    if (input == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
 // Read input from the specified file or stdin based on the condition
    if (batch_file != NULL) {
        if (fgets(input, 100, batch_file) == NULL) {
            free(input); // Free memory if fgets fails
            return NULL;
        }
    } else {

        if (fgets(input, 100, stdin) == NULL) {
            free(input); // Free memory if fgets fails
            return NULL;
        }
        if (strcmp(input, "\n") == 0) {
            free(input); 
            return NULL;
        }
    }

  
    return input;
}


char** parseInput(char* input, bool* dont_wait){
    char **commands = NULL; //Array of Strings
	int wordCount = 0; //
    int bufferSize = 20;


	// Allocate memory for the array of strings
    commands = (char **)malloc(bufferSize * sizeof(char *));
    if (commands == NULL) {
        printf("Memory allocation failed!\n");
    	exit(1);
	}
		
	// Tokenize input and store in the array of strings
    char *token = strtok(input, " \t\n");
    while (token != NULL) {

        //If & symbol is found, set dont_wait to true to be used for background exectution
        if(strcmp(token,"&") == 0){
            *dont_wait = true;
            token = strtok(NULL, " \t\n");
            continue;
            
        }
        commands[wordCount] = strdup(token);
    	wordCount++;

        	// Check if we need to resize the buffer
        	if (wordCount >= bufferSize) {
                // Double the buffer size
            	bufferSize *= 2; 
                //Dynamically reallocate memory for buffer
            	commands = (char**)realloc(commands, bufferSize * sizeof(char *));
            	if (commands == NULL) {
                	printf("Memory allocation failed!\n");
                	return NULL;
            	}
        	}

        	// Get the next token
        	token = strtok(NULL, " \t\n");
    	}
        // Null-terminate the commands array
        commands[wordCount] = NULL;
        return commands;
}


int dir(char* directory, char* output_file, int typeOfRedirection){
    FILE *fp;
    //Determine the type of output redirection is being used, w for > (overwrite) and a for >> (append)
    const char *mode = (typeOfRedirection == 1) ? "w" : (typeOfRedirection == 2) ? "a" : "none";

    //If no I/O Redirection
    if(strcmp(mode,"none") == 0){
        if (directory != NULL) {
            char command[100];
            //Create command with directory
            sprintf(command, "ls -al %s", directory);
            system(command);
        } 
        else {
        system("ls -al");
        }
        return CONTINUE;

    }

    //Run command with I/O redirection
    fp = fopen(output_file, mode);
    if(fp == NULL){
        perror("fopen");
        return ERROR;

    }
    if (freopen(output_file,mode,stdout) == NULL){
        perror("freopen");
        return ERROR;
    }

     if (directory != NULL && strcmp(directory, ">") != 0 && strcmp(directory, ">>") != 0) {
        char command[100];
        //Create command with directory
        sprintf(command, "ls -al %s", directory);
        system(command);
    } else {
        system("ls -al");
    }
    // Flush any remaining output
    fflush(stdout); 
    // Close the output file
    fclose(fp);

    // Redirect stdout back to the terminal
    if (freopen("/dev/tty", "a", stdout) == NULL) {
        perror("freopen");
        return ERROR; 
    }
 
    return CONTINUE;
}



int cd(char* directory){
    //If no directory given, print the current working directory.
    if(directory == NULL){
		printf("PWD : %s\n", getenv("PWD"));
		return CONTINUE;
	}
	//chdir() function changes the current working directory of the calling process to the directory specified by path. 
	//If the operation is successful, chdir() returns 0; otherwise, it returns -1 and sets errno to indicate the error.
	if(chdir(directory) == -1){
		perror("Directory does not exist");
		return ERROR;
	}

	//cwd is string used to hold the current working directory
	char cwd[1024];
	//use getcwd to set cwd to the current working directory, check for error
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd"); 
        return ERROR;
    }
	
	//updates PWD environ var to full path of current directory, 1 is the overwrite value meaning if PWD environ var exists, 
	//the func will overwrite the existing value.
	if(setenv("PWD", cwd, 1) == -1){
		perror("Could not set env");
		return ERROR;
	}
    //Print new current working directory.
	printf("PWD : %s\n", getenv("PWD"));
	return CONTINUE;
}   




int env(char* output_file, int typeOfRedirection){
    FILE *fp;
    //Determine the type of output redirection is being used, w for > (overwrite) and a for >> (append)
    const char *mode = (typeOfRedirection == 1) ? "w" : (typeOfRedirection == 2) ? "a" : "none";

    //If no I/O Redirection, print to terminal
    if(strcmp(mode,"none") == 0){
        int i;
        for (i = 0; environ[i] != NULL; i++)
            printf("%s\n",environ[i]);
        return CONTINUE;
    }

    //I/O redirection handling
    fp = fopen(output_file, mode);
    if(fp == NULL){
        perror("fopen");
        return ERROR;

    }
    if (freopen(output_file,mode,stdout) == NULL){
        perror("freopen");
        return ERROR;
    }

    //Prints evironment strings to output_file
    int i;
    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n",environ[i]);
        

    // Flush any remaining output
    fflush(stdout); 
    // Close the output file
    fclose(fp); 
    // Redirect stdout back to the terminal
    if (freopen("/dev/tty", "a", stdout) == NULL) {
        perror("freopen");
        return ERROR; // Error restoring stdout
    }
    return CONTINUE;

}

int quit(){
    return ERROR;
}

int clr(){
    int result = system("clear");
    if (result == -1) {
        perror("Error executing clear command");
        return ERROR; 
    } else {
        return CONTINUE; 
    }
}





int echo(char** args, char* output_file, int typeOfRedirection){
    
    FILE *fp;
    //Determine the type of output redirection is being used, w for > (overwrite) and a for >> (append)
    const char *mode = (typeOfRedirection == 1) ? "w" : (typeOfRedirection == 2) ? "a" : "none";
    if(strcmp(mode, "none") == 0){
        int i = 1;
        while(args[i] != NULL && strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0){
            printf("%s ",args[i]);
            i++;
        }
        printf("\n");
        return CONTINUE;
    }
    //I/O Redirection Handling
    fp = fopen(output_file, mode);
    if(fp == NULL){
        perror("fopen");
        return ERROR;

    }
    if (freopen(output_file,mode,stdout) == NULL){
        perror("freopen");
        return ERROR;
    }   

    //Print all given arguments until we arrive at a > or a >>, signifying the end of the printable arguments.
    int i = 1;
    while(args[i] != NULL && strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0){
        printf("%s ",args[i]);
        i++;
    }
    printf("\n");

    // Flush any remaining output
    fflush(stdout); 
    // Close the output file
    fclose(fp); 
    // Redirect stdout back to the terminal
    if (freopen("/dev/tty", "a", stdout) == NULL) {
        perror("freopen");
        return ERROR; 
    }
    return CONTINUE;


    
    
}

int help(){

    return CONTINUE;
}




int pause(){
    printf("Press Enter to continue...\n");

    while (getchar() != '\n');

    printf("Continuing with shell operations...\n");

    return CONTINUE;

}


void checkForRedirection(char** args, char** input_file, char** output_file, int* typeOfRedirection) {
    *input_file = NULL;
    *output_file = NULL;
    *typeOfRedirection = 0;

    //Iterate through args array, if a > or >> is found we extract the output_file,
    //if a < is found we extract the input_file.
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            *typeOfRedirection = 1;
            *output_file = args[i + 1];
        } if(strcmp(args[i], ">>") == 0){
            *output_file = args[i + 1];
            *typeOfRedirection = 2; 

        }
        
        else if (strcmp(args[i], "<") == 0) {
            *input_file = args[i + 1];
        }
    }
}


//Function responsible for forc and execing.
int forkAndExec(char** args, char* input_file, char* output_file, int typeOfRedirection, bool dont_wait){
    pid_t pid;
	int status;
    
	
	switch(pid = fork()){
        //ERROR
		case -1:
			perror("fork");
            return ERROR;
        //Child process
		case 0: 

            //Checking if I/O Redirection is requested.s
            if (input_file != NULL) {
                freopen(input_file, "r", stdin);
            }
            if (output_file != NULL) {
                const char *mode = (typeOfRedirection == 1) ? "w" : (typeOfRedirection == 2) ? "a" : NULL;
                FILE *output = freopen(output_file, mode, stdout);
                if (output == NULL) {
                    perror("freopen");
                    exit(ERROR);
                }
            }

        
            //execvp used to execute file, commands[0] cotains name of file, commands is string array of args where 
            //commnads[0] is the name of the file.
            if((execvp(args[0], args) == -1)){
                perror("exec");
                return ERROR;
            }
            
        //Parent Process
		default:
				
		    if(!dont_wait){
				waitpid(pid, &status, 0);
			}
            
		}
		
        return CONTINUE;
}



//Determines which command is trying to be invoked. If no known internal command is being called, will call forkAndExec() func.
int runCommand(char** args, char* input_file, char* output_file, int typeOfRedirection, bool dont_wait){

    if (!strcmp("clr",args[0])){
		return clr();	
	}
	else if(!strcmp("cd", args[0])){
		return cd(args[1]);
	}

	else if (!strcmp("dir", args[0])){
		return dir(args[1],output_file, typeOfRedirection);
	}
	else if (!strcmp("quit", args[0])){
		return quit();
	}
	else if (!strcmp("environ",args[0])){
		return env(output_file, typeOfRedirection);
	}
    else if (!strcmp("echo",args[0])){
		return echo(args, output_file, typeOfRedirection);
    }
    else if (!strcmp("help",args[0])){
		return help();
    }
    else if (!strcmp("pause",args[0])){
		return pause();
    }
	else{
		return forkAndExec(args, input_file,output_file, typeOfRedirection, dont_wait);
	}
    
}

