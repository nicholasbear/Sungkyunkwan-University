
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void indexPrinter(const char* indexFileNm, const char* outputFileNm)
{
	int fp;
	int fw;
	int fp1;
	char buff[1];
	int mode=0;	
	int a=0;
	int b=0;
	int c=0, chapter=0, d=0;
	int verse1[100]={0};
	int verse=0;
	char buf[2]={' ','\n'};


	fp = open(indexFileNm, O_RDONLY, 0755);
	fw = open(outputFileNm,O_RDWR | O_CREAT,0755);
		
	while(read(fp,buff,1)>0){
		if(buff[0]=='.'){
			b++;
		}
		if(buff[0]==','){
			a++;
		}

		if(mode==0&&buff[0]==':'){
			mode=1; 
		}
		else if(mode==1){
			if(buff[0]==','){
				mode=2;
			}
			
		}
		else if(mode==2){
			if(buff[0]==':'){
				mode=3;
			}
			if(buff[0] >= '0'&&buff[0] <= '9'){
				c*=10;
				c+=buff[0]-'0';
			}
				
		}
		else if(mode==3){
			if(c>chapter){
				chapter=c;
			}		
			if(buff[0]==':'){
				mode=4;
			}
			if(buff[0] >= '0'&&buff[0] <= '9'){
				d*=10;
				d+=buff[0]-'0';
			}
		}
		else if(mode==4){
			if(d>verse1[c]){
				verse1[c]=d;
			}
			c=0; d=0;
			if(buff[0]=='.'){
				mode=0; 
			}
			else if(buff[0]==','){
				mode=2;
			}
		}

	} 

	for(int i=1;i<chapter+1;i++){
		verse+=verse1[i];
	}

char chapter1[2];
char verse2[4];
char index[4];
char word[5];

chapter1[0]=chapter/10+'0'; chapter1[1]=chapter%10+'0';
verse2[0]=verse/1000+'0'; verse2[1]=verse%1000/100+'0'; verse2[2]=verse%100/10+'0'; verse2[3]=verse%10+'0';
index[0]=b/1000+'0'; index[1]=b%1000/100+'0'; index[2]=b%100/10+'0'; index[3]=b%10+'0';
word[0]=a/10000+'0'; word[1]=a%10000/1000+'0'; word[2]=a%1000/100+'0'; word[3]=a%100/10+'0'; word[4]=a%10+'0';

int idx=0;

while(indexFileNm[idx]!='\0'){
	idx++;
}	
write(fw,indexFileNm,sizeof(char)*(idx-6));		
write(fw,chapter1,sizeof(char)*2); write(fw,buf,sizeof(char));
write(fw,verse2,sizeof(char)*4); write(fw,buf,sizeof(char));
write(fw,index,sizeof(char)*4);	write(fw,buf,sizeof(char));	
write(fw,word,sizeof(char)*5); write(fw,buf,sizeof(char)*2);

close(fp);
fp1 = open(indexFileNm, O_RDONLY, 0755);
while(read(fp,buff,1)>0){
	write(fw,buff,sizeof(char));
}		

close(fp1);
close(fw);

}


