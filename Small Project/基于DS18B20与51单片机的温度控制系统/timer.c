#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"



int  T0_count=0;	                          //���ȼ�����
unsigned int ds18b20count=0;								//DS18B20������
unsigned int PIDcount=0;								    //PID������
unsigned int xianshicount=0;								//��ʾ������ 

void Init_Timer0()
{
   TMOD = 0X01;										          //��ʱ��0����ģʽ1
   TH0=0xB1;   									            //��ʱ��0װ��ֵ
	 TL0=0xE0;                                //��ʱ20ms
   TR0 = 1;
   ET0 = 1;
   EA=1;
}

/*******************************************************************************
* ������         : Timer0()
* ��������		 : T0�жϺ���
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Timer0() interrupt 1 using 1
{

  TR0=0;
  TH0=0xB1;   								                	//��ʱ��0װ��ֵ
	TL0=0xE0;                                     //��ʱ20ms	
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