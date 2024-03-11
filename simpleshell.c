#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;



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
	char input[200]; 
	char command[100];
	char directory[100];
	while (!feof(stdin)){
		//Writes prompt to stdout
		fputs(prompt, stdout);

		//Read one word command from stdin and stores in str
	
		fgets(input, sizeof(input), stdin);

  		// Parse input to extract command and directory
    		sscanf(input, "%s %s", command, directory);

		//Change this logic to switch block
		if (!strcmp("clear",command)){
			clr();	
		}

		else if (!strcmp("dir", command)){
			
			dir(directory);
		}
		else if (!strcmp("quit", command)){
			quit();
		}
		else if(!strcmp("cd", command)){
			cd(directory);
		}
		else{
			system(command);
		}
	}

}
