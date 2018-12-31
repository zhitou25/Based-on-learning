#ifndef __ds18b20_H_
#define __ds18b20_H_


extern int  T_ds18b20_new;			//DS18B20²â¶¨µÄÎÂ¶È
sbit DS18B20   =   P2^0;

unsigned char Ds18b20_Init();
void Ds18b20_Write_Byte(unsigned char dat);
unsigned char Ds18b20ReadBit(void);
unsigned char Ds18b20_Read_Byte();
void  Ds18b20_start_trans();
void  Ds18b20_Read_Temp_Com();
int Ds18b20_Read_Temp();
//void read_temperature();

#endif

