#ifndef __main_H_
#define __main_H_
#include "STC12C5A60S2.h"
/******************************∫Í∂®“Â***************************/
#define uint unsigned int 
#define uchar unsigned char

sbit KT        =   P3^3;
extern int  maikuan;
extern int  T_ds18b20;
extern int  T;
void PID();
void	xianshi();
void read_temperature();


#endif