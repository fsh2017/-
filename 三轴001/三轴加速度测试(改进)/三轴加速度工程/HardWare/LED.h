/***********************
**数码管显示控制.h文件**
***********************/
#ifndef __LED_H_
#define __LED_H_
#include "STC15F2K60S2.H"
#include "Type_Redfine.h"
#include "Delay.h"
/***定义LED相关IO引脚***/
sbit 		SEL0=P2^0;
sbit 		SEL1=P2^1;
sbit 		SEL2=P2^2;
sbit		SEL3=P2^3;

/***数码管显示0~F相关数据***/
extern uint digtalDuan[16];

/******************************
功能描述：初始化数码管相关IO
输入：void
输出：void
******************************/
void LED_Init(void);

/******************************
功能描述：数码管显示
输入：void
输出：void
******************************/
void LED_Display(uint position,uint display_Data);
/******************************
功能描述：数码管扫描
输入：void
输出：void
******************************/
void LED_Scan(void);
#endif