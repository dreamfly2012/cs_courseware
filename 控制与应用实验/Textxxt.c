//LCM-12864汉字液晶显示驱动程序
#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

uint count_time=4000;
uint count,pcount;
sbit p_csa = P1^7; 		//cs1
sbit p_csb = P1^6;		//cs2
//sbit p_gnda=P2^5;
//sbit p_gndb=P2^4;
sbit p_rst = P1^5;	
sbit p_rw = P3^4;	//读写信号		
sbit p_e = P3^3;	//使能信号
sbit p_rs = P3^5;	 //寄存器选择信号


//判别busy
void lcd_busy(void) {
	P2=0xff;//总线释放
	p_rs=0;
	p_rw=1;
	while (1) {
		p_e=1;
		if (P2<0x80) break;//Not busy
		p_e=0;
	} 
	p_e=0;
}

//设置xy
void set_xy(unsigned char y,unsigned char x) {
	if (y>=64)//右边屏幕有效64=0x0100 0000,half and half set
 	{
	p_csa=0;
	p_csb=1;
	}
 	else   //左边有效
  	{
	p_csb=0;
	p_csa=1;
	}
	lcd_busy();
	p_rs=p_rw=0;//写指令代码
	P2=0x40|y; //0100 0000|x,y addr set,6 bit
	p_e=1;//p_e=1,写指令代码
	p_e=0;    
	lcd_busy();
	p_rs=p_rw=0;//写指令代码
	P2=0xb8|x;//1011 1000|y,page addr x sey,3 bit
	p_e=1;
	p_e=0;
	P2=0xff;  //总线释放
}


//写数据
void lw(unsigned char y,unsigned char x,unsigned char dd) {
	set_xy(y,x);//set x and y
	lcd_busy();
	p_rs=1;
	p_rw=0;//写displayed数据
	P2=dd;//data
	p_e=1;
	p_e=0;//下降边沿
	P2=0xff;//总线释放
}


//显示初始化
#pragma disable
void lcd_init(void) 
{
	unsigned char x,y;
	//p_gnda=p_gndb=0;
   //开显示
	p_e=p_rs=p_rw=0;//现display开关设置
	p_csa=p_csb=0;//All closed at fist

	p_csa=1;//left open
	P2=0x3f;//0011 1111 open display开关
	p_e=1;
	p_e=0;//input DB7--DB0,写指令代码 
	p_csa=0;//left close

	p_csb=1;//right open
	P0=0x3f;//open display开关
	p_e=1;
	p_e=0;
	p_csb=0;//right close


	//0行开始显示
	p_csa=1;    //left screen display init
	lcd_busy();
	p_rs=p_rw=0;//写指令代码
	P2=0xc0;   //1100 0000,init display data from the first line
	p_e=1;
	p_e=0;    //下降边沿
	p_csa=0;//close left

	p_csb=1; //right half screen display init
	lcd_busy();
	p_rs=p_rw=0;
	P0=0xc0;
	p_e=1;
	p_e=0;
	p_csb=0;

	for (y=0;y<8;y++) {//row     init display
		for (x=0;x<128;x++)//cols
	 		lw(x,y,0);
	}
}





unsigned char code hz[]={
0x04,0xE4,0x34,0x24,0x2F,0xE4,0x04,0x64,0xA4,0x2F,0x34,0x24,0xE4,0x24,0x04,0x00,
0x00,0x7F,0x25,0x25,0x25,0x7D,0x02,0x0A,0x0A,0x0B,0xFE,0x0B,0x0A,0x0A,0x02,0x00,/*"薛",0*/

0x00,0x10,0x0C,0x84,0x74,0x24,0x25,0xFE,0x24,0x24,0x24,0x24,0x14,0x0C,0x04,0x00,
0x00,0x01,0x81,0x41,0x31,0x0F,0x01,0x01,0x01,0x3F,0x41,0x41,0x41,0x71,0x20,0x00,/*"宪",1*/

0x00,0x40,0x30,0x12,0xDC,0x54,0x50,0x5F,0x50,0x50,0xD8,0x16,0x54,0x38,0x10,0x00,
0x00,0x40,0x48,0x48,0x4B,0x4A,0x4A,0x7E,0x4A,0x4A,0x4B,0x48,0x48,0x48,0x40,0x00,/*"堂",2*/

};

//显示汉字，fb==1:反白显示,x is col,n is to select which hanzi to dispaly
void dh(unsigned char x,unsigned char y,unsigned char n,unsigned char fb) //16*16
{
	unsigned char j,i,dd;
	for (i=0;i<16;i++) //16 cols every "hanzi"
	{
    //for(j=0;j<32;j++){
		dd=hz[i+n*32];
		if (fb) //fb==1:反白显示
			if (n!=5) 
				dd=255-dd;
		lw(x*8+i,y,dd);//写数据

	dd=hz[i+n*32+16];
	if (fb)
 		if (n!=5) 
			dd=255-dd;
	lw(x*8+i,y+1,dd);
	}
}


void delayX10ms(uint count) //delay X10ms
{
	uint i,j,k;
	for (i=0; i<count; i++)
 	 for(j=0; j<10; j++)
  	  for(k=0; k<120; k++);
}

void main()
{
//unsigned char t;
 lcd_init();
 while(1)
 {
 lcd_init();

 

    dh(0,0,0,1);
	 dh(0,2,1,1);
	 dh(0,4,2,1);

  
 } 
}

 
