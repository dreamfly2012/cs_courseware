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
#define UART_BPS 115200
void DelayNS(uint32 dly)
{
uint32 i;
for(;dly>0;dly--)
{
	for(i=0;i<5000;i++);
}
}
void UART0Init(void)
{
	uint16 Fdiv;
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	Fdiv = (Fpclk>>4)/UART_BPS;
	U0DLM=Fdiv>>8;
	U0DLL=Fdiv & 0xff;
	U0LCR=0x03;
}
void UART0SendByte(uint8 data)
{
	U0THR = data;
	while((U0LSR&0x40)==0);
}
void UART0SendStr(char * str)
{
while(1)
{
	if( *str == '\0')break;
	UART0SendByte(*str++);
}
}
void PCDispChar(uint8 x,uint8 y,int8 chr,uint8 color)
{
	UART0SendByte(0xff);
	UART0SendByte(x);
	UART0SendByte(y);
	UART0SendByte(chr);
	UART0SendByte(color);
}
void ISendStr(uint8 x,uint8 y,uint8 color,char * str)
{
	while(1)
	{
		if(*str == '\0')break;
		PCDispChar(x++,y,*str++,color);
		if(x>=80)
		{
			x=0;
			y++;
		}
	}
}
        int main (void)
{// add user source code
	uint32 ADC_Data;
	char str[20];
	UART0Init();
	PINSEL1=0x01<<22;
	ADCR=(1<<0)|
	((Fpclk/1000000-1)<<8)|
	(0<<16)|
	(0<<17)|
	(0<<21)|
	(0<<22)|
	(0<<24)|
	(0<<27);
	DelayNS(10);
	ADC_Data=ADDR;
	while(1)
	{
		ADCR=(ADCR&0x00FFFF00)|0x01|(1<<24);
		while((ADDR&0x80000000)==0);
		ADCR=ADCR|(1<<24);
		while((ADDR&0x80000000)==0);
		ADC_Data = ADDR;
		ADC_Data = (ADC_Data>>6)&0x3FF;
		ADC_Data=ADC_Data*3300;
		ADC_Data=ADC_Data/1024;
		sprintf(str,"%4d",ADC_Data);
		ISendStr(40,12,0x51,str);
		DelayNS(10);
	} 
    return 0;
}
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
