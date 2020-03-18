#include "config.h"
#define  UART_BPS 115200;
volatile uint8 rcv_new;  //缓冲区是否有新接收数据
uint8 rcv_buf[8];
uint8 rcv_buflen;
uint32 y;

extern void strswap(uint8 *a,uint8 *b,uint8 *c,uint8 *d);
void __irq IRQ_UART0(void)
{ 
  if (0x04==(U0IIR&0x0f))
  {
   rcv_buf[rcv_buflen++]=U0RBR;
   if (rcv_buflen==5)  
   {
     rcv_new=1; 
     rcv_buflen=0;
   }
  }
  VICVectAddr=0x00;  
}



void UART0_Init(void)         //UART0初始化配置子程序
{
 uint16 FDIV;
 U0LCR=0x83;   //传输格式  8Bits数据  1bit停止位 无校验  DLAB=1 
 FDIV=(Fpclk/16)/UART_BPS;  //波特率计算
 U0DLM=FDIV>>8;             //波特率高8位寄存器配置
 U0DLL=FDIV&0xff;           //波特率低8位寄存器配置 
 U0LCR&=0x7F;               //使用U0RBR,U0THR接收，发送数据
 
 
 
  VICIntSelect=0;    // UART0 RDA IRQ方式
  VICVectCntl0=0x20|0x06;
  VICVectAddr0=(uint32)IRQ_UART0;
  
  U0FCR=0x01;   //1个触发点   0x81 
  U0IER=0x01;
 
  VICIntEnable=0x00000040;   //UART0开中断 
 
 
}
void SendByte(uint8 data)    
{
   U0THR=data;
   while((U0LSR&0x40)==0);             //等待发送结束,D6=1发送缓冲区空 //+++++
}
void ISendBuf(void)
{
 uint8 i;
 for(i=0;i<8;i++)  SendByte(rcv_buf[i]);
 while((U0LSR &0x20)==0);
}

int main(void)
{
  IRQEnable();
  PINSEL0=0x00000005;            //配置p0.0 p0.1为TXD0,RXD0
  UART0_Init();                  //UART0初始化
  rcv_buflen=0;

 while(1)
  {
    if(rcv_new==1)
      {
        rcv_new=0;
        strswap(rcv_buf+1,rcv_buf+2,rcv_buf+3,rcv_buf+4);         
        ISendBuf();
      }
  }
}
