#include<tmwp>
#include<stdlib.h>
#include<iostream>
#include<ctime>
#include "tpl.h"
using namespace std;
using namespace tmwp;
void dispatchTime(Request &request,Response &response)
{
time_t t=time(0);
char *now=ctime(&t);
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>The Clock</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>");
response.write(now);
response.write("</h1>");
response.write("<a href='now'>Refresh</a><br>");
response.write("<a href='index.html'>Home</a><br>");
response.write("</body>");
response.write("</html>");
response.close();
}
void getCityView(Request &request,Response &response)
{
string cityCodeString=request.get("cityCode");
cout<<"("<<cityCodeString<<")"<<endl;
int cityCode=atoi(cityCodeString.c_str());
if(cityCode==1)request.forward("Ujjain.html");
else if(cityCode==2) request.forward("Indore.html");
else if(cityCode==3)request.forward("Dewas.html");
else
{
request.setKeyValue("error","Invalid choice, City not selected");
request.forward("ErrorPage.tpl");
}
}

void saveEnquiry(Request &request,Response &response)
{
string n=request.get("nm");
string c=request.get("ct");
string a=request.get("ad");
string m=request.get("msg");
cout<<"Data recieved"<<endl;
cout<<"Name :"<<n<<endl;
cout<<"City :"<<c<<endl;
cout<<"Address :"<<a<<endl;
cout<<"Query :"<<m<<endl;

//some logic to save data somewhere (may be a file or some database)
request.forward("SaveNotification.html");
}

int main()
{
TMWebProjector server(8080);
//following calls are for mapping a url to a function
server.onRequest("/now",dispatchTime);
server.onRequest("/addEnquiry",saveEnquiry);
server.onRequest("/getCity",getCityView);
registerTPLs(&server);
server.start();
return 0;
}
