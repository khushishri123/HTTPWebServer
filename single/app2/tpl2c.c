#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int size,char *targetFiles[])
{
char s[1024],t[1024],p[1024];
char g,a;
char *c,*jk,*d;
FILE *f;
FILE *k;
int j,m,n,i,len,x,l,h;
f=fopen("tpl.h","w");
strcpy(s,"#ifndef ___TPL\n#define ___TPL\n#include<tmwp>\nusing namespace tmwp;\n");
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],f);
}
for(m=1;m<size;m++)
{

x=strlen(targetFiles[m]); 
jk=(char *)malloc(sizeof(char)*x);
strcpy(jk,targetFiles[m]);
d=(char *)malloc(sizeof(char)*(x+3)); // +3 for get (getErrorPage_TPL)
strcpy(d,"get");
n=3;
l=0;
while(1)
{
if(jk[l]=='.')break;
d[n]=jk[l];
n++;
l++;
}
d[n]='\0';
strcat(d,"_"); 
strcat(d,"TPL"); 
sprintf(s,"void %s(Request &request,Response &response);\n",d);
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],f);
}
free(jk);
free(d);
}

strcpy(s,"void registerTPLs(TMWebProjector *server)\n{\n");
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],f);
}
for(m=1;m<size;m++)
{
x=strlen(targetFiles[m]); 
jk=(char *)malloc(sizeof(char)*x);
strcpy(jk,targetFiles[m]);
d=(char *)malloc(sizeof(char)*(x+3)); // +3 for get (getErrorPage_TPL)
strcpy(d,"get");
n=3;
l=0;
while(1)
{
if(jk[l]=='.')break;
d[n]=jk[l];
n++;
l++;
}
d[n]='\0';
strcat(d,"_"); 
strcat(d,"TPL"); 
sprintf(s,"server->onRequest(\"/%s\",%s);\n",jk,d);
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],f);
}
free(jk);
free(d);
}
fputc('}',f);
fputc('\n',f);
strcpy(s,"#endif");
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],f);
}
fclose(f);
for(m=1;m<size;m++)
{
f=fopen(targetFiles[m],"r");
if(f==NULL)continue;
x=strlen(targetFiles[m]); 
jk=(char *)malloc(sizeof(char)*x);
strcpy(jk,targetFiles[m]);

c=(char *)malloc(sizeof(char)*(x+9)); // 9 for .tpl.cpp
strcpy(c,targetFiles[m]);
strcat(c,".cpp");
d=(char *)malloc(sizeof(char)*(x+3)); // +3 for get (getErrorPage_TPL)
strcpy(d,"get");
n=3;
l=0;
while(1)
{
if(jk[l]=='.')break;
d[n]=jk[l];
n++;
l++;
}
d[n]='\0';
strcat(d,"_"); 
strcat(d,"TPL"); 
k=fopen(c,"w");
if(f==NULL)
{
sprintf(s,"#include<tmwp>\nusing namespace tmwp;\nvoid %s(Request &request,Response &response)\n{\n}",d);
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],k);
}
fclose(f);
fclose(k);
free(jk);
free(d);
continue;
}
sprintf(s,"#include<tmwp>\nusing namespace tmwp;\nvoid %s(Request &request,Response &response)\n{\n",d);
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],k);
}


while(1)
{
g=fgetc(f);
if(feof(f))break;
if(g!='$')strcpy(t,"response.write(\"");
else strcpy(t,"response.write(request.getKeyValue(\"");
len=strlen(t);
for(i=0;i<len;i++)
{
fputc(t[i],k);
}
if(g=='"')
{
fputc('\\',k);
}
if(g=='\n')
{
fputc('\\',k);
fputc('n',k);
}
else 
{
if(g!='$')fputc(g,k);
else
{
a=fgetc(f); // for 2nd $
while(a=='\n')a=fgetc(f);
a=fgetc(f); //for 3rd $
while(a=='\n')a=fgetc(f);
a=fgetc(f); //for {
while(a=='\n')a=fgetc(f);
a=fgetc(f);
while(a=='\n')a=fgetc(f);
i=0;
while(a!='}')
{
p[i]=a;
i++;
a=fgetc(f);
while(a=='\n')a=fgetc(f);
}
p[i]='\0';
len=strlen(p);
for(i=0;i<len;i++)fputc(p[i],k);
}
}
a='"';
fputc(a,k);
fputc(')',k);
if(g=='$')fputc(')',k);
fputc(';',k);
fputc('\n',k);
}

strcpy(s,"response.close();");
len=strlen(s);
for(i=0;i<len;i++)
{
fputc(s[i],k);
}
fputc('\n',k);
fputc('}',k);
fclose(f);
fclose(k);
free(c);
free(d);
} //for loop ended
printf("Code completed\n");
return 0;
}