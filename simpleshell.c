#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int clr(void){
	system("clear");
	return 0;	
}

int dir(void){
	system("ls -al");
	return 0;
}

int environ(void){
	return 0;
}

int quit(void){
	return 0;
}




int main(int argc, char *argv[]){
	
	char * prompt = "==>";
	

	//Command 
	char str[100];

	//Writes prompt to stdout
	fputs(prompt, stdout);

	//Reads prompt from stdin and stores in str
	fgets(str, sizeof(str), stdin);
	
	if (strcmp("clear",str) != 0){
		clr();	
	}

	if (strcmp("dir", str) != 0){
		//Need to somehow get the argument 
		dir();
	}

	

}
