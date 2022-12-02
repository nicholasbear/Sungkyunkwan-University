#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZEMAX 500

extern FILE *stdin;
extern FILE *stdout;

typedef struct Link{
	char data[SIZEMAX];
	struct Link *next;
} lnk;

//alternative for strcmp : only compare digit and alphabet(case-insensitive)
int cmp(char *f, char *s)
{
	int i=0, j=0;
	while(f[i]*s[j]!=0)
		if(!isalpha(f[i]) && !isdigit(f[i]))
			i++;
		else if(!isalpha(s[j]) && !isdigit(s[j]))
			j++;
		else if(toupper(f[i])==toupper(s[j]))
		{
			i++;
			j++;
		}
		else
			break;
	return toupper(f[i])-toupper(s[j]);
}

int main(int argc, char *argv[])
{
	char buf[SIZEMAX];
	lnk *lp, *h, *tmp;
	FILE *fp, *out;

	if(argc==1)
	{
		fp = stdin;
		out = stdout;
	}
	else if(argc==2)
	{
		fp = fopen(argv[1],"r");
		out = stdout;
	}
	else if(argc==3)
	{
		fp = fopen(argv[1],"r");
		out = fopen(argv[2],"w");
	}
	else
	{
		printf("argument error!!!");
		return -1;
	}

	h = (lnk*)malloc(sizeof(lnk));
	h->data[0] = 0;
	h->next = (lnk*)malloc(sizeof(lnk));

	fgets(buf, SIZEMAX, fp);
	strcpy(h->next->data, buf);
	h->next->next = NULL;

	while(fgets(buf, SIZEMAX, fp) != NULL)
	{
		lp = h;
		
		while(lp->next != NULL)
		{
			if(cmp(lp->next->data,buf)<0)
				lp = lp->next;
			else
				break;
		}
		
		tmp = (lnk*)malloc(sizeof(lnk));
		strcpy(tmp->data,buf);
		tmp->next = lp->next;
		lp->next = tmp;
	}
	
	lp = h;
	while(lp != NULL)
	{
		fprintf(out,"%s",lp->data);
		lp=lp->next;
	}
	return 0;
}
