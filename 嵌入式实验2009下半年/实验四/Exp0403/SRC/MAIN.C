#include "config.h"

uint32 TimeCnt=0;
uint8 b=0;
void __irq IRQ_Timer0(void)
{
   TimeCnt++;
   if(b==0)  //20S
   {
      if (TimeCnt>=10)
      {
        b=1;
        TimeCnt=0;
      }
   } else
   {  //10s
      if (TimeCnt>=10)
      {
        b=0;
        TimeCnt=0;
      }
   }  
  
   T0IR=0x01; 
   VICVectAddr=0x00;
}

void Init(void)
{
    T0PR=99;
    T0MCR=0x03;
    T0MR0=221184;
    T0TCR=0x03;
    T0TCR=0x01;
    
    
    
    VICIntSelect=0x00;
    VICVectCntl0=0x24;
    VICVectAddr0=(uint32)IRQ_Timer0;
    VICIntEnable=0x00000010;
}

const uint32 DISP_TAB0[8]=
{
  0xff01ffff,0xff02ffff,0xff04ffff,0xff08ffff,
  0xff10ffff,0xff20ffff,0xff40ffff,0xff80ffff
};

const uint32 DISP_TAB4[4]=
{
  0xff81ffff,0xff42ffff,0xff24ffff,0xff18ffff
};

void DelayNs(uint32 dly)
{
    uint32 i;
    for(;dly>0;dly--)
    {
      for(i=0;i<5000;i++);
    }
}
int main (void)
{ 
      uint8 x1=0;
      uint8 x4=0;
      IRQEnable();
      Init();
      IO2DIR=0x00ff0000;
      while(1)
      {
        if(b==0)
        {   //8
           IO2CLR=DISP_TAB0[x1];
           x1++;
           if(x1>=8)   x1=0;
           DelayNs(30);
           IO2SET=0xffffffff;
           DelayNs(30);
        } else
        {   //4
           IO2CLR=DISP_TAB4[x4];
           x4++;
           if(x4>=4)   x4=0;
           DelayNs(30);
           IO2SET=0xffffffff;
           DelayNs(30);
        }                                
      
      }

    return 0;
}
