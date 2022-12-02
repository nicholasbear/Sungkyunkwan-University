#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char* argv[]){

char buff[1];
int fp;
int wordcount=0;
int mode=0;
int chapter=0;
int verse=0;
int a=0,b=0,c=0;
int lastspace=0;

	fp=open(argv[1],O_RDONLY,0755);


while(read(fp,buff,1) > 0){
if(mode==0&&buff[0]==':'){
	mode=1;
	chapter+=a;
	a=0;
	}
else if(mode==1&&buff[0]==':'){
	mode=2;
	verse+=b;
	b=0;
	}
else if(mode==2&&buff[0]=='\n'){
	mode=0;
	wordcount+=c;
	c=0;
	}


else if(mode==0&&buff[0]>='0'&&buff[0]<='9'){
	a*=10;
	a+=buff[0]-'0';
}
else if(mode==1&&buff[0]>='0'&&buff[0]<='9'){
	b*=10;
	b+=buff[0]-'0';
}
else if(mode==2&&buff[0]==' '){
	if(lastspace==1){
		c;
	}
	else if(lastspace==0){
		c++;
	}
}
if(lastspace==1&&buff[0]=='\n'){
	c--;
}
		
if(buff[0]==' '){
	lastspace=1;
	}
else{
	lastspace=0;
}


}

printf("%d     ",chapter);
printf("%d     ",verse);
printf("%d     ",wordcount);


close(fp);

return 0;
}
