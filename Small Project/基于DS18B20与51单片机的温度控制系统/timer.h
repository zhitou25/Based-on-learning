#ifndef __timer_H_
#define __timer_H_
#include "main.h"

extern unsigned int ds18b20count;								//用于定时快速任务
extern unsigned int PIDcount;								//用于中时快速任务
extern unsigned int xianshicount;								//用于慢速时快速任务
void Init_Timer0();


#endif