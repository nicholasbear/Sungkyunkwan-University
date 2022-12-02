#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define N (10)

pid_t pid[N];
int ccount=0;

void handler(int sig){
	pid_t id=wait(NULL);
	ccount--;
	printf ("Received signal %d from pid %d\n",sig,id);
	if(waitpid(pid[i],NULL,WNOHANG){
		if pid==0
			kill(pid_t pid,SIGINT)
	}
}


int main(){
	int i;
	ccount=N;
	signal (SIGCHLD,handler);
	for(i=0;i<N;i++){
		if((pid[i]=fork())==0){
			exit(0);
		}
	}

	while(ccount>0)
	sleep(5);

	return 0;
}
