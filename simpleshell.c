#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int clr(void){
	system("clear");
	return 0;	
}







int main(int argc, char *argv[]){
	
	char * prompt = "==>";
	char str[100];
	fputs(prompt, stdout);
	fgets(str, sizeof(str), stdin);
	
	if (strcmp("clear",str) != 0){
		clr();	
	}

	

}



