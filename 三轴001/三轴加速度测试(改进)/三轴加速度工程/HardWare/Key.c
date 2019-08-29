#include "Key.h"
#include "ADXL345_Func.h"
#include <math.h>
uchar keyFuncFlag=0,keyScanFlag=0,keyNum=0;
struct keyStruct keyValue={{PRESSNUM,PRESSNUM,PRESSNUM,PRESSNUM,PRESSNUM,PRESSNUM,PRESSNUM,PRESSNUM},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}};

uint AD_Get(void)
{
	uint tempAD;
	if(ADC_CONTR&0x10)
	{
		ADC_CONTR &=0xef;
		ADC_CONTR |=0x08;
		tempAD=ADC_RES>>5;
		return tempAD;
	}
	return 0x07;
}
void AD_Init(void)
{
	P1ASF=0x80;
	ADC_CONTR=0x8F;
	CLK_DIV=0x00;
	ADC_RES=0x00;
}
void Key_Scan(void)
{
	uint i;
	uint tempKey;
	if(keyScanFlag)
	{
		keyScanFlag=0;
		if(P32==0)
			keyValue.pressNum[0]--;
		if(P33==0)
			keyValue.pressNum[1]--;
		tempKey=AD_Get();
		switch(tempKey){
			case 0:keyValue.pressNum[2]--;break;
			case 1:keyValue.pressNum[3]--;break;
			case 2:keyValue.pressNum[4]--;break;
			case 3:keyValue.pressNum[5]--;break;
			case 4:keyValue.pressNum[6]--;break;
			case 5:keyValue.pressNum[7]--;break;
			default:break;
		}
		if(keyNum==SENSITIVITY)
		{	
			keyFuncFlag=1;
			for(i=0;i<8;i++)
			{
				if(keyValue.pressNum[i]<0x80)
				{
					 
					keyValue.previousState[i]=keyValue.presentState[i];
					keyValue.presentState[i]=0;
				}
				else{
					keyValue.previousState[i]=keyValue.presentState[i];
					keyValue.presentState[i]=1;
				}
			}
			keyNum=0;
			for(i=0;i<8;i++)
				keyValue.pressNum[i]=PRESSNUM;	
		}
	}
}

void Key_Func()
 {
 	if((keyValue.previousState[2]==1) && (keyValue.presentState[2]==0))
		{
			ready=0;
			readyX=1;
			geY=0;
			geX=1;
			shiX=0;
			shiY=0;
			geZ=0;
			shiZ=0;
			Multiple_Read_ADXL345();
			z0g[0]=(Buffer[5]<<8)+Buffer[4];
			y0g[1]=(Buffer[3]<<8)+Buffer[2];
			x1g=(Buffer[1]<<8)+Buffer[0];
			if(readyZ==1&&readyY==1&&readyX==1)
			{
				readyX=0;
				readyY=0;
				readyZ=0;
				offX=(x0g[0]+x0g[1])/2;
				offY=(y0g[0]+y0g[1])/2;
				offZ=(z0g[0]+z0g[1])/2;
				factorX=(double)1000/abs(x1g-offX);
				factorY=(double)1000/abs(y1g-offY);
				factorZ=(double)1000/abs(z1g-offZ);
				ready=1;
/*				real_Collect_ADXL345_Num=0;
				sumY=0;
				sumX=0;
				sumZ=0;	  */
			}	   
		}
 	if((keyValue.previousState[1]==1) && (keyValue.presentState[1]==0))
		{
			ready=0;
			readyY=1;
			geY=0;
			geX=2;
			shiX=0;
			shiY=0;
			geZ=0;
			shiZ=0;
			Multiple_Read_ADXL345();
			x0g[1]=(Buffer[1]<<8)+Buffer[0];
			z0g[1]=(Buffer[5]<<8)+Buffer[4];
			y1g=(Buffer[3]<<8)+Buffer[2];
			if(readyX==1&&readyY==1&&readyZ==1)
			{
				readyX=0;
				readyY=0;
				readyZ=0;
				offX=(x0g[0]+x0g[1])/2;
				offY=(y0g[0]+y0g[1])/2;
				offZ=(z0g[0]+z0g[1])/2;
				factorX=(double)1000/abs(x1g-offX);
				factorY=(double)1000/abs(y1g-offY);
				factorZ=(double)1000/abs(z1g-offZ);
				ready=1;
/*				real_Collect_ADXL345_Num=0;
				sumY=0;
				sumX=0;
				sumZ=0;   */
			} 
		}
		
		if((keyValue.previousState[0]==1) && (keyValue.presentState[0]==0))
		{
			ready=0;
			readyZ=1;
			geY=0;
			geX=3;
			shiX=0;
			shiY=0;
			geZ=0;
			shiZ=0;
			Multiple_Read_ADXL345();
			x0g[0]=(Buffer[1]<<8)+Buffer[0];
			y0g[0]=(Buffer[3]<<8)+Buffer[2];
			z1g=(Buffer[5]<<8)+Buffer[4];
			if((readyX==1)&&(readyY==1)&&(readyZ==1))
			{
				readyX=0;readyY=0;readyZ=0;
				offX=(x0g[0]+x0g[1])/2;
				offY=(y0g[0]+y0g[1])/2;
				offZ=(z0g[0]+z0g[1])/2;
				factorX=(double)1000/abs(x1g-offX);
				factorY=(double)1000/abs(y1g-offY);
				factorZ=(double)1000/abs(z1g-offZ);
				ready=1;
/*				real_Collect_ADXL345_Num=0;
				sumY=0;
				sumX=0;
				sumZ=0;	*/
			} 	
		}
 }