#include "config.h"
uint8 function(uint8 cc)
{ 
  return (cc*2);
}

int main(void)
{  
  uint8 x = 1;
  uint8 y = 128;

while(1)

{  
 x = 1;
 while(x<y)
   {
     x = function(x);
     }
     }
     }