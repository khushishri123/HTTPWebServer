#include<tmwp>
#include<iostream>
using namespace std;
using namespace tmwp;
/*
void doSomething(int dataCount,char * data[])
{
cout<<"Great, This code got executed on Server Side"<<endl;
if(dataCount>0)cout<<"Data That Arrived"<<endl;
for(int r=0;r<dataCount;r++)
{
cout<<data[r]<<endl;
}
}
*/

void doSomething(Request &request,Response &response)
{
string n=request.get("nm");
string c=request.get("ct");
cout<<n<<endl;
cout<<c<<endl;
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>TMWebServer</title>");
response.write("</head>");
response.write("<body>");
response.write("Hello ");
response.write(n);
response.write("<br>");
response.write("Data Saved");
response.write("</body>");
response.write("</html>");
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/register",doSomething);
server.start();
return 0;
}
