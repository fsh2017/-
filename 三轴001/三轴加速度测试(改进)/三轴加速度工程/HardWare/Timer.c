/*********************
***��ʱ������.c�ļ�***
**********************/
#include "Timer.h"	
#include "Key.h"
#include "LED.h"
#include "ADXL345_Func.h"
uint timer500usNum=0,timer100usNum=0;
void Timer1_Init(void)	  //100΢��@11.0592MHz
{
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	IE |=0x88;			//������ʱ���ж�
	TL1 = 0x33;		//���ö�ʱ��ֵ
	TH1 = 0xFE;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}	
void Timer0_Init(void)		//100΢��@11.0592MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	IE |=0x82;
	TL0 = 0xA4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}
/******************************
������������ʱ��0�жϷ�����
���룺void
�����void
******************************/
void Timer0_Interrupt(void) interrupt 1
{
	TR0=0;	
	LED_Scan();
	TL0 = 0xA4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TR0 = 1;
}
/******************************
������������ʱ��1�жϷ�����
���룺void
�����void
******************************/
void Timer1_Interrupt(void) interrupt 3
{
	TR1=0;
	timer500usNum++;
	if(timer500usNum%KEY_SCAN_FREQUENCY==0)
	{
	   keyNum++;
	   keyScanFlag=1;
	   Key_Scan();	
	}
	if(timer500usNum%COLLECT_ADXL345_FREQUENCY ==0)
	{
		timer500usNum=0;
		collectFlag=1;
	}
	
	TL1 = 0x33;		//���ö�ʱ��ֵ
	TH1 = 0xFE;		//���ö�ʱ��ֵ
	TR1=1;
}