/*--------------------------------------  
超声测距单片机程序  
6MHz  40KHZ的方波
--------------------------------------*/   
#include <REG51.H>    
#include <stdio.h>
#include"intrins.h"
#define uchar unsigned char    
#define uint unsigned int    
#define ulong unsigned long  

data uchar led_dis[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x0};//段选码,0有效
data uchar dispram[3];   //bw sw gw
data uchar testok; //test sending finished or not
sbit P11 = 0x91; //1001 0001 
sbit P12 = 0x92; //1001 0010
sbit P13 = 0x93; //1001 0011
   
void cs_t(void)
{
data uchar i=0x4D;
data uchar j=1;
P1=0;
//TMOD=0X01;//STYLE 1
TH0=0X00;
TL0=0X00;//initial time is 6us
TR0=1;//start T0
for(i=0;i<70;i++)
  {
   P1^=0X01;//P1.0=~P1.0
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
   //j=1;
   //while(j--);//set 6us
  }
}   

extern void delay(uint);   
    
void display()//dispaly LED
{
	data uchar i = 0;
	data uchar temp = 0x80;//1000 0000
	data uchar dis0,dis1,dis2;
	dis0 = led_dis[dispram[0]];//LED display gw
	dis1 = led_dis[dispram[1]];//sw
	dis2 = led_dis[dispram[2]];//bw
	for(i=0;i<8;i++)
	{
		P12=0;//关,CLK低电平
		if(dis0&0x80)//1000 0000,gw1最高位为1,serial input data
		{
			P11=1;//A\B口data is 1
			dis0=dis0<<1;//gw
			P12=1;//开SN74HC164,CLK高电平
		}
		else
		{
			P11=0;//data is 0
			dis0=dis0<<1;
			P12=1;
		}
	}

	for(i=0;i<8;i++)
	{
		P12=0;
		if(dis1&0x80)
		{
			P11=1;//sw
			dis1=dis1<<1;
			P12=1;
		}
		else
		{
			P11=0;
			dis1=dis1<<1;
			P12=1;
		}
	}

	for(i=0;i<8;i++)
	{
		P12=0;
		if(dis2&0x80)
		{
			P11=1;
			dis2=dis2<<1;//bw
			P12=1;
		}
		else
		{
			P11=0;
			dis2=dis2<<1;
			P12=1;
		}
	}
}

/*主程序*/   
void main(void)   
{  
data ulong time; //calculate time
P0 = 0xff;   
P2 = 0xff;   
//TMOD = 0x11;    //type 3 working
TMOD = 0x01;   //type 1 working
IE = 0x80;     //1000 0000,CPU respond INTR
while (1)   
  {   
  cs_t();       //sending or transport,start TO
  delay(1);     //delay to make sure sending finishied
  testok = 0;   //initial unfinished 
  EX0 = 1;      //permit INT0
  ET0 = 1;      //permit T0
  while (!testok)
  display();    //dispaly the current  0
  if (1 == testok)   
    {   
    time = TH0;   
    time = (time<<8) | TL0;   
    time *=170;   //sound speed 0f 1/2
    time /= 10000; //S=170*TIME/10000(us)  
    dispram[0] = (uchar) (time % 10);   //gw
    time /= 10; 
    dispram[1] = (uchar) (time % 10);   //sw
    dispram[2] = (uchar) (time / 10);   //bw
    } 
	 else   //unfinished sending,dispaly LED nothing
    {   
    dispram[0] = 10;   
    dispram[1] = 10;   
    dispram[2] = 10;   
    }   
  display();   //dispaly the distance
  delay(10000);
  }
  while(1);
}   
    
//超声接收程序（外中断0)  
void cs_r(void) interrupt 0   
{   
 TR0 = 0;   //close T0
 ET0 = 0;   //no permit TO
 EX0 = 0;   //no permit INT0
 testok = 1;//received
}   
 
  
//超时清除程序（内中断T0）   
void overtime(void) interrupt 1
{   
 EX0 = 0;   
 TR0 = 0;   
 ET0 = 0;   
 testok = 2;   
}   

