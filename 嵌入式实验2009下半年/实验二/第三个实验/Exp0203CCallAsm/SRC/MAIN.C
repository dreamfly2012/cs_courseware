#include "config.h"
extern void strcopy(char *d,char *s);
 int main (void)
{
 
 char str1[256];
 char str2[256];

 uint8 i;
 
 for(i=0;i<255;i++)
 {
   str1[i]=(char)(i+1);
   str2[i]=(char)0x00;
 }
   str1[255]=(char)0x00;
   str2[255]=(char)0x00;
   
   strcopy(str2,str1); 
 
    return 0;
}
