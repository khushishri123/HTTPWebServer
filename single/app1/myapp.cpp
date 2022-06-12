#include<tmwp>
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
using namespace std;
using namespace tmwp;
class StudentsData
{
public:
int rollNumber;
char name[35];
};
void addStud(Request &request,Response &response)
{
/*
No need to check uniqueness of the rollNumber
But be sure that you are not adding duplicate roll Number
Code to add data to a file
Put data in an object ,open file in append and binary mode
write object
close file
using response.write send back html that says , Student Added and a link
(OK) to send request for index.html
in the end dont't forget to call close method
*/
StudentsData sd;


int i,j,size;
string str;
sscanf(request.get("rl").c_str(),"%d",&sd.rollNumber);
cout<<"ROLL nunber coming is : "<<sd.rollNumber<<endl;
str=request.get("nm");
strcpy(sd.name,str.c_str());

//We will put StudentsData type object in File

ofstream f("Student.data",ios::app | ios::binary);
f.write((char *)&sd,sizeof(StudentsData));
f.close();

//Sending Response
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Student Add Form</title>");
response.write("</head>");
response.write("<body>");
response.write("Student Added<br>");
response.write("<a href='index.html'>Ok</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void getAllStudents(Request &request,Response &response)
{
/*
code to open data file
create html with that data from file and send it using response.write
in the end don't forget to call close
*/
//we will read oject of StudentsData class from file 

ifstream k("Student.data",ios::in | ios::binary);
if(k.fail())
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Student Add Form</title>");
response.write("</head>");
response.write("<body>");
response.write("No Student Added<br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
k.close();
return;
}
int pos,y,i,size;
k.seekg(0,ios::end);
pos=k.tellg();
size=sizeof(StudentsData);
y=pos/size;
k.seekg(0,ios::beg);
i=k.tellg();
StudentsData d[y];
StudentsData s;
i=0;
while(i<y)
{
k.read((char *)&s,sizeof(StudentsData));

if(k.fail())break;
d[i].rollNumber=s.rollNumber;
strcpy(d[i].name,s.name);

i++;
}
k.close();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Student Add Form</title>");
response.write("<style>");



response.write("table ,td {");
response.write("border: 1px solid black;");
response.write("border-collapse: collapse;");
response.write("}");
response.write("</style>");
response.write("</head>");
response.write("<body>");
response.write("<table>");
response.write("<tr>");
response.write("<td>S.NO.</td>");
response.write("<td>Roll Number</td>");
response.write("<td>Name</td>");
response.write("</tr>");
char a[93];
string str;

for(i=0;i<y;i++)
{
sprintf(a,"<tr><td>%d</td><td>%d</td><td>%s</td></tr>",i+1,d[i].rollNumber,d[i].name);

str=string(a);
response.write(str);
}
response.write("</table>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void sendStudentEditForm(Request &request,Response &response)
{
int rollNumber;
string str=request.get("rl");

sscanf(str.c_str(), "%d", &rollNumber);
ifstream k("Student.data",ios::in | ios::binary);
if(k.fail())return;
StudentsData s;
while(1)
{
k.read((char *)&s,sizeof(StudentsData));
if(k.fail())break;
if(s.rollNumber==rollNumber)break;
}
k.close();
char a[80];
char b[80];
char c[27];
str.clear();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Edit Module)");
response.write("<form method='get' action='updateStudent'>");
   sprintf(c,"Roll Number: %d<br>",rollNumber);
   str=string(c);
response.write(str);
   str.clear();
   sprintf(a,"<input type='hidden' id='rl' name='rl' value='%d'><br>",rollNumber);
   str=string(a);
response.write(str);
   str.clear();
  sprintf(b,"Name <input type='text' id='nm' name='nm' value='%s'><br>",s.name);
  str=string(b);
response.write(str);
response.write("<button type='submit'>Update</button>");
response.write("</form>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void updateStudentData(Request &request,Response &response)
{
int rollNumber;
int pos;
StudentsData s;
string str=request.get("rl");
sscanf(str.c_str(), "%d", &rollNumber);
str.clear();
string name=request.get("nm");
fstream f("Student.data",ios::out | ios::in | ios::binary);
//we are assuming that the roll number exist
while(1)
{
pos=f.tellg();
f.read((char *)&s,sizeof(StudentsData));
if(f.fail())break;
if(s.rollNumber==rollNumber)break;
}
strcpy(s.name,name.c_str());
//Very Very Important to bring the put pointer at pos position 
f.seekp(pos,ios::beg); 
f.write((char *)&s,sizeof(StudentsData));
f.close();

//Sending Response
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Edit Module)");
response.write("<h3>Student Updated</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='submit'>Ok</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}

void sendStudentDeleteConfirmationForm(Request &request,Response &response)
{
int rollNumber;
string str=request.get("rl");

sscanf(str.c_str(), "%d", &rollNumber);
ifstream k("Student.data",ios::in | ios::binary);
if(k.fail())return;
StudentsData s;
while(1)
{
k.read((char *)&s,sizeof(StudentsData));
if(k.fail())break;
if(s.rollNumber==rollNumber)break;
}
k.close();
char a[80];
char b[80];
char c[27];
str.clear();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Delete Module)");
response.write("<form method='get' action='deleteStudent'>");
   sprintf(c,"Roll Number: %d<br>",rollNumber);
   str=string(c);
response.write(str);
   str.clear();
   sprintf(a,"<input type='hidden' id='rl' name='rl' value='%d'><br>",rollNumber);
   str=string(a);
response.write(str);
   str.clear();
  sprintf(b,"Name: %s<br>",s.name);
  str=string(b);
response.write(str);
response.write("<button type='submit'>Delete</button>");
response.write("</form>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}

void deleteStudentData(Request &request,Response &response)
{
int rollNumber;
int pos;
StudentsData s;
string str=request.get("rl");
sscanf(str.c_str(), "%d", &rollNumber);
str.clear();
fstream f("Student.data",ios::in | ios::binary);
ofstream k("tmp.tmp",ios::out | ios::binary);
//we are assuming that the roll number exist
while(true)
{
f.read((char *)&s,sizeof(StudentsData));
if(f.fail())break;
if(s.rollNumber!=rollNumber)
{
k.write((char *)&s,sizeof(StudentsData));
}
}
f.close();
k.close();
ifstream kFile("tmp.tmp",ios::in | ios::binary);
ofstream fFile("Student.data",ios::out | ios::binary);
while(true)
{
kFile.read((char *)&s,sizeof(StudentsData));
if(kFile.fail())break;
fFile.write((char *)&s,sizeof(StudentsData));
}
fFile.close();
kFile.close();
kFile.open("tmp.tmp",ios::out | ios::binary);
//Sending Response
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Delete Module)");
response.write("<h3>Student Deleted</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='submit'>Ok</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}


int main()
{
TMWebProjector server(8080);
server.onRequest("/addStudent",addStud);
server.onRequest("/getStudents",getAllStudents);
server.onRequest("/editStudent",sendStudentEditForm);
server.onRequest("/updateStudent",updateStudentData);
server.onRequest("/confirmDeleteStudent",sendStudentDeleteConfirmationForm);
server.onRequest("/deleteStudent",deleteStudentData);
server.start();
return 0;
}
