/*********************
***��ʱ������.h�ļ�***
**********************/
#ifndef __Timer_H_
#define __Timer_H_
#include "STC15F2K60S2.H"
#include "Type_Redfine.h"

extern uint timer500usNum,timer100usNum;	//500usʱ��־λ���Լ���Ӧ�Ĵ���
/******************************
������������ʱ��0��ʼ������
���룺void
�����void
******************************/
void Timer0_Init(void);

/******************************
������������ʱ��1��ʼ������
���룺void
�����void
******************************/
void Timer1_Init(void);
#endif