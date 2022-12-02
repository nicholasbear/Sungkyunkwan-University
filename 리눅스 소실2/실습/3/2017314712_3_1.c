#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int monthold=0;
	int i;
	pid_t pid=fork();
	
	printf("Input number: ");
	scanf("%d",&monthold);
	
	if(pid==0){
		printf("These rabbits are new borns");
		}
	else{
	 for(i=1;i<monthold+1;i++){
		 if(i>1){
			fork();
			}

		 printf("These rabbits are %d-month old\n",i);
	 }
	}

return 0;
}
