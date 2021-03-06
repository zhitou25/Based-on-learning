#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"

/*******************************************************************************
* 函数名         : Ds18b20Init
* 函数功能		   : 初始化
* 输入           : 无
* 输出         	 : 初始化成功返回1，失败返回0
*******************************************************************************/

unsigned char Ds18b20_Init()
{
	unsigned int i=0;
	DS18B20=0;			 //将总线拉低480us~960us	
	 i=1000;
  	while(i>0)i--;
	DS18B20=1;			//然后拉高总线，如果DS18B20做出反应会将在15us~60us后总线拉低
	while(DS18B20)	//等待DS18B20拉低总线
	{
		i++;
		if(i>5000)//等待>5MS
			return 0;//初始化失败	
	}
	return 1;//初始化成功
}

/*******************************************************************************
* 函数名         : Ds18b20WriteByte
* 函数功能		   : 向18B20写入一个字节
* 输入           : com
* 输出         	 : 无
*******************************************************************************/

void Ds18b20_Write_Byte(unsigned char dat)
{ 
	unsigned int i;
	unsigned int j;
	unsigned char testb;
	for(j=0;j<8;j++)
	{
		testb=dat&0x01;
		dat=dat>>1;
	if(testb)     // 写1部分
    {
      DS18B20=0;
	  i=15;
	  while(i>0)i--;
      DS18B20=1;
		i=100;
	  while(i>0)i--;
    }
    else
    {
      DS18B20=0;       //写0部分
	 	i=96;
	  while(i>0)i--;
      DS18B20=1;
	  i=15;
	  while(i>0)i--;
    }

	}
}
/*******************************************************************************
* 函数名         : Ds18b20ReadByte
* 函数功能		   : 读取一个位
* 输入           : com
* 输出         	 : 无
*******************************************************************************/
unsigned char Ds18b20ReadBit(void)
{

	unsigned char i;
   unsigned char dat;
   DS18B20=0;
	  i=15;
	  while(i>0)i--;
   DS18B20=1;
   i++;i++;
   dat=DS18B20;
  	i=96;
   while(i>0)i--;
   return (dat);
}
/*******************************************************************************
* 函数名         : Ds18b20ReadByte
* 函数功能		   : 读取一个字节
* 输入           : com
* 输出         	 : 无
*******************************************************************************/


unsigned char Ds18b20_Read_Byte()
{
unsigned char i,j,dat;
  dat=0;
  for(i=1;i<=8;i++)
  {
    j=Ds18b20ReadBit();
    dat=(j<<7)|(dat>>1);   //读出的数据最低位在最前面，这样刚好//一个字节在DAT里
  }
  return(dat);             //将一个字节数据返回
}
/*******************************************************************************
* 函数名         : Ds18b20ChangTemp
* 函数功能		   : 让18b20开始转换温度
* 输入           : com
* 输出         	 : 无
*******************************************************************************/

void  Ds18b20_start_trans()
{
	Ds18b20_Init();
	Delay1ms(1);
	Ds18b20_Write_Byte(0xcc);		//跳过ROM操作命令		 
	Ds18b20_Write_Byte(0x44);	    //温度转换命令
//	Delay1ms(100);	//等待转换成功，而如果你是一直刷着的话，就不用这个延时了
   
}
/*******************************************************************************
* 函数名         : Ds18b20ReadTempCom
* 函数功能		   : 发送读取温度命令
* 输入           : com
* 输出         	 : 无
*******************************************************************************/

void  Ds18b20_Read_Temp_Com()
{	

	Ds18b20_Init();
	Delay1ms(1);
	Ds18b20_Write_Byte(0xcc);	 //跳过ROM操作命令
	Ds18b20_Write_Byte(0xbe);	 //发送读取温度命令
}
/*******************************************************************************
* 函数名         : Ds18b20ReadTemp
* 函数功能		   : 读取温度
* 输入           : com
* 输出         	 : 无
*******************************************************************************/

int Ds18b20_Read_Temp()
{
	int temp=0;	
	float tp; 
	unsigned char tmh,tml;
	Ds18b20_start_trans();			 	//先写入转换命令
	Ds18b20_Read_Temp_Com();			//然后等待转换完后发送读取温度命令
	tml=Ds18b20_Read_Byte();			//读取温度值共16位，先读低字节
	tmh=Ds18b20_Read_Byte();			//再读高字节
	temp=tmh;
	temp<<=8;
	temp|=tml;
	 
	if(temp < 0)						//当温度值为负数
  	{
		
		temp=temp-1;						//因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=~temp;
		tp=temp;
		temp=tp*0.0625f*100+0.5f;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算由�0.5，还是在小数点后面。
  	}
 	else
  	{			
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量									
		temp=tp*0.0625f*100+0.5f;				//如果温度是正的那么，那么正数的原码就是补码它本身
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
	}
	return temp;
}

//void read_temperature()
//{
//	if(ds18b20count>=5)
//	{
//	   	ds18b20count=0;
//		T_ds18b20_new=Ds18b20_Read_Temp();				//读取温度值	
//	}
//}