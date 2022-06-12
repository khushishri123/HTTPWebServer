//Code of Lecture 108 (before changing for lecture 109)
#include<tmwp>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<map>
#include<utility>
using namespace tmwp;
using namespace std;

void Request::setKeyValue(string k,string v)
{
this->keyValues.insert(pair<string,string>(k,v));
}
string Request::getKeyValue(string k)
{
map<string,string>::iterator it=this->keyValues.find(k);
if(it==this->keyValues.end())return string("");
return it->second;
}


string Request::decoder(string str)
{
int i,pos;
string s;
pos=str.find("+");
while(pos>=0 && pos<str.length())
{
str.replace(pos,1," ");
pos=str.find("+",pos+1);
}
pos=str.find("%20");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3," ");
pos=str.find("%20",pos+1);
}
pos=str.find("%22");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"\"");
pos=str.find("%22",pos+1);
}
pos=str.find("%23");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"#");
pos=str.find("%23",pos+1);
}
pos=str.find("%24");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"$");
pos=str.find("%24",pos+1);
}
pos=str.find("%25");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"%");
pos=str.find("%25",pos+1);
}
pos=str.find("%26");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"&");
pos=str.find("%26",pos+1);
}
pos=str.find("%27");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"'");
pos=str.find("%27",pos+1);
}
pos=str.find("%28");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"(");
pos=str.find("%28",pos+1);
}
pos=str.find("%29");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,")");
pos=str.find("%29",pos+1);
}
pos=str.find("%2B");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"+");
pos=str.find("%2B",pos+1);
}
pos=str.find("%2C");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,",");
pos=str.find("%2C",pos+1);
}
pos=str.find("%2F");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"/");
pos=str.find("%2F",pos+1);
}
pos=str.find("%5B");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"[");
pos=str.find("%5B",pos+1);
}

pos=str.find("%5D");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"]");
pos=str.find("%5D",pos+1);
}

pos=str.find("%5E");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"^");
pos=str.find("%5E",pos+1);
}

pos=str.find("%7B");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"{");
pos=str.find("%7B",pos+1);
}

pos=str.find("%7C");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"|");
pos=str.find("%7C",pos+1);
}

pos=str.find("%7D");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"}");
pos=str.find("%7D",pos+1);
}


pos=str.find("%3A");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,":");
pos=str.find("%3A",pos+1);
}

pos=str.find("%3B");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,";");
pos=str.find("%3B",pos+1);
}

pos=str.find("%3C");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"<");
pos=str.find("%3C",pos+1);
}

pos=str.find("%3D");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"=");
pos=str.find("%3D",pos+1);
}

pos=str.find("%3E");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,">");
pos=str.find("%3E",pos+1);
}

pos=str.find("%40");
while(pos>=0 && pos<str.length())
{
str.replace(pos,3,"@");
pos=str.find("%40",pos+1);
}
return str;
}

string Request::get(string name)
{
string val,s;
int i,e;
for(i=0;i<this->dataCount;i++)
{
for(e=0;data[i][e]!='\0' && data[i][e]!='=';e++);
if(data[i][e]!='=') continue;//we are going to compare only when we found = ,otherwise no comp.
if(strncmp(data[i],name.c_str(),e)==0)break;
}
if(i==this->dataCount)
{
val="";
}
else
{
val=string(data[i]+(e+1));
}
s=decoder(val);
return s;
}
void Request::forward(string forwardTo)
{
this->forwardTo=forwardTo;
}

Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->isClosed=false;
this->headerCreated=false;
}
void Response::createHeader()
{
char header[51];
strcpy(header,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n");
send(clientSocketDescriptor,header,strlen(header),0);
this->headerCreated=true;
}
void Response::write(const char *str)
{
if(str==NULL)return;
int len=strlen(str);
if(len==0)return;
if(!this->headerCreated)createHeader();
send(clientSocketDescriptor,str,len,0);
}
void Response::write(string str)
{
this->write(str.c_str());
}

void Response::close()
{
if(isClosed) return;
closesocket(this->clientSocketDescriptor);
isClosed=true;
}


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
if(extensionEquals(resource+lastIndexOfDot+1,"tpl"))
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
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
return mimeType;
}
char isClientSideResource(char *resource)
{
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(resource[i]=='\0')return 'N';
i++;
while(resource[i]!='\0')
{
if(resource[i]=='t')i++;
if(resource[i]=='p')i++;
if(resource[i]=='l')i++;
break;
}
if(resource[i]=='\0')return 'N';
return 'Y'; //this has to be changed later on
}
Request * parseRequest(char *bytes)
{
char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++)method[i]=bytes[i];
method[i]='\0';
i+=2;//One for space and one for front slash

char ** data=NULL;
int dataCount=0;
if(strcmp(method,"GET")==0)
{
//whatever?something=something&something=something&something=something
for(j=0;bytes[i]!=' ';i++,j++)
{
if(bytes[i]=='?')break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?') //Query String Exists
{
i++; //Since we are on the question mark ,humme ek ghar aage se start kerna hai
int si=i; //We have stored that point from  where query string starts
while(bytes[i]!=' ')
{
if(bytes[i]=='&')dataCount++;
i++;
}
dataCount++; //++ islia kiya because if there are two & ,it means there are 3 elements
data=(char **)malloc(sizeof(char *)*dataCount);
int *pc=(int *)malloc(sizeof(int)*dataCount);
i=si;
j=0;
while(bytes[i]!=' ') //we have not written bytes[i]!='&' because it may be possible that there will be only one element, then we will not find &
{
if(bytes[i]=='&')
{
pc[j]=i;
j++;
}
i++;
}
pc[j]=i; //because if there are 2 & ,it means that dataCount=3 
i=si;
j=0;
int howManyToPick;
while(j<dataCount)
{
howManyToPick=pc[j]-i; //pc[j] is on & ,so we don't have to count that &
data[j]=(char *)malloc(sizeof(char)*(howManyToPick+1));
strncpy(data[j],bytes+i,howManyToPick);
data[j][howManyToPick]='\0';//data[j] is a pointer and at the end we putted \0 to which it is pointing
i=pc[j]+1; //we did +1 because pc[j] stands on & and our data starts after &
j++;
}
}//Query String Exists
}//if method is of GET type 

printf("Request arrived for %s\n",resource);
//Request *request=(Request *)malloc(sizeof(Request));
Request *request=new Request; //v v v IMP

request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
request->dataCount=dataCount;
request->data=data;
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
TMWebProjector::TMWebProjector(int portNumber)
{
this->portNumber=portNumber;
}
TMWebProjector::~TMWebProjector()
{
}
void TMWebProjector::onRequest(string url,void (*ptrOnRequest)(Request &rq,Response &rs))
{
if(url.length()==0 || ptrOnRequest==NULL)return;
requestMappings.insert(pair<string,void (*)(Request &,Response &)>(url,ptrOnRequest));
}

void TMWebProjector::start()
{
FILE *f;
int length;
int i,rc;
char g;
char responseBuffer[1024];//A chunk of 1024 
char requestBuffer[8192];//1024*8 =8192
char header[5000];
int y;
long k;
int cnt;
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
return;
}
//filling all the necessary information on the structure
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->portNumber);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);

//binding the socket with IP and Port Number
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
char message[101];
if(successCode<0)
{
sprintf(message,"Unable to bind socket to port %d",this->portNumber);
printf("%s\n",message);
WSACleanup();
return;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);

while(1) //infinite loop to accept connection
{
sprintf(message,"TMServer is ready to accept request on port %d",this->portNumber);
printf("%s\n",message);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept Client Connection");
closesocket(serverSocketDescriptor);
WSACleanup();
return;
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
Request *request=parseRequest(requestBuffer);

while(1) //Infinite loop to enable the forwarding feature
{
if(request->isClientSideTechnologyResource=='Y')
{
if(request->resource==NULL)//this will happen only when request contains only front slash
{
f=fopen("index.html","rb");
if(f!=NULL)printf("Sending index.html\n");
if(f==NULL) //index.html does not exists
{
f=fopen("index.htm","rb");
if(f!=NULL)printf("Sending index.htm\n");
}
if(f==NULL)
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:163\nConnection: close\n\n<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("Sending 404 page\n");
closesocket(clientSocketDescriptor);
break; //introduced because of the forwarding feature
}
else
{
fseek(f,0,2);// move the internal pointer to the end of file
length=ftell(f);
fseek(f,0,0);//move the internal pointer to the start of file
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}//while loop ends
fclose(f);
closesocket(clientSocketDescriptor);
break; //introduced because of the forwarding feature
}
}
else //resource name is present
{
f=fopen(request->resource,"rb");
if(f!=NULL)printf("Sending %s\n",request->resource);
if(f==NULL)
{
//something needs to be done over here
char tmp[501];
printf("Sending 404 page\n");
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
break; //introduced because of the forwarding feature
}
else
{
fseek(f,0,2);// move the internal pointer to the end of file
length=ftell(f);
fseek(f,0,0);//move the internal pointer to the start of file
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: close\n\n",request->mimeType,length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024)rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}//while loop ends
fclose(f);
closesocket(clientSocketDescriptor);
break; //introduced because of the forwarding feature
}
}
}
else //Server Side Resource
{
//more changes required in contest to server side resource
map<string,void (*)(Request &,Response &)>::iterator iter;
iter=requestMappings.find(string("/")+string(request->resource));

if(iter==requestMappings.end())
{
char tmp[501];
printf("Sending 404 page\n");
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
break; //introduced because of the forwarding feature
}
else
{
Response response(clientSocketDescriptor);
request->forwardTo="";
iter->second(*request,response);
if(request->forwardTo.length()>0)
{
free(request->resource);
request->resource=(char *)malloc((sizeof(char)*request->forwardTo.length())+1);
strcpy(request->resource,request->forwardTo.c_str());
request->isClientSideTechnologyResource=isClientSideResource(request->resource);
request->mimeType=getMIMEType(request->resource);
continue;
}
//Now releasing memory of data
if(request->data!=NULL)
{
for(int k=0;k<request->dataCount;k++)
{
free(request->data[k]);// releasing memory of pointers to which data is pointing
}
free(request->data); //releasing memory of data
}//if ended
break; //introduced because of the forwarding feature
} //else ended
} //else ended(Server side resource)
}//infinite loop ends that provides feature of forwarding
} //else ended
}//the infinite loop related to accept method  ends here
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}
