#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int clr(void){
	system("clear");
	return 0;	
}

int dir(char directory[]){
	
	if(strlen(directory) > 0){
		char command[100];
                sprintf(command, "ls -al %s", directory);
                system(command);
	
	}else{
		system("ls -al");
	}
	
	return 0;
}

int environ(void){
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


		if (!strcmp("clear",command)){
			clr();	
		}

		else if (!strcmp("dir", command)){
			
			dir(directory);
		}
		else if (!strcmp("quit", command)){
			quit();
		}
		else{
			system(command);
		}
	}

}
