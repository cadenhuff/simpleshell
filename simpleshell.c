#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_ARGS  64
#define SEPERATORS  " \t\n"
#define BUFFER_SIZE  20 //Inital buffer size



extern char **environ;

//Should all funcs be split into seperate files

int clr(void){
	system("clear");
	return 0;	
}

int dir(char directory[]){
	//Lists directory contents
	if(strlen(directory) > 0){
		char command[100];
                sprintf(command, "ls -al %s", directory);
                system(command);
	
	}else{
		system("ls -al");
	}
	
	return 0;
}


int env(void){
	return 0;
}

int quit(void){
	exit(0);
	return 0;
}




int main(int argc, char *argv[]){
	
	char * prompt = "==>";
	//Command max 100 chars

	//Clean this section up, IDK if I need all this, or I think there is a better way to write these vars will the use of the constants
	char input[200]; 
	char command[100];
	char directory[100];
	int bufferSize = BUFFER_SIZE;
	
	bool input_redirection = false;
	bool output_redirection = false;

	char input_file[200];
	char output_file[200];

	while (!feof(stdin)){
		
		//Writes prompt to stdout
		fputs(prompt, stdout);
	
		//Read one word command from stdin and stores in str
	
		fgets(input, sizeof(input), stdin);

		char **commands; //Array of Strings
		int wordCount = 0; //


		 // Allocate memory for the array of strings, mem can hel bufferSize num of strings
    	commands = (char **)malloc(bufferSize * sizeof(char *));
    	if (commands == NULL) {
        	printf("Memory allocation failed!\n");
        	exit(1);
    	}
		
		// Tokenize input and store in the array of strings
    	char *token = strtok(input, " \t\n");
		bool next_word_is_inputfile = false;
		bool next_word_is_outputfile = false;
    	while (token != NULL) {
        	// Allocate memory for the new string and copy input
			commands[wordCount] = strdup(token);
        	if (commands[wordCount] == NULL) {
            	printf("Memory allocation failed!\n");
            	exit(1);
        	}
        	if (input_redirection) {
            	strcpy(input_file, token);
            	input_redirection = false; // Reset the flag
        	}

        	if (output_redirection) {
            	strcpy(output_file, token);
            	output_redirection = false; // Reset the flag
        	}

        	if (!strcmp("<", token)) {
            	input_redirection = true;
        	}

        	if (!strcmp(">", token) || !strcmp(">>", token)) {
            	output_redirection = true;
        	}


        	wordCount++;

        	// Check if we need to resize the buffer
        	if (wordCount >= bufferSize) {
            	bufferSize *= 2; // Double the buffer size
            	commands = realloc(commands, bufferSize * sizeof(char *));
            	if (commands == NULL) {
                	printf("Memory allocation failed!\n");
                	exit(1);
            	}
        	}

        	// Get the next token
        	token = strtok(NULL, " \t\n");
    	}

    	// Print the stored strings
    	printf("Strings stored:\n");
    	for (int i = 0; i < wordCount; i++) {
        	printf("%s\n", commands[i]);
    	}

		printf("%s\n",output_file);
		printf("%s\n",input_file);



		//Change this logic to switch block
		if (!strcmp("clear",commands[0])){
			clr();	
		}

		else if (!strcmp("dir", commands[0])){
			dir(directory);
		}
		else if (!strcmp("quit", commands[0])){
			quit();
		}
		else if (!strcmp("environ",commands[0])){
			env();
		}
		else{
			pid_t pid;
			int status;
			bool dont_wait = false;
			switch(pid = fork()){
				case -1:
					perror("fork");
				case 0:
					//execvp used to execute file, commands[0] cotains name of file, commands is string array of args where 
					//commnads[0] is the name of the file.
					execvp(commands[0],commands);
					
				default:
					
				if(!dont_wait){
					waitpid(pid, &status, 0);
				}

			}
			wait(NULL);

		}
		//free commands from memory after running
		free(commands);
	}

}
