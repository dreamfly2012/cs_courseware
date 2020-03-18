#include<reg52.h>
int r0=3;
float r1=0;
void main()
{
   P1=0;
	TMOD=0X22;
	TH0=0xF9;
	TL0=0xF9;
	TH1=0XFE;
	TH0=0XFE;
	IE=0XFF;
	IT0=1;
	PX0=1;
	TR0=1;
	while(1);
}

void timer_0() interrupt 1 using 1
{
  r0--;
  P1^=0X01;
  TR1=1;
  if(r0==0)
  {
    TR0=0;
  }
}
void timer_1()interrupt 3 using 1
{
  r1++;
}

void int_0()interrupt 0 using 1
{
   TR0=0;
	TR1=0;
	r1=(int)0.068*r1*100;
	
}
