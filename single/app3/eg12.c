#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int extensionEquals(const char *left,const char *right)
{
char a,b;
while(*left && *right)
{
a=*left;
b=*right;
if(a>=65 && a<=90)a=a+32;
if(b>=65 && b<=90)b=b+32;
if(a!=b)return 0;
left++;
right++;
}
return *left==*right;
}
int main()
{
FILE *f;
f=fopen("marksSheet.sct","r");
string str;
char nm[22];
string str;
string s="";
int x,y,p,c,e,m,h,i;
char *a;
p=50;
c=40;
m=60;
e=76;
h=90;
cout<<p<<","<<c<<","<<m<<","<<e<<","<<h<<endl;
while(1)
{
fgets(nm,22,f);
s="";
a=(char *)malloc(sizeof(char)*10);
nm[strlen(nm)-1]='\0';
cout<<"Value of nm: "<<nm<<endl;
for(x=0;x<strlen(nm);x++)
{
str="";
if(nm[x]=='$')
{
i=x+2;
while(nm[i]!='}')
{
str+=nm[i];
i++;
}
cout<<"Value of str: "<<str<<endl;
if(extensionEquals(str.c_str(),"physics"))
{
sprintf(a,"%d ",p);
s+=string(a);
}
if(extensionEquals(str.c_str(),"chemistry"))
{
sprintf(a,"%d ",c);
s+=string(a);
}
if(extensionEquals(str.c_str(),"maths"))
{
sprintf(a,"%d ",m);
s+=string(a);
}
if(extensionEquals(str.c_str(),"english"))
{
sprintf(a,"%d ",e);
s+=string(a);
}
if(extensionEquals(str.c_str(),"hindi"))
{
sprintf(a,"%d ",h);
s+=string(a);
}

delete []a;
x=i;
}// if ends(nm[x]=='$')
else
{
s+=string(a);
}
}//for loop ends
cout<<"Value of s: "<<s<<endl;
if(feof(f))break;
}//while loop ends
return 0;
}