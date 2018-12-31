#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"

//int    T_ds18b20=0,T_ds18b20_new=0;			//DS18B20测定的温度
//int    T=6000;    								//目标温度 初始化设为50度  放大一百倍	类型需为int型 有正有负	   
//int    maikuan=50;							//占空比 最大100
//int    Det=0;					
//float  Kp=30, Ki=0.6,Kd=10;							//	PID参数		   KP需调大一点
//int   error=0,last_error=0,pre_error=0;


//void PID()
//{
//	if(PIDcount>=30)					   					//大概600多ms一次  用于调整输出脉宽
//	{
//		PIDcount=0;
//		pre_error  = last_error;
//		last_error = error;
//		T_ds18b20=T_ds18b20*0.7f+T_ds18b20_new*0.3f; 
//		error=T-T_ds18b20;				//误差数值缩小100倍
//		 if(500<=error<1000)
//		{
//		 maikuan=maikuan+	Det;
//		}
//	    if(error<500)
//		{
//		 Det= (Kp*(error-last_error)+Ki*error+Kd*(error-2*last_error+pre_error));//增量式PID计算公式
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