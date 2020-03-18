#include "config.h"
unsigned char *Snstr=(unsigned char *)0x40003000;
unsigned char *Dnstr=(unsigned char *)0x40003200;

extern void strcopy(unsigned char *d,unsigned char *s);
 int main (void)
{
 
 unsigned char i;
 unsigned char *Snstr1=Snstr;
 unsigned char *Dnstr1=Dnstr;

 for(i=0;i<255;i++)
 {
  *Snstr1=(unsigned char)(i+1);
  *Dnstr1=(unsigned char)0x00;
  Snstr1++;
  Dnstr1++;
 }
  *Snstr1=(unsigned char)0x00;
  *Dnstr1=(unsigned char)0x00;
 
   
   strcopy(Dnstr,Snstr); 
 
    return 0;
}
