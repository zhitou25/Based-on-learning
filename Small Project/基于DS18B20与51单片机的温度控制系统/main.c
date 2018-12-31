#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"


int    T_ds18b20=0;               //惯性滤波后的温度
int    T_ds18b20_new=0;			      //DS18B20测定的温度
int    T=7500;                                  								//目标温度 放大一百倍	类型需为int型 有正有负	   
int    maikuan=50;							  //占空比 最大100
int    Det=0;					            //PID计算值△u(k)
float  Kp=20;                     //PID公式中比例系数
float  Ki=0.6;                    //PID公式中积分系数 
float  Kd=10;							        //PID公式中微分系数
float  error=0;                   //当前偏差即       e(k)
float  last_error=0;              //上次偏差即       e(k-1)
float  pre_error=0;               //上上次偏差即     e(k-2)

/*******************************************************************************
* 函数名         : PID()
* 函数功能		   : PID计算
* 输入           : 当前温度
* 输出         	 : 需调整的PWM波的占空比
*******************************************************************************/	

void PID()
{
	if(PIDcount>=30)				            	      					//600ms对输出脉宽做出调整
	{
		PIDcount=0;                                         
		pre_error  = last_error;
		last_error = error;
		T_ds18b20=T_ds18b20*0.7f+T_ds18b20_new*0.3f;        //惯性滤波
		error=T-T_ds18b20;			                            //误差数值缩小100倍
		if(500<=error<1000)                                 //当温度与设定值相差5~10度进入PID计算
		{
		 Det=Kp*(error-last_error);
		 maikuan=maikuan+	Det;
		}
	    if(error<500)                                     //当温度与设定值相差小于5度时进入PID计算
		{
		 Det=(Kp*(error-last_error)+Ki*error+Kd*(error-2*last_error+pre_error)); //增量式PID计算△u(k)=Kp*[e(k)-e(k-1)]+Ki*e(k)+Kd[e(k)-2*e(k-1)+e*(k-2)]
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
* 函数名         : xianshi()
* 函数功能		   : 显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/	

void xianshi()
{

	 	if(xianshicount>=40)					   			//大概800多ms一次   用于屏幕显示
	{
		xianshicount=0;
		LCD_dis_data_f(1,3,T);                //显示设定温度
		Delay1ms(1);                          
		LCD_dis_data_f(2,3,T_ds18b20);       //显示测量温度
		Delay1ms(1);

	}
}

/*******************************************************************************
* 函数名         : read_temperature()
* 函数功能		   : 读取温度
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void read_temperature()
{
	if(ds18b20count>=5)
	{
	   	ds18b20count=0;                         //ds18b20计数器清零
		T_ds18b20_new=Ds18b20_Read_Temp();				//读取温度值	
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
* 函数名         : main()
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void main()
{  
	LcdInit();                                  //液晶屏初始化
	DisplayChar(1,0,"PV:");                     //考核时改为自己姓名首字母
	Delay1ms(10); 
	DisplayChar(0,0,"SV:");                      //学号后两位15
	Delay1ms(10);
	Ds18b20_Init();                             //Ds18b20温度传感器初始化
	Init_Timer0();	                            //定时器0初始化		
  while(1) 
		  {	
				PID();	                              //PID算法函数
				xianshi();                            //液晶屏显示函数
			  read_temperature();                   //读取温度函数
				//design();
			}
}