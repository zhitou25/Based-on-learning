#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"

//int    T_ds18b20=0,T_ds18b20_new=0;			//DS18B20�ⶨ���¶�
//int    T=6000;    								//Ŀ���¶� ��ʼ����Ϊ50��  �Ŵ�һ�ٱ�	������Ϊint�� �����и�	   
//int    maikuan=50;							//ռ�ձ� ���100
//int    Det=0;					
//float  Kp=30, Ki=0.6,Kd=10;							//	PID����		   KP�����һ��
//int   error=0,last_error=0,pre_error=0;


//void PID()
//{
//	if(PIDcount>=30)					   					//���600��msһ��  ���ڵ����������
//	{
//		PIDcount=0;
//		pre_error  = last_error;
//		last_error = error;
//		T_ds18b20=T_ds18b20*0.7f+T_ds18b20_new*0.3f; 
//		error=T-T_ds18b20;				//�����ֵ��С100��
//		 if(500<=error<1000)
//		{
//		 maikuan=maikuan+	Det;
//		}
//	    if(error<500)
//		{
//		 Det= (Kp*(error-last_error)+Ki*error+Kd*(error-2*last_error+pre_error));//����ʽPID���㹫ʽ
//		 maikuan=maikuan+	Det;
//		}
//		else 
//		maikuan=100;	
//	 	if (maikuan>100)	 
//			  maikuan=100;
//	  if (maikuan<=0)	  
//			  maikuan=0;
//	}
//}