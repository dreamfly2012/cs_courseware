/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			main.c
** Last modified Date:  2004-09-16
** Last Version:		1.0
** Descriptions:		The main() function example template
**
**------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-09-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#include "config.h"
const uint32 DISP_TAB8[8]=
{
	0xff01ffff,0xff02ffff,0xff04ffff,0xff08ffff,
	0xff10ffff,0xff20ffff,0xff40ffff,0xff80ffff
};
const uint32 DISP_TAB4[4]=
{
	0xff81ffff,0xff42ffff,0xff24ffff,0xff18ffff,
};
#define KEY 1<<20
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
    unsigned flag=0;    
    PINSEL0=0x00000000;
    IO0DIR=0x00000080;
    IO2DIR=0x00ff0000;
while(1)
{
	if((IO0PIN&KEY)==0)
	{ //¼ü°´ÏÂ
	  if(flag>=8)  flag=0;
	  IO2CLR=DISP_TAB8[flag];
	  flag++;
	  DelayNs(30);
	}
	else
	{
	  if(flag>=4)  flag=0;
	  IO2CLR=DISP_TAB4[flag];
	  flag++;
	  DelayNs(30);
	}
            IO2SET=0xffffffff;
			DelayNs(30);	
	
}
    return 0;
}
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
