#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"



int  T0_count=0;	                          //加热计数器
unsigned int ds18b20count=0;								//DS18B20计数器
unsigned int PIDcount=0;								    //PID计数器
unsigned int xianshicount=0;								//显示计数器 

void Init_Timer0()
{
   TMOD = 0X01;										          //定时器0工作模式1
   TH0=0xB1;   									            //定时器0装初值
	 TL0=0xE0;                                //定时20ms
   TR0 = 1;
   ET0 = 1;
   EA=1;
}

/*******************************************************************************
* 函数名         : Timer0()
* 函数功能		 : T0中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Timer0() interrupt 1 using 1
{

  TR0=0;
  TH0=0xB1;   								                	//定时器0装初值
	TL0=0xE0;                                     //定时20ms	
  T0_count++;
  ds18b20count++;
  PIDcount++;
  xianshicount++;	
  if(T0_count>maikuan)
  	 {	
       KT=1; 
     }
  else 	
	   {	
       KT=0;
	   }
  if(T0_count>=100)
  	 {
	     T0_count=0;
	   }
	TR0=1;
}