/***********************
**�������ʾ����.h�ļ�**
***********************/
#ifndef __LED_H_
#define __LED_H_
#include "STC15F2K60S2.H"
#include "Type_Redfine.h"
#include "Delay.h"
/***����LED���IO����***/
sbit 		SEL0=P2^0;
sbit 		SEL1=P2^1;
sbit 		SEL2=P2^2;
sbit		SEL3=P2^3;

/***�������ʾ0~F�������***/
extern uint digtalDuan[16];

/******************************
������������ʼ����������IO
���룺void
�����void
******************************/
void LED_Init(void);

/******************************
�����������������ʾ
���룺void
�����void
******************************/
void LED_Display(uint position,uint display_Data);
/******************************
���������������ɨ��
���룺void
�����void
******************************/
void LED_Scan(void);
#endif