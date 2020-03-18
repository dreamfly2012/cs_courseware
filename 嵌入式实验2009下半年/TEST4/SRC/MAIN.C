#include "config.h"
#define LEDCON 0x00ff0000
const uint32 DISP_TAB[8]={0xff01ffff,0xff02ffff,0xff04ffff,0xff08ffff,0xff10ffff,0xff20ffff,0xff40ffff,0xff80ffff};
  uint32 time=0;
void delay(uint32 dly)
{
    uint32 i;
    for(;dly>0;dly--)
    {for(i=0;i<5000;i++);}
}
void __irq IRQtime(void)
{
   time=1;
}
        int main (void)
{// add user source code
 uint32 i; 
    IRQEnable();
    IO2SET  = 0xffffffff;
    IO2DIR=LEDCON;
    T0PR=99;
    T0MCR=0x03;
    T0MR0=2211840;
    T0TCR=0x03;
    VICIntSelect=0x00;
    VICVectCntl0=0x20|4;
    VICVectAddr0=(uint32)IRQtime;
    VICIntEnable=1<<4;
     

  while(1)
    {
     time=0;
     while(time==0)
     {
     for(i=0;i<8;i++)
         {
           if(time==1)break;
           IO2CLR=DISP_TAB[i];
           delay(60);
           IO2SET  = 0xffffffff;
           delay(60);
         }
     }
    time=0;
    while(time==0)
     {
     for(i=0;i<4;i++)
         {
          if(time==1)break;
           IO2CLR=DISP_TAB[i]&DISP_TAB[7-i];
           delay(60);
            IO2SET  = 0xffffffff;
            delay(60);
         }
     time=0;
   while(time==0)
     {
     for(i=0;i<4;i++)
         {
          if(time==1)break;
           IO2CLR=DISP_TAB[i]&DISP_TAB[7-i];
           delay(60);
            IO2SET  = 0xffffffff;
            delay(60);
         }
     }
     time=0;
    
    }
    while(1);
    return 0;
    }
}
