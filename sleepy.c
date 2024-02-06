#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
unsigned int seconds;

void sighandler(int signum){
	printf("Recieved a signal %d\n",signum);
	int pid = getpid();
	kill(pid, SIGTERM);

}





int main(void){
	signal(SIGINT, sighandler);
	printf("Type a number: ");
	scanf("%d", &seconds);

	for(int i = 0; i<seconds; i++){
		int pid = getpid();
		printf("Pid is %d\n",pid);
		fflush(stdout);
		int remaining;
		remaining = sleep(5);
		printf("remaining time %d\n",remaining);
				
		
		
	}
	

	return 0;


}
