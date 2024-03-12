#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>



int cd(char directory[]){
	//Might want to add functionality for the ~, (.. does work but not ~)


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