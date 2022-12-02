#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


int main(void){

	sigset_t sigset;
	int ndx;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGINT);

	printf("Enter CTRL+C\n");

	sigprocmask(SIG_UNBLOCK,&sigset,NULL);
	if(read(SIGINT)){
	for(ndx=5;0<ndx;ndx--){
		printf("Beep\n");
		sleep(1);
	}
	printf("I'm Alive");
	}
return 0;
}
