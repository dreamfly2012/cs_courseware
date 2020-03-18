#include <REG51.H>    
#define uchar unsigned char    
#define uint unsigned int    
#define ulong unsigned long    

sbit P11 = 0x91;
sbit P12 = 0x92;
   
extern void cs_t(void);   
extern void delay(uint);   
void display();
data uchar dispram[3];   

data uchar testok;   
/*主程序*/   
void main(void)   
{   
data ulong time;   
P0 = 0xff;   
P2 = 0xff;   
TMOD = 0x11;   
IE = 0x80;   
while (1)   
  {   
  cs_t();   
  delay(1);   
  testok = 0;   
  EX0 = 1;   
  ET0 = 1;   
  while (!testok) display();   
  if (1 == testok)   
    {   
    time = TH0;   
    time = (time<<8) | TL0;   
    time *=170;   
    time /= 10000;   
    dispram[0] = (uchar) (time % 10);   
    time /= 10;   
    dispram[1] = (uchar) (time % 10);
    time /=10;   
    dispram[2] = (uchar) (time % 10);   
    } 
	 else   
    {   
    dispram[0] = 10;   
    dispram[1] = 10;   
    dispram[2] = 10;   
    }   
   display();
   delay(10000);
  }   
  while(1);
}   
//    
/*超声接收程序（外中断INT0）*/   
void cs_r(void) interrupt 0   
{   
 TR0 = 0;   
 ET0 = 0;   
 EX0 = 0;   
 testok = 1;   
}   
   
/*超时清除程序（内中断T0）*/
  
void overtime(void) interrupt 1   
{   
 EX0 = 0;   
 TR0 = 0;   
 ET0 = 0;   
 testok = 2;   
}   

void display()
{
	data uchar led_dis[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x0};
	data uchar i = 0;
	data uchar temp = 0x80;
	data uchar dis[3];
	P12 = 0;
	
	dis[0] = led_dis[dispram[0]];
	dis[1] = led_dis[dispram[1]];
	dis[2] = led_dis[dispram[2]];
	for(i=0;i<8;i++)
	{
		if(dis[0]&temp)
			P11 = 1;
		else
			P11 = 0;
		P12 = 1;		
		P12 = 0;		
		temp=temp>>1;
	}
    temp = 0x80;
	for(i=0;i<8;i++)
	{
		if(dis[1]&temp)
			P11 = 1;
		else
			P11 = 0;
		P12 = 1;		
		P12 = 0;		
		temp=temp>>1;
	}
    temp = 0x80;
	for(i=0;i<8;i++)
	{
		if(dis[2]&temp)
			P11 = 1;
		else
			P11 = 0;
		P12 = 1;	
		P12 = 0;
		temp=temp>>1;
	}
}
		