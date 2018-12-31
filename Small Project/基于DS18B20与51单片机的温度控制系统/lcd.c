#include "STC12C5A60S2.h"
#include <INTRINS.H>
#include "main.h"
#include "lcd.h"
#include "timer.h"
#include "ds18b20.h"
#include "stdio.h"	
#include "pid.h"	

void DisplayChar(uchar Y,uchar X,uchar *s)
{						
    Y&=1;						
    X&=15;						
    if(Y)	X|=0xC0;					
    else 	X|=0x80;
    while(*s!='\0')
	{
		LcdWriteCom(X++,0);
		LcdWriteData(*s);
		_nop_();
		s++;
	}
	Delay1ms(1);					
}

/*******************************************************************************
* 函数名         : Delay1ms
* 函数功能		   : 延时函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Delay1ms(unsigned int y)			  			//ms级延时函数 不是十分精确
{

	unsigned int x;
	for(y;y>0;y--)
		for(x=1000;x>0;x--);
}

/*******************************************************************************
* 函数名         : WaitForEnable
* 函数功能		 : 等待液晶模块退出忙状态
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void WaitForEnable(void)	
{					
	LCD1602_DATAPINS=0xff;		
	LCD1602_RS=0;LCD1602_RW=1;
	_nop_();
	LCD1602_E=1;
	_nop_();_nop_();
	while(LCD1602_DATAPINS&0x80);	
	LCD1602_E=0;				
}

/*******************************************************************************
* 函数名         : LcdWriteCom
* 函数功能		 : 向LCD写入一个字节的命令
* 输入           : CMD 指令码 	   AttribC=1检查忙状态，AttribC=0不检查忙状态
* 输出         	 : 无
*******************************************************************************/
void LcdWriteCom(uchar CMD,uchar Attribc)  //写入命令
{
	if(Attribc)WaitForEnable();	
	LCD1602_RS=0;LCD1602_RW=0;
	_nop_();
	LCD1602_DATAPINS=CMD;
	_nop_();	
	LCD1602_E=1;
	_nop_();_nop_();
	LCD1602_E=0;
}
/*******************************************************************************
* 函数名         : LcdWriteData
* 函数功能		 : 向LCD写入一个字节的数据
* 输入           : dat
* 输出         	 : 无
*******************************************************************************/		   
void LcdWriteData(uchar dataW)             //写入数据
{
	WaitForEnable();		
  	LCD1602_RS=1;LCD1602_RW=0;
	_nop_();
	LCD1602_DATAPINS=dataW;
	_nop_();	
	LCD1602_E=1;
	_nop_();_nop_();
	LCD1602_E=0;
}
/*******************************************************************************
* 函数名         : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/		   
void LcdInit()						  //LCD初始化子程序
{
	LcdWriteCom(0x32,1);	//将8位总线转为4位总线
	LcdWriteCom(0x38,1);	//在四位线下的初始化
	LcdWriteCom(0x08,1);	//设置数据指针起点
	LcdWriteCom(0x01,1);	//清屏
	LcdWriteCom(0x06,1);	//写一个指针加1
	LcdWriteCom(0x0c,1); 	//开显示不显示光标
	Delay1ms(30);
//	DisplayChar(1,0,"liuhongzhi");
//	Delay1ms(1000);
//	DisplayChar(2,3,"201506010615");
//	Delay1ms(1000);
//	LcdWriteCom(0x01,1);	//清屏
//	Delay1ms(10);
//	DisplayChar(1,3,"Temperature");
//	Delay1ms(100);
//	DisplayChar(2,5,"Control");
//	Delay1ms(1500);
}

void LCD_dis_data_f(uchar x,uchar y,uint dat)								 //带小数点版本		 显示两位小数的浮点数
{
   uchar pos,j=0,i=0,str[6];
	switch(x%2)
	{
		case 1:pos=0x80+y;break; //第一行
		case 0:pos=0xc0+y;break; //第二行
	}
	LcdWriteCom(pos,0);		   		 //写入定位命令
	if( dat>=0  && dat < 65535 )
	{	
			if(dat<=9)
				{
					str[0]=' ';			   //填空位
					str[1]=0+0x30;
					str[2]='.';	
					str[3]=0+0x30;
					str[4]=dat%10+0x30;
					str[5]='\0';
				}
	   else if(dat>9  && dat <= 99)
	   			{				

					str[0]=' ';			   //填空位
					str[1]=0+0x30;
					str[2]='.';	
					str[3]=dat/10%10+0x30;
					str[4]=dat%10+0x30;
					str[5]='\0';
				}
	   else if(dat>99  && dat <= 999)
	   			{
					str[0]=' ';			   //填空位
					str[1]=dat/100%10+0x30;
					str[2]='.';	
					str[3]=dat/10%10+0x30;
					str[4]=dat%10+0x30;
					str[5]='\0';
				}
	   else if(dat>999)
	   			{
					str[0]=dat/1000%10+0x30;
					str[1]=dat/100%10+0x30;
					str[2]='.';	
					str[3]=dat/10%10+0x30;
					str[4]=dat%10+0x30;
					str[5]='\0';
				}
	 }
	while(str[i] != '\0')
    {
        LcdWriteData(str[i++]);	//写一个字符，指向下一个
    }

}

//void xianshi()
//{
//	 	if(xianshicount>=40)					   			//大概800多ms一次   用于屏幕显示
//	{
//		xianshicount=0;
//		LCD_dis_data_f(1,2,T);
//		Delay1ms(1);
//		LCD_dis_data_f(1,10,T_ds18b20);
//		Delay1ms(1);
//	}
//}
