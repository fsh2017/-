/*********************
***定时器控制.c文件***
**********************/
#include "Timer.h"	
#include "Key.h"
#include "LED.h"
#include "ADXL345_Func.h"
uint timer500usNum=0,timer100usNum=0;
void Timer1_Init(void)	  //100微秒@11.0592MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	IE |=0x88;			//开启定时器中断
	TL1 = 0x33;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}	
void Timer0_Init(void)		//100微秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	IE |=0x82;
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}
/******************************
功能描述：定时器0中断服务函数
输入：void
输出：void
******************************/
void Timer0_Interrupt(void) interrupt 1
{
	TR0=0;	
	LED_Scan();
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TR0 = 1;
}
/******************************
功能描述：定时器1中断服务函数
输入：void
输出：void
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
	
	TL1 = 0x33;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	TR1=1;
}