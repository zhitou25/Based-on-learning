#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"


int    T_ds18b20=0;               //�����˲�����¶�
int    T_ds18b20_new=0;			      //DS18B20�ⶨ���¶�
int    T=7500;                                  								//Ŀ���¶� �Ŵ�һ�ٱ�	������Ϊint�� �����и�	   
int    maikuan=50;							  //ռ�ձ� ���100
int    Det=0;					            //PID����ֵ��u(k)
float  Kp=20;                     //PID��ʽ�б���ϵ��
float  Ki=0.6;                    //PID��ʽ�л���ϵ�� 
float  Kd=10;							        //PID��ʽ��΢��ϵ��
float  error=0;                   //��ǰƫ�       e(k)
float  last_error=0;              //�ϴ�ƫ�       e(k-1)
float  pre_error=0;               //���ϴ�ƫ�     e(k-2)

/*******************************************************************************
* ������         : PID()
* ��������		   : PID����
* ����           : ��ǰ�¶�
* ���         	 : �������PWM����ռ�ձ�
*******************************************************************************/	

void PID()
{
	if(PIDcount>=30)				            	      					//600ms�����������������
	{
		PIDcount=0;                                         
		pre_error  = last_error;
		last_error = error;
		T_ds18b20=T_ds18b20*0.7f+T_ds18b20_new*0.3f;        //�����˲�
		error=T-T_ds18b20;			                            //�����ֵ��С100��
		if(500<=error<1000)                                 //���¶����趨ֵ���5~10�Ƚ���PID����
		{
		 Det=Kp*(error-last_error);
		 maikuan=maikuan+	Det;
		}
	    if(error<500)                                     //���¶����趨ֵ���С��5��ʱ����PID����
		{
		 Det=(Kp*(error-last_error)+Ki*error+Kd*(error-2*last_error+pre_error)); //����ʽPID�����u(k)=Kp*[e(k)-e(k-1)]+Ki*e(k)+Kd[e(k)-2*e(k-1)+e*(k-2)]
		 maikuan=maikuan+	Det;
		}
		
		else 
		    maikuan=100;	
	 	if (maikuan>100)	 
			  maikuan=100;
	  if (maikuan<=0)	  
			  maikuan=0;
	}
}

/*******************************************************************************
* ������         : xianshi()
* ��������		   : ��ʾ����
* ����           : ��
* ���         	 : ��
*******************************************************************************/	

void xianshi()
{

	 	if(xianshicount>=40)					   			//���800��msһ��   ������Ļ��ʾ
	{
		xianshicount=0;
		LCD_dis_data_f(1,3,T);                //��ʾ�趨�¶�
		Delay1ms(1);                          
		LCD_dis_data_f(2,3,T_ds18b20);       //��ʾ�����¶�
		Delay1ms(1);

	}
}

/*******************************************************************************
* ������         : read_temperature()
* ��������		   : ��ȡ�¶�
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void read_temperature()
{
	if(ds18b20count>=5)
	{
	   	ds18b20count=0;                         //ds18b20����������
		T_ds18b20_new=Ds18b20_Read_Temp();				//��ȡ�¶�ֵ	
	}
}

sbit number=P0^3;
int a=0;
void design()
{
	 	if(number=1)					   			
	{	
		LCD_dis_data_f(2,4,a+=10);               
		Delay1ms(1000);
	}
}

/*******************************************************************************
* ������         : main()
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{  
	LcdInit();                                  //Һ������ʼ��
	DisplayChar(1,0,"PV:");                     //����ʱ��Ϊ�Լ���������ĸ
	Delay1ms(10); 
	DisplayChar(0,0,"SV:");                      //ѧ�ź���λ15
	Delay1ms(10);
	Ds18b20_Init();                             //Ds18b20�¶ȴ�������ʼ��
	Init_Timer0();	                            //��ʱ��0��ʼ��		
  while(1) 
		  {	
				PID();	                              //PID�㷨����
				xianshi();                            //Һ������ʾ����
			  read_temperature();                   //��ȡ�¶Ⱥ���
				//design();
			}
}