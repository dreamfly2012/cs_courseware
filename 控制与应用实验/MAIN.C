//====================================================================
#include <reg52.h>
#include <intrins.h>   //use _nop_() function
//===================================================================

//键盘定义
sbit s1=P3^6;  //
sbit s2=P3^7;  //

//74HC164
sbit sclk=P1^2;
sbit sda=P1^1; 

unsigned char tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};// 11表示清屏

//==============================================================
void delay(int  count )	   //延时
{
	unsigned char i;
	for (i=0;i<count;i++)
	{
		_nop_();
	}
}

void sendbyte(unsigned char by)
{
	unsigned char num,c; 
	num=tab[by];
	//从高位开始发送每一位
	for(c=0;c<8;c++)
	{
		sclk=0;
		sda=num&0x80; //(0x80即十进制的128, 二进制的10000000 按位发送)
		sclk=1;
		_nop_();
		num<<=1;
	}
}

void display_t(){ 
	unsigned char t0,t1,t2; //显示   
	t0=1;
	t1=2;
	t2=3;
	sendbyte(t2);
	sendbyte(t1);
	sendbyte(t0); 
} 
            
void main()
{
	do{
		display_t();
		delay(1000);
	}while(1);
}

