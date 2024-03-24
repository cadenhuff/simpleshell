#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
extern char **environ;

int dir(char* args){
    return 0;
}

int cd(char* directory){
    if(directory == NULL){
		printf("PWD : %s\n", getenv("PWD"));
		return 0;
	}
	//chdir() function changes the current working directory of the calling process to the directory specified by path. 
	//If the operation is successful, chdir() returns 0; otherwise, it returns -1 and sets errno to indicate the error.
	if(chdir(directory) == -1){
		perror("Directory does not exist");
		return 1;
	}
	//cwd is string used to hold the current working directory
	char cwd[1024];
	//use getcwd to set cwd to the current working directory, check for error
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd"); 
        return 1;
    }
	
	//updates PWD environ var to full path of current directory, 1 is the overwrite value meaning if PWD environ var exists, 
	//the func will overwrite the existing value.
	if(setenv("PWD", cwd, 1) == -1){
		perror("Could not set env");
		return 1;
	}
	printf("PWD : %s\n", getenv("PWD"));
	return 0;
}   

int env(){

    int i;
    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n",environ[i]);
    return 1;
   
}

int quit(){
    return 0;
}

int clr(){
    int result = system("clear");
    if (result == -1) {
        perror("Error executing clear command");
        return 0; 
    } else {
        return 1; 
    }
}

int echo(char** args, char* output_file, int typeOfRedirection){
    //printf("hell");
    FILE *fp;

    const char *mode = (typeOfRedirection == 1) ? "w" : (typeOfRedirection == 2) ? "a" : "none";
    if(strcmp(mode, "none") == 0){
        int i = 1;
        while(args[i] != NULL && strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0){
            printf("%s ",args[i]);
            i++;
        }
        printf("\n");
        return 1;
    }

    fp = fopen(output_file, mode);
    if(fp == NULL){
        perror("fopen");
        return 0;

    }
    if (freopen(output_file,mode,stdout) == NULL){
        perror("freopen");
        return 1;
    }
    int i = 1;
    while(args[i] != NULL && strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0){
        printf("%s ",args[i]);
        i++;
    }
    printf("\n");
    fflush(stdout); // Flush any remaining output
        fclose(fp); // Close the output file
        // Redirect stdout back to the terminal
        if (freopen("/dev/tty", "a", stdout) == NULL) {
            perror("freopen");
            return 1; // Error restoring stdout
        }
    return 1;


    
    
}

int help(){

    return 0;
}


int pause(){
    printf("Press Enter to continue...\n");

    while (getchar() != '\n');

    printf("Continuing with shell operations...\n");


    return 1;

}






void display(){
    char * prompt = "==>";
    fputs(prompt, stdout);
}



char* readInput(){
    char* input = malloc(100); // Allocate memory for input buffer
    if (input == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    fgets(input, 100, stdin); // Read input
    printf("%s", input);
    return input;


}


char** parseInput(char* input){
    char **commands = NULL; //Array of Strings
	int wordCount = 0; //
    int bufferSize = 20;


		 // Allocate memory for the array of strings, mem can hel bufferSize num of strings
    commands = (char **)malloc(bufferSize * sizeof(char *));
    if (commands == NULL) {
        printf("Memory allocation failed!\n");
    	exit(1);
	}
		
		// Tokenize input and store in the array of strings
    char *token = strtok(input, " \t\n");
    while (token != NULL) {
        commands[wordCount] = strdup(token);
    	wordCount++;

        	// Check if we need to resize the buffer
        	if (wordCount >= bufferSize) {
            	bufferSize *= 2; // Double the buffer size
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

void checkForRedirection(char** args, char** input_file, char** output_file, int* typeOfRedirection) {
    *input_file = NULL;
    *output_file = NULL;

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


int forkAndExec(char** args, char* input_file, char* output_file){
    pid_t pid;
		int status;
		bool dont_wait = false;
		switch(pid = fork()){
			case -1:
				perror("fork");
			case 0:
				if(input_file[0] != '\0'){
					printf("%lu",strlen(input_file));
					//check if file exists
					if (access(input_file, F_OK) != -1) {
       					freopen(input_file, "r", stdin);
   					}else{ 
						printf("Input File does not exist");
						exit(1);
					}
				}
				if(strlen(output_file) > 0){
					//check if file exists
					if (access(output_file, F_OK) != -1) {
        				freopen(output_file, "w", stdout);
    				}else{ 
						printf("Ouput File does not exist");
						exit(1);
					}
				}
				//execvp used to execute file, commands[0] cotains name of file, commands is string array of args where 
				//commnads[0] is the name of the file.
				execvp(args[0],args);
                
					
			default:
				
			if(!dont_wait){
				waitpid(pid, &status, 0);
			}
            
		}
		wait(NULL);
        return 1;
}

int runCommand(char** args, char* input_file, char* output_file, int typeOfRedirection){

    if (!strcmp("clr",args[0])){
		return clr();	
	}
	else if(!strcmp("cd", args[0])){
		return cd(args[1]);
	}

	else if (!strcmp("dir", args[0])){
		return dir(args[1]);
	}
	else if (!strcmp("quit", args[0])){
		return quit();
	}
	else if (!strcmp("environ",args[0])){
		return env();
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
		return forkAndExec(args, input_file,output_file);
	}
    return 0;
}

