
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct Word {
	char* data;
	struct Word *next;
	struct PlaceList* pList;
}Word;


typedef struct Place {
	int chapter;
	int verse;
	int num;
	struct Place *next;
}Place;

typedef struct WordList {
	Word* head;
	Word* tail;
	Word* cur;
}WList;

typedef struct PlaceList {
	Place* head;
	Place* cur;
	Place* tail;
	int numofdata;
}PList;

void copystring(char* s1,char* s2){
	int idx=0;
	while(s2[idx]!='\0'){
		s1[idx]=s2[idx];
		idx++;
	}
}

void addWord(WList* wlist,char* arr, int arrLen) {
	Word* Newword = (Word*)malloc(sizeof(Word));
	Newword->data=(char*)malloc(arrLen * sizeof(char));
	copystring(Newword->data,arr);
	Newword->pList=(PList*)malloc(sizeof(PList));
	Newword->pList->head=NULL;
	Newword->pList->cur=NULL;
	Newword->pList->tail=NULL;
	Newword->pList->numofdata=0;
	if(wlist->tail==NULL){
		wlist->head=Newword;
		wlist->tail=Newword;
		wlist->tail->next=NULL;
	}
	else{
		wlist->tail->next=Newword;
		Newword->next = NULL;
		wlist->tail = Newword;
	}
}

void addPlace(PList* plist,int chapter, int verse, int num) {
	Place* Newplace = (Place*)malloc(sizeof(Place));
	Newplace->chapter = chapter;
	Newplace->verse = verse;
	Newplace->num = num;
	if(plist->head==NULL){
		plist->head=Newplace;
		plist->tail=Newplace;
		plist->numofdata=1;
	}
	else{
	plist->tail->next=Newplace;
	plist->tail = Newplace;
	Newplace->next = NULL;
	(plist->numofdata)++;
	}
}
int Isstringsame(char* s1,char* s2){
	int idx=0;
	
	while(s1[idx]!='\0'||s2[idx]!='\0'){
		if(s1[idx]!=s2[idx]){
			return 0;
		}
		else{
			idx++;
		}	
	}
	if(s1[idx]=='\0'||s2[idx]=='\0'){
			if(s1[idx]=='\0'&&s2[idx]=='\0'){
				return 1;
			}
			else
				return 0;
	}
	else
		return 0;
			
	
}

int Findword(WList* wlist,char* word) {
	if(wlist->head==NULL){
		return 0;
	}
	else{
		wlist->cur = wlist->head;
		while(Isstringsame(wlist->cur->data,word)==0) {
			if (wlist->cur->next == NULL) {
				return 0;
			}
			wlist->cur = wlist->cur->next;
		}
		if (Isstringsame(wlist->cur->data, word)==1) {
		
			return 1;
		}
		else
			return 0;
	}
}

void WriteList(WList* wlist,int fw){
	int idx=0;
	char buff[2]={'.','\n'};
	char buf[1]={':'};
	char bufff[2]={',',' '};
	char jang[3];
	char jul[3];
	char whichi[3];
	char numofword[4];
	int a=0,b=0,c=0,d=0;
	wlist->cur=wlist->head;

	while(wlist->cur!=NULL){
		wlist->cur->pList->cur=wlist->cur->pList->head;
		while(wlist->cur->data[idx]!='\0'){
			idx++;
		}
		write(fw,wlist->cur->data,sizeof(char)*(idx));
		write(fw,buf,sizeof(char));
			
			if(wlist->cur->pList->numofdata<10){
				numofword[0]=(wlist->cur->pList->numofdata)%10+'0';
				d=1;
			}
			else if(wlist->cur->pList->numofdata<100){
				numofword[0]=(wlist->cur->pList->numofdata)/10+'0';
				numofword[1]=(wlist->cur->pList->numofdata)%10+'0';
				d=2;
			}
			else if(wlist->cur->pList->numofdata<1000){
				numofword[0]=(wlist->cur->pList->numofdata)/100+'0';
				numofword[1]=(wlist->cur->pList->numofdata)%100/10+'0';
				numofword[2]=(wlist->cur->pList->numofdata)%10+'0';
				d=3;
			}
			else if(wlist->cur->pList->numofdata<10000){
			numofword[0]=(wlist->cur->pList->numofdata)/1000+'0';
			numofword[1]=((wlist->cur->pList->numofdata)%1000)/100+'0';
			numofword[2]=((wlist->cur->pList->numofdata)%100)/10+'0';
			numofword[3]=(wlist->cur->pList->numofdata)%10+'0';
			d=4;
			}

		write(fw,numofword,sizeof(char)*d); write(fw,bufff,sizeof(char)*2);
		
		while(wlist->cur->pList->cur!=NULL){
			if(wlist->cur->pList->cur->chapter<10){
				jang[0]=(wlist->cur->pList->cur->chapter)%10+'0';
				a=1;
			}
			else if(wlist->cur->pList->cur->chapter<100){
				jang[0]=(wlist->cur->pList->cur->chapter)/10+'0';
				jang[1]=(wlist->cur->pList->cur->chapter)%10+'0';
				a=2;
			}
			else if(wlist->cur->pList->cur->chapter<1000){
				jang[0]=(wlist->cur->pList->cur->chapter)/100+'0';
				jang[1]=((wlist->cur->pList->cur->chapter)%100)/10+'0';
				jang[2]=(wlist->cur->pList->cur->chapter)%10+'0';
				a=3;
			}

			if(wlist->cur->pList->cur->verse<10){
				jul[0]=(wlist->cur->pList->cur->verse)%10+'0';
				b=1;
			}
			else if(wlist->cur->pList->cur->verse<100){
				jul[0]=(wlist->cur->pList->cur->verse)/10+'0';
				jul[1]=(wlist->cur->pList->cur->verse)%10+'0';
				b=2;
			}
			else if(wlist->cur->pList->cur->verse<1000){
				jul[0]=(wlist->cur->pList->cur->verse)/100+'0';
				jul[1]=((wlist->cur->pList->cur->verse)%100)/10+'0';
				jul[2]=(wlist->cur->pList->cur->verse)%10+'0';
				b=3;
			}

			if(wlist->cur->pList->cur->num<10){
				whichi[0]=(wlist->cur->pList->cur->num)%10+'0';
				c=1;
			}
			else if(wlist->cur->pList->cur->num<100){
				whichi[0]=(wlist->cur->pList->cur->num)/10+'0';
				whichi[1]=(wlist->cur->pList->cur->num)%10+'0';
				c=2;
			}
			else if(wlist->cur->pList->cur->chapter<1000){
				whichi[0]=(wlist->cur->pList->cur->num)/100+'0';
				whichi[1]=((wlist->cur->pList->cur->num)%100)/10+'0';
				whichi[2]=(wlist->cur->pList->cur->num)%10+'0';
				c=3;
			}
			
			if(wlist->cur->pList->cur->next==NULL){			
				write(fw,jang,sizeof(char)*a);     write(fw,buf,sizeof(char)*1);
				write(fw,jul,sizeof(char)*b);      write(fw,buf,sizeof(char)*1);
				write(fw,whichi,sizeof(char)*c);   write(fw,bufff+1,sizeof(char)*1);
			}
			else{			
				write(fw,jang,sizeof(char)*a);     write(fw,buf,sizeof(char)*1);
				write(fw,jul,sizeof(char)*b);      write(fw,buf,sizeof(char)*1);
				write(fw,whichi,sizeof(char)*c);   write(fw,bufff,sizeof(char)*2);
			}

			for(int j=0;j<4;j++){
				numofword[j]='\0';
			}
			for(int i=0;i<3;i++){
				jang[i]='\0'; jul[i]='\0'; whichi[i]='\0';
			}
			
			wlist->cur->pList->cur=wlist->cur->pList->cur->next;	
		}	

		
		write(fw,buff,sizeof(char)*2);
		wlist->cur = wlist->cur->next;
		idx=0;
	
	
	}
}



void indexBuilder(const char* inputFileNm,const char* indexFileNm)
{
	int fp;
	int fw;
	char buff[1];
	int mode = 0;
	int a = 0, b = 0, c = 0; 
	char arr[20];
	int i = 0;
	int chapter = 0, verse = 0;
	WList*wlist=(WList*)malloc(sizeof(WList));

wlist->head=NULL;
wlist->tail=NULL;
wlist->cur=NULL;
	fp = open(inputFileNm, O_RDONLY, 0755);
	fw = open(indexFileNm,O_RDWR | O_CREAT,0755);

	while (read(fp, buff, 1) >0) {

		if (mode == 0) {
			if(buff[0] == ':'){
				mode =1;
				chapter=a;
				a=0;
			}
			if(buff[0] >= '0'&&buff[0] <= '9'){
				a*=10;
				a+=buff[0] - '0';
			}
		}

		else if (mode == 1) {
			if(buff[0] == ':'){
				mode = 2;
				verse=b;
				b=0;
			}
			if(buff[0] >= '0'&&buff[0] <= '9'){
				b *= 10;
				b += buff[0] - '0';
			}
		}

		else if (mode == 2) {
			c++;
			if((buff[0]>='a' && buff[0]<='z') || (buff[0]>='A' && buff[0] <='Z')||buff[0]==39||buff[0]=='-'){
				if(buff[0]>='A' && buff[0] <='Z'){
					buff[0]=buff[0]-('A'-'a');
					arr[i] = buff[0];
					i++;
				}
				
				else{
					arr[i] = buff[0];
					i++;
				}
			}
			else{
				if(buff[0] == '\n'){
				mode = 0;
				c = 0;
				}

				else{
					if(i != 0) {
					arr[i] ='\0'; 
			
						if (Findword(wlist,arr) == 0) {
							addWord(wlist,arr,i); 
							addPlace(wlist->tail->pList,chapter, verse, c-i-2);
						}
						else {
							addPlace(wlist->cur->pList,chapter, verse, c-i-2);
						}	
						for(int e=0;e<20;e++){
							arr[e]='\0';
						}
						i=0;
					}
				}
	
			}
		}
	}

WriteList(wlist,fw);

close(fp);
close(fw);
	
}











