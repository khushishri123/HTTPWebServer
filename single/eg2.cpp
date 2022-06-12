//Assignment 1 Submitted by me
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct _request
{
char * method;
char * resource;
char isClientSideTechnologyResource;
char *mimeType;
}REQUEST;
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
char * getMIMEType(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
if(len<4)return mimeType;
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.')lastIndexOfDot--;
if(lastIndexOfDot==0)return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
return mimeType;
}
char isClientSideResource(char *resource)
{
return 'Y'; //this has to be changed later on
}
REQUEST * parseRequest(char *bytes)
{
char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++)method[i]=bytes[i];
method[i]='\0';
i+=2;//One for space and one for front slash
for(j=0;bytes[i]!=' ';i++,j++)resource[j]=bytes[i];
resource[j]='\0';
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc((sizeof(char)*strlen(resource))+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
return request;
}
int main()
{
char responseBuffer[1025];//A chunk of 1024 +1 for string terminator
char requestBuffer[8193];//1024*8 =8192
char header[5000];
int y;
long k;
int serverSocketDescriptor;
int clientSocketDescriptor;
int len,successCode;
int bytesExtracted;
char *req;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
WSADATA wsaData;
WORD ver;
ver=MAKEWORD(1,1);
//initialising the socket
WSAStartup(ver,&wsaData);
//Creating socket 
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create the socket");
return 0;
}
//filling all the necessary information on the structure
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);

//binding the socket with IP and Port Number
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind socket to port 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TMServer is ready to accept request on port 5050\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept Client Connection");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,8192,0);
if(bytesExtracted<0)
{
//what to do is yet to be decided
}else
if(bytesExtracted==0)
{
//what to do is yet to be decided
}
else
{
requestBuffer[bytesExtracted]='\0';
printf("Request : %s\n",requestBuffer);
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource)
{
FILE *f=fopen("index.html","rb");
if(f==NULL)//if index.html does not exists
{
f=fopen("index.htm","rb");
if(f==NULL)//if index.htm does not exists
{
strcpy(responseBuffer,"<!DOCTYPE HTML>");
strcat(responseBuffer,"<html lang='en'>");
strcat(responseBuffer,"<head>");
strcat(responseBuffer,"<meta charset='utf-8'>");
strcat(responseBuffer,"<title>ERROR</title>");
strcat(responseBuffer,"</head>");
strcat(responseBuffer,"<body>");
strcat(responseBuffer,"<h1>ERROR 404</h1>");
strcat(responseBuffer,"</body>");
strcat(responseBuffer,"</html>");

strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
strcat(header,"Content-Length: ");
char responseLength[11];
sprintf(responseLength,"%d\n",(strlen(responseBuffer)+1));
strcat(header,responseLength);
strcat(header,"\n");
successCode=send(clientSocketDescriptor,header,strlen(header)+1,0);
successCode=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
}
else //index.htm exists
{
len=0;
strcpy(responseBuffer,"");
while(1)
{
req=(char *)malloc(sizeof(char)*5);
fread(req,sizeof(req),1,f);
if(feof(f))break;
req[strlen(req)-1]='\0';
y=strlen(req);
len+=y;
strcat(responseBuffer,req);
free(req);
}
fclose(f);

strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
strcat(header,"Content-Length: ");
char responseLength[11];
sprintf(responseLength,"%d\n",len);
strcat(header,responseLength);
strcat(header,"\n");
successCode=send(clientSocketDescriptor,header,strlen(header)+1,0);
successCode=send(clientSocketDescriptor,responseBuffer,len+1,0);
}
}
else //index.html exists
{
len=0;
strcpy(responseBuffer,"");
while(1)
{
req=(char *)malloc(sizeof(char)*5);
fread(req,sizeof(req),1,f);
if(feof(f))break;
req[strlen(req)-1]='\0';
y=strlen(req);
len+=y;
strcat(responseBuffer,req);
free(req);
}
fclose(f);

strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
strcat(header,"Content-Length: ");
char responseLength[11];
sprintf(responseLength,"%d\n",len);
strcat(header,responseLength);
strcat(header,"\n");
successCode=send(clientSocketDescriptor,header,strlen(header)+1,0);
successCode=send(clientSocketDescriptor,responseBuffer,len+1,0);
}
}
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
