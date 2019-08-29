/*********************
***定时器控制.h文件***
**********************/
#ifndef __Timer_H_
#define __Timer_H_
#include "STC15F2K60S2.H"
#include "Type_Redfine.h"

extern uint timer500usNum,timer100usNum;	//500us时标志位，以及相应的次数
/******************************
功能描述：定时器0初始化函数
输入：void
输出：void
******************************/
void Timer0_Init(void);

/******************************
功能描述：定时器1初始化函数
输入：void
输出：void
******************************/
void Timer1_Init(void);
#endif