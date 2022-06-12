#include<tmwp>
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
using namespace std;
using namespace tmwp;

void marks(Request &request,Response &response)
{
int r;
sscanf(request.get("rl").c_str(),"%d",&r);
int p,c,m,e,h;
if(r==101)
{
p=50;
c=55;
m=90;
e=60;
h=90;
}
if(r==102)
{
p=65;
c=75;
m=80;
e=70;
h=95;
}
if(r==103)
{
p=80;
c=95;
m=95;
e=70;
h=95;
}
if(r==104)
{
p=40;
c=54;
m=67;
e=56;
h=75;
}
if(r==105)
{
p=54;
c=89;
m=67;
e=67;
h=90;
}
request.setInt("physics",p);
request.setInt("chemistry",c);
request.setInt("maths",m);
request.setInt("english",e);
request.setInt("hindi",h);

request.forward("marksSheet.sct");
}

void generalStore(Request &request,Response &response)
{
int r;
sscanf(request.get("cs").c_str(),"%d",&r);
int ri,w,p,c,d;
if(r==101)
{
ri=50;
w=55;
p=90;
d=60;
c=90;
}
if(r==102)
{
ri=65;
w=75;
p=80;
d=70;
c=95;
}
if(r==103)
{
ri=80;
w=95;
p=95;
d=70;
c=95;
}
if(r==104)
{
ri=40;
w=54;
p=67;
d=56;
c=75;
}
if(r==105)
{
ri=54;
w=89;
p=67;
d=67;
c=90;
}
request.setInt("rice",ri);
request.setInt("wheat",w);
request.setInt("pulses",p);
request.setInt("dryFruits",d);
request.setInt("chocolates",c);

request.forward("generalStore.sct");
}

int main()
{
TMWebProjector server(8080);
server.onRequest("/marks",marks);
server.onRequest("/generalStore",generalStore);

server.addSCTFunction("marksSheet.sct","physics");
server.addSCTFunction("marksSheet.sct","chemistry");
server.addSCTFunction("marksSheet.sct","maths");
server.addSCTFunction("marksSheet.sct","english");
server.addSCTFunction("marksSheet.sct","hindi");

server.addSCTFunction("generalStore.sct","rice");
server.addSCTFunction("generalStore.sct","wheat");
server.addSCTFunction("generalStore.sct","chocolates");
server.addSCTFunction("generalStore.sct","pulses");
server.addSCTFunction("generalStore.sct","dryFruits");

server.start();
return 0;
}
