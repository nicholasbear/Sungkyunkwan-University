/*-----------------------------------------------------------
*
* SWE2007: System Software Experiment 2 (Fall 2018)
*
* Skeleton code for PA#1
*
* October 날짜, 2018.
* Sungkyunkwan University
*
* Student Id   :
* Student Name :
*
*-----------------------------------------------------------
*/


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Word {
	char data[20];
	struct Word *next;
	struct Place *placehead;
}Word;


struct Place {
	int chapter;
	int verse;
	int num; //줄안에서의 위치
	struct Place *next;
}Place;

struct WordList {
	Word* head;
	Word* tail;
	Word* cur;
}WList;

struct PlaceList {
	Place* head;
	Place* cur;
	Place* tail;
}PList;

void ClearList(List*a) {
	a->head = (word*)malloc(sizeof(Word));
	a->head->next = NULL;
	a->tail = a->head;
}

void addWord(WordList*tail, char* arr) {
	Newword = (Word*)malloc(sizeof(Word));
	Newword.data= arr;
	WordList->tail->next=Newword;
	Newword->next = NULL;
	WordList->tail = Newword;
}

void addPlace(PlaceList *tail, int chapter, int verse, int num) {
	Place*Newplace = (Place*)malloc(sizeof(Place*));
	Place*Newplace.chapter = chapter;
	Place*Newplace.verse = verse;
	Place*Newplace.num = num;
	PlaceList->tail->next=Newplace;
	PlaceList->tail = Newplace;
	Newplace->next = NULL;
}

Word* Findword(WordList, char* word) {
	WordList->cur = Wordlist->head;
	whie(strcmp(WordList->cur,word)!=0) {
		WordList->cur == WordList->cur * next;
		if (WordList->cur->next = NULL) {
			return 0;
		}
	}
	if (strcmp(WordList->cur, word)==0) {
		return word;
	}
}




void indexBuilder(const char* inputFileNm, const char* indexFileNm)
{
	char buff[1];
	char line[N];
	int mode == 0;
	int a = 0, b = 0, c = 0;//index위치정보
	char arr[20];//단어 세는거
	int i = 0;
	int chapter = 0, verse = 0, wordcount = 0;//총합

	fp = open(argv[1], O_RDONLY, 0755);

	ClearList(WordList);

	while (read(fp, buff, 1) > 0) {
		if (mode == 0 && buff[0] == ':') {
			mode = 1;
			chapter += a;
			a = 0;
		}
		else if (mode == 1 && buff[0] == ':') {
			mode = 2;
			verse += b;
			b = 0;
		}
		else if (mode == 2 && buff[0] == '\n') {
			mode = 0;
			wordcount += c;
			c = 0;
		}


		else if (mode == 0 && buff[0] >= '0'&&buff[0] <= '9') {
			a *= 10;
			a += buff[0] - '0';
		}
		else if (mode == 1 && buff[0] >= '0'&&buff[0] <= '9') {
			b *= 10;
			b += buff[0] - '0';
		}
		else if (mode == 2 && buff[0] == ' ') {
			if (i != 0) {
				arr[i] = '\0'; //단어가 끝났으므로 스트링의 끝을 알린다.
			}
			i = 0; //단어를 읽기위해


			if (Findword == NULL) { //단어가 저장 안되있으면 추가
				addWord(WordList, arr);
				addPlace(PlaceList, a, b, c);
			}
			else {//단어가 저장되어있으면 위치정보만 추가
				addPlace(PlaceList, a, b, c);
			}


			if (lastspace == 1) {
				c;
			}
			else if (lastspace == 0) {
				c++;
			}
		}
		else if (mode == 2 && buff[0] != ' ') {
			arr[i] = buff[0];
			i++;
		}

		if (buff[0] == ' ') {
			lastspace = 1;
		}
		else {
			lastspace = 0;
		}


	}

	return 0;
}