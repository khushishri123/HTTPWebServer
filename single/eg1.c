#include<stdio.h>
int main()
{
FILE *f;
char g;
int cnt,length;
int backSlashnCnt;
f=fopen("index.html","rb");
fseek(f,0,2); //move to end
length=ftell(f);
printf("%d\n",length);
fseek(f,0,0);
cnt=0;
backSlashnCnt=0;
while(1)
{
g=fgetc(f);
if(feof(f))break;
if(g=='\n')backSlashnCnt++;
printf("%c",g);
cnt++;
}
fclose(f);
printf("\n");
printf("%d\n",cnt);
printf("\\n count: %d\n",backSlashnCnt);
return 0;
}