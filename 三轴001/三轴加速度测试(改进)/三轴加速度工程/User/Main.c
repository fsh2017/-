#include "HardWare_Config.h"
#include <math.h>
int main(void)
{
 	uchar devid;
  Delay(500);//上电延时	
  LED_Init();	
 	AD_Init();
	Timer0_Init();
 	Timer1_Init();
  Init_ADXL345();                 //初始化ADXL345
  devid=Single_Read_ADXL345(0X00);//读出的数据为0XE5,表示正确
  if(devid!=0xE5)	
  	while(1)
  	{
 
  	}
	Multiple_Read_ADXL345();
	offX=(Buffer[1]<<8)+Buffer[0];
	offY=(Buffer[3]<<8)+Buffer[2];
	offZ=(Buffer[5]<<8)+Buffer[4];
	while(1)
	{
//		LED_Scan();

    	if(keyFuncFlag)
		{
			Key_Func();
			keyFuncFlag=0;
		}
		if(ready==0&&readyX==0&&readyY==0&&readyZ==0&&collectFlag==1)
		{
			
			Multiple_Read_ADXL345();
			ACC_XYZ(0);
			collectFlag=0;
			Delay1ms();
		}
		if(ready==1&&collectFlag==1)
		{
			Multiple_Read_ADXL345();
			ACC_XYZ(1);
			collectFlag=0;
			Delay1ms();
		}  		  	  
	}
}