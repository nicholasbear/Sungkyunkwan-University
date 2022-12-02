#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 5000
#define MAX_LEN 400
extern FILE *stdin;
extern FILE *stdout;

char str[MAX_SIZE][MAX_LEN];

//alternative for strcmp : only compare digit and alphabet(case-insensitive)
int cmp(const void *fi, const void *se)
{
	char *f = (char*) fi;
	char *s = (char*) se;
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
	char buf[MAX_LEN];
	FILE *fp, *out;
	int i,j;

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

	for(i=0;fgets(buf, MAX_LEN, fp)!=NULL;i++)
		strcpy(str[i],buf);
	qsort(str, i, sizeof(char)*MAX_LEN, cmp);

	
	for(j=0;j<i;j++)
		fprintf(out,"%s",str[j]);

	return 0;
}
