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
* ������         : Delay1ms
* ��������		   : ��ʱ����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Delay1ms(unsigned int y)			  			//ms����ʱ���� ����ʮ�־�ȷ
{

	unsigned int x;
	for(y;y>0;y--)
		for(x=1000;x>0;x--);
}

/*******************************************************************************
* ������         : WaitForEnable
* ��������		 : �ȴ�Һ��ģ���˳�æ״̬
* ����           : ��
* ���         	 : ��
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
* ������         : LcdWriteCom
* ��������		 : ��LCDд��һ���ֽڵ�����
* ����           : CMD ָ���� 	   AttribC=1���æ״̬��AttribC=0�����æ״̬
* ���         	 : ��
*******************************************************************************/
void LcdWriteCom(uchar CMD,uchar Attribc)  //д������
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
* ������         : LcdWriteData
* ��������		 : ��LCDд��һ���ֽڵ�����
* ����           : dat
* ���         	 : ��
*******************************************************************************/		   
void LcdWriteData(uchar dataW)             //д������
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
* ������         : LcdInit()
* ��������		 : ��ʼ��LCD��
* ����           : ��
* ���         	 : ��
*******************************************************************************/		   
void LcdInit()						  //LCD��ʼ���ӳ���
{
	LcdWriteCom(0x32,1);	//��8λ����תΪ4λ����
	LcdWriteCom(0x38,1);	//����λ���µĳ�ʼ��
	LcdWriteCom(0x08,1);	//��������ָ�����
	LcdWriteCom(0x01,1);	//����
	LcdWriteCom(0x06,1);	//дһ��ָ���1
	LcdWriteCom(0x0c,1); 	//����ʾ����ʾ���
	Delay1ms(30);
//	DisplayChar(1,0,"liuhongzhi");
//	Delay1ms(1000);
//	DisplayChar(2,3,"201506010615");
//	Delay1ms(1000);
//	LcdWriteCom(0x01,1);	//����
//	Delay1ms(10);
//	DisplayChar(1,3,"Temperature");
//	Delay1ms(100);
//	DisplayChar(2,5,"Control");
//	Delay1ms(1500);
}

void LCD_dis_data_f(uchar x,uchar y,uint dat)								 //��С����汾		 ��ʾ��λС���ĸ�����
{
   uchar pos,j=0,i=0,str[6];
	switch(x%2)
	{
		case 1:pos=0x80+y;break; //��һ��
		case 0:pos=0xc0+y;break; //�ڶ���
	}
	LcdWriteCom(pos,0);		   		 //д�붨λ����
	if( dat>=0  && dat < 65535 )
	{	
			if(dat<=9)
				{
					str[0]=' ';			   //���λ
					str[1]=0+0x30;
					str[2]='.';	
					str[3]=0+0x30;
					str[4]=dat%10+0x30;
					str[5]='\0';
				}
	   else if(dat>9  && dat <= 99)
	   			{				

					str[0]=' ';			   //���λ
					str[1]=0+0x30;
					str[2]='.';	
					str[3]=dat/10%10+0x30;
					str[4]=dat%10+0x30;
					str[5]='\0';
				}
	   else if(dat>99  && dat <= 999)
	   			{
					str[0]=' ';			   //���λ
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
        LcdWriteData(str[i++]);	//дһ���ַ���ָ����һ��
    }

}

//void xianshi()
//{
//	 	if(xianshicount>=40)					   			//���800��msһ��   ������Ļ��ʾ
//	{
//		xianshicount=0;
//		LCD_dis_data_f(1,2,T);
//		Delay1ms(1);
//		LCD_dis_data_f(1,10,T_ds18b20);
//		Delay1ms(1);
//	}
//}
