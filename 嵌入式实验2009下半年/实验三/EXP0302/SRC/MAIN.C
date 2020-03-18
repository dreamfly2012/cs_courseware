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
#define BEEPCON   0x00000080
#define LEDCON    0x00ff0000
#define KEY       1<<20
const uint32 DISP_TAB[8]={ 0xff01ffff,0xff02ffff,0xff04ffff,0xff08ffff,
                           0xff10ffff,0xff20ffff,0xff40ffff,0xff80ffff  };
void DelayNs(uint32 dly)
{
     uint32 i;
     for(;dly>0;dly--)
     {
         for(i=0;i<5000;i++);
     }
}
 
/*执行效果   
   0  LED亮60个单位   蜂鸣器不响60个单位   LED全灭    蜂鸣器响60个单位
   1  LED亮60个单位   蜂鸣器响60个单位     LED全灭    
   2  LED亮60个单位   蜂鸣器不响60个单位   LED全灭    蜂鸣器响60个单位
   3  LED亮60个单位   蜂鸣器响60个单位     LED全灭    
   4  LED亮60个单位   蜂鸣器不响60个单位   LED全灭    蜂鸣器响60个单位
   5  LED亮60个单位   蜂鸣器响60个单位     LED全灭    
   6  LED亮60个单位   蜂鸣器不响60个单位   LED全灭    蜂鸣器响60个单位
   7  LED亮60个单位   蜂鸣器响60个单位     LED全灭    
  
  KEY按下，LED\蜂鸣器保持前边状态     
*/
int main (void)
{
     uint8 i;
//初始化
     PINSEL0=0x00000000; //       p0.7   GPIO
     PINSEL1=0x00000000; //       p0.20  GPIO
     
     IO0DIR=0x00000080;  //       p0.7   Ouptput     p0.20  Input
     IO2DIR=LEDCON;      //       p2.16...p2.23     Output  
//

     while(1)
     {//while        
          for(i=0;i<8;i++)
              {  //for        
                 IO2CLR=DISP_TAB[i];      //显示LED
                 if((i%2)==0)             //0,2,4,6  LED
                 {          
                   IO0SET=BEEPCON;        //蜂鸣器不响
                   DelayNs(60);
              
                   while((IO0PIN&KEY)==0); 
  
                   IO2SET=0xffffffff;    //所有LED灭
                   IO0CLR=BEEPCON;       //蜂鸣器响
                   
                   DelayNs(60); 
                  }else                 //1,3,5,7 LED
                    { 
                     DelayNs(60);
                     while((IO0PIN&KEY)==0);
                     IO2SET=0xffffffff; 
                    }  
             }   //for
      } //while
      
      
       return 0;
    }


/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
