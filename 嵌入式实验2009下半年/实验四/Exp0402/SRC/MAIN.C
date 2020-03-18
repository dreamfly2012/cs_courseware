#include "config.h"

#define BEEPCON 1<<7


void __irq IRQ_Timer0(void)
{
  if((IO0SET&BEEPCON)==0)
  {
    IO0SET=BEEPCON;
  } else
  {
   IO0CLR=BEEPCON;
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
    VICIntEnable=0x00000000;
}


int main (void)
{ 
      IRQEnable();
      PINSEL0=0;
      IO0DIR=BEEPCON;
      Init();
      while(1);

    return 0;
}
