#include<fstream.h>
#include<dos.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<graphics.h>
float ld=-20,ud=20;
int pwry=1,var=1;
const float pi=22/7;
void reverse(char s[])              //reverses string
{for(int j=0;j<(strlen(s)/2);j++)
{char ch=s[j];
s[j]=s[strlen(s)-j-1];
s[strlen(s)-j-1]=ch;
}}
float strtoint(char a[])          //converts char to float
{float n=0,i=0,dec=0,ct1=0;
for(i=0;a[i]!='\0';i++)
if(a[i]=='.')
ct1++;

if(ct1==1)
{for(i=0;a[i]!='\0';i++)
if(a[i]=='.')
dec=i;
for(i=0;i<dec;i++)
n+=(a[i]-48)*pow(10,dec-i-1);
for(i=dec+1;i<strlen(a);i++)
n+=(a[i]-48)*(1/pow(10,i-dec));
}
else
for(i=0;a[i]!='\0';i++)
n+=(a[i]-48)*pow(10,strlen(a)-i-1);
return n;
}

void put(int color=14)       //To insert pixel at current location
{int x=getx();
int y=gety();
putpixel(x,y,color);}

double rety(char a[],float x)     //returns y for fn of x
{
double term,exp=0;
int pwrx=1;
float coeff=1;

for(int i=0;i<strlen(a);i++)
{
if(a[i]==' ')
i++;
else if(tolower(a[i])=='y'&&a[i+1]=='^')
pwry=a[i+2]-48;

else if(tolower(a[i])=='x')
{
int ct=0;
if(a[i+1]=='^')
{pwrx=a[i+2]-48;
if(pwrx>5)
break;}

for(int h=i-1;a[h]!=' ';h--)
{
if(a[h]=='-')
 {
	term=-term;
	ct++;
 }

else if(isdigit(a[h]))               
//to retrieve coefficient
 {
	char buff[20];
	for(int j=h,k=0;isdigit(a[j])||a[j]=='.';j--,k++)
	buff[k]=a[j];
	buff[k]='\0';
	reverse(buff);
	coeff=strtoint(buff);
	if(ct==0)
	term=coeff*pow(x,pwrx);
	else
	term=coeff*pow(term,pwrx);
	ct++;
 }

else if(isalpha(a[h]))         //functions
 {
	char s[10];
	for(int g=h,k=0;isalpha(a[g]);g--,k++)
	s[k]=a[g];
	s[k]='\0';
	reverse(s);
	if(ct==0)
	term=pow(x,pwrx);
	if(strcmpi(s,"sin")==0)
	{term=sin(term);
	}
	else if(strcmpi(s,"tan")==0)
	term=tan(term);
	else if(strcmpi(s,"cos")==0)
	{term=cos(term);
	}
	else if(strcmpi(s,"cot")==0)
	term=1/tan(term);
	else if(strcmpi(s,"cosec")==0)
	term=1/sin(term);
	else if(strcmpi(s,"log")==0)
	{if(term<0)
	term=0;
	else
	term=log10(fabs(term));
	var*=2;}
	else if(strcmpi(s,"ln")==0)
	{if(term<0)
	term=0;

	term=log(fabs(term));
	::var*=2;}
	else if(strcmpi(s,"asin")==0)
	{term=asin(term);
	::var*=3;}
	else if(strcmpi(s,"atan")==0)
	term=atan(term);
	else if(strcmpi(s,"acos")==0)
	{term=acos(term);
	::var*=3;}
	ct++;
  }

}
if(ct==0)
term=pow(x,pwrx);
exp+=term;
}
}

double ret;
if(exp<0&&pwry%2==0)
ret=0;
else
ret=pow(exp,1.0/pwry);
return ret;
}


void instructions()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:/TC/BGI");
clearviewport();
setbkcolor(BLUE);
settextstyle(GOTHIC_FONT,0,5);
outtextxy(100,40,"INSTRUCTIONS");
settextstyle(2,0,4);
setcolor(YELLOW);
outtextxy(10,120,"-> Enter the equation of the curve in the below mentioned format\n  y = ax^n + bx^m + ....");
delay(500);
outtextxy(10,140,"-> Eqaution must be an implicit function of x ");
delay(500);
outtextxy(10,160,"-> Equations may contain compound functions such as- sinx^2, logsinx, tancosecx");
delay(500);
outtextxy(10,180,"-> Type the equation in the following format-");
delay(500);
outtextxy(10,200,"-> y^l = Ax^m + Bx^n + Cx^0 ... where order of y=1 or 2 and order of x<5");
delay(500);
outtextxy(10,220,"-> Constants must be included as the coeffecients of x^0 ");
delay(500);
setcolor(CYAN);
outtextxy(10,240,"-> GIVE SPACES BEFORE & AFTER EACH TERM IN THE EQUATION");
delay(500);
setcolor(YELLOW);
outtextxy(10,260,"-> Trigonometric- sinx, cosx, tanx, cotx, cosecx, secx");
delay(500);
outtextxy(10,280,"-> Egs. y = 2sinx, y = 3sin2x -tancosx^2 etc...");
delay(500);
outtextxy(10,300,"-> Logarithmic/Exponential- y = ln2x, y = lntanx etc...");
delay(500);
setcolor(CYAN);
outtextxy(10,320,"-> DO NOT USE BRACKETS");
delay(500);

settextstyle(8,0,3);
setcolor(135);
outtextxy(150,360,"PRESS ANY KEY TO CONTINUE");
getch();
clearviewport();
}

		/*To draw co-ordinate axes of unit n(multiple of 8)
		  x - scale
		  n - division of screen*/
void axes(int x)
{setlinestyle(3,1,1);
setcolor(WHITE);
settextstyle(2,0,0);
int n=-320/x;
for(int i=-320;i<=320;i+=x,n++)  //incrementing by scale
{char s[5];
if(n<0)
s[0]='-';
else if(n>0)
s[0]='+';
else s[0]='0';
for(int f=n,j=1;f!=0;f/=10,j++)   //retrieving first digit
s[j]=abs(f)%10+48;
s[j]='\0';
for(j=1;j<strlen(s)/2+1;j++)      //retrieving second digit
{char ch=s[j];
s[j]=s[strlen(s)-j];
s[strlen(s)-j]=ch;
}
outtextxy(i+320,240,s);
outtextxy(320,-i+240,s);
}
line(320,0,320,480);
line(0,240,640,240);
}
