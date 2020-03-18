#include "config.h"
#define BEEPCON  1<<7


void __irq IRQ_Eint3(void)
{
   uint32  x;
   x=IO0SET;
   if((x&BEEPCON)==0)    
   {
      IO0SET=BEEPCON;
   } else
   {
      IO0CLR=BEEPCON;
   }
   
   EXTINT=1<<3;
   VICVectAddr=0;
}

int main (void)
{
    IRQEnable();
    PINSEL1=3<<8;
    IO0DIR=BEEPCON;
    IO0SET=BEEPCON;
    
    
    VICIntSelect=0;
    VICVectCntl0=0x20|17;
    VICVectAddr0=(int)IRQ_Eint3;
    EXTINT=1<<3;
    EXTMODE=1<<3;
    EXTPOLAR=0x00;
    VICIntEnable=1<<17;
    while(1);
    return 0;
}
