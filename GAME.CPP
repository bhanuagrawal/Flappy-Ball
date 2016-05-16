#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<string.h>
char buffer[80],buffer1[80];
union REGS in,out;
int y1=250,cl;
int xa1,xa2,xb1,xb2,xc1,xc2,h0,x,y,count=0,flag=0,counts=0,click,highscore=0,i=0;
char bt1[20],ch='q';
int callmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}
void mouseposi(int &xpos,int &ypos,int &click)
{

	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}
void setposi(int &xpos,int &ypos)
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}
int mousehide()
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}
void pipe(int,int,int);
void menu();
char*  mouse(int,int,int,int,char*);
void button(int,int,int,int,char*);
void main()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
   setbkcolor(6);
   menu();
   closegraph();
}
void pipe(int h1,int h2,int h3)
{
	count++;
	h0=random(250);
	xa1=getmaxx();
	xb1=getmaxx()/2;
	xc1=0;
	do{
		cleardevice();
		callmouse();
		mouseposi(x,y,cl);
		circle(100,y1,20);
		if(counts%100==0)
			click=0;
		if(cl==1||click==1)
		{
			y1=y1-2;
			counts=counts+2;
			click=1;
		}
		else
		{
		  y1=y1+2;
		}
		xa2=xa1+50;
		xb2=xb1+50;
		xc2=xc1+50;
		rectangle(xa1,-5,xa2,h1);
		rectangle(xb1,-5,xb2,h2);
		rectangle(xc1,-5,xc2,h3);
		rectangle(xa1,h1+150,xa2,600);
		rectangle(xb1,h2+150,xb2,600);
		rectangle(xc1,h3+150,xc2,600);
		if(30<xb1&&xb1<120&&((y1-20)<h2||y1>(h2+130)))
			menu();
		if(xa1<(getmaxx()/2))
			pipe(h0,h1,h2);
		delay(10);
		xa1=xa1-2;
		xb1=xb1-2;
		xc1=xc1-2;
	}while(!kbhit());
}
void menu()
{
	int score;
	if(count>highscore)
		highscore=count;
	setposi(100,100);
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(200,200,400,400);
	i++;
	sprintf(buffer1,"HIGHSCORE:%d",highscore);
	outtextxy(220,280,buffer1);
	if(i!=1)
		sprintf(buffer,"YOUR SCORE:%d",count);
	outtextxy(220,250,buffer);
	y1=250;
	button(220,310,50,20,"PLAY");
	button(320,310,50,20,"EXIT");
	cl=0;
	do{
		callmouse();
		mouseposi(x,y,cl);
		strcpy(bt1,mouse(220,310,50,20,"PLAY"));
		if(strcmp(bt1,"PLAY")==0)
		{
			count=0;
			pipe(150,100,50);
		}
		strcpy(bt1,mouse(320,310,50,20,"EXIT"));
		if(strcmp(bt1,"EXIT")==0)
		{
			exit(1);
		}
   }while(1);
}

void  button(int Left,int Top,int Width,int Height,char* Caption)
{
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(Left,Top,Left+Width,Top+Height);
	setcolor(WHITE);
	line(Left,Top,Left+Width,Top);
	line(Left,Top,Left,Top+Height);
	setcolor(BLACK);
	line(Left,Top+Height,Left+Width,Top+Height);
	line(Left+Width,Top,Left+Width,Top+Height);
	setcolor(WHITE);
	outtextxy(Left+(Width/2)-(textwidth(Caption)/2)+1,
	Top+(Height/2)-(textheight(Caption)/2)+1,Caption);
}

char*  mouse(int left,int top,int width,int height,char* caption)
{
     if(x>=left&&x<=(left+width)&&y>=top&&y<=(top+height)&&cl==1)
     {
		mousehide();
		return(caption);
     }
     else
		return(" ");
}
