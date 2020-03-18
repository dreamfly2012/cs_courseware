#include "config.h"
#define  UART_BPS 115200;
uint8 const  SEND_STRING[] = "Hello World!\r\n";
void DelayNS(uint32 dly)
{
  uint32 i;
  for(;dly>0;dly--)
{
  for(i=0;i<5000;i++);
}
}
void UART0_Init(void)         //UART0初始化配置子程序
{
 uint16 FDIV;
 U0LCR=0x83;   //传输格式  8Bits数据  1bit停止位 无校验  DLAB=1 
 FDIV=(Fpclk/16)/UART_BPS;  //波特率计算
 U0DLM=FDIV>>8;             //波特率高8位寄存器配置
 U0DLL=FDIV&0xff;           //波特率低8位寄存器配置 
 U0LCR&=0x7F;               //使用U0RBR,U0THR接收，发送数据
}

void UART0_SENDBYTE(uint8 data)
{
  U0THR=data;
  while((U0LSR&0x40)==0);             //等待发送结束,D6=1发送缓冲区空
}
void UART0_SENDSTRING(uint8 const *str)
{
  while(1)
  {
    if(*str=='\0') break;       // 发送字符串，字符串以‘\0’结束
    UART0_SENDBYTE(*str++);
  }
}

int main(void)
{
  PINSEL0=0x00000005;            //配置p0.0 p0.1为TXD0,RXD0
  UART0_Init();                  //UART0初始化
  while(1)
  {
    UART0_SENDSTRING(SEND_STRING);    //发送字符串
    DelayNS(10);                      //延时10个单位
  }
}
