/*************************
***数码管显示控制.c文件***
**************************/
#include "LED.h"
#include "Delay.h"
#include "ADXL345_Func.h"
uint digtalDuan[16]={0x3f,0x06,0x5b,0x4f,
						0x66,0x6d,0x7d,0x07,
						0x7f,0x6f,0x77,0x7c,
						0x39,0x5e,0x79,0x71};
void LED_Init(void)
{
	P0M1=0x00;
    P0M0=0xff;
	P2M1=0x00;
	P2M0=0x08;
	SEL3=0;	
}

void LED_Display(uint position,uint display_Data)
{
	SEL2=position/4;
	SEL1=position%4/2;
	SEL0=position%2;
	P0=digtalDuan[display_Data];
}
void LED_Scan()
{
	LED_Display(0,shiX);
	Delay5us();
	P0=0X00;
	LED_Display(1,geX);
	Delay5us();
	P0=0X00;
	/*LED_Display(3,shiZ);
	Delay5us();
	P0=0X00;
	LED_Display(4,geZ);
	Delay5us();
	P0=0X00;*/
	LED_Display(6,stepDec); 
	Delay5us();
	P0=0X00;  
	LED_Display(7,stepUni);
	Delay5us();
	P0=0X00;	
}