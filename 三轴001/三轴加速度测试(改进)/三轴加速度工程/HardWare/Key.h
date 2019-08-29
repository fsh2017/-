/***********************
****按键扫描.h文件******
***********************/
#ifndef __Key_H_
#define __Key_H_
#include "STC15F2K60S2.H"
#include "Type_Redfine.h"
#define KEYNUM 8			//板子上的按键总数
#define SENSITIVITY 50		   //
#define KEY_SCAN_FREQUENCY 2   //按键扫描频率
#define PRESSNUM (0x80+(SENSITIVITY/3*2))
extern uchar keyFuncFlag,keyScanFlag,keyNum;	   //按键扫描相关标志位
/***按键扫描计数结构体***/
struct  keyStruct{
	uint pressNum[KEYNUM];
	uint previousState[KEYNUM];
	uint presentState[KEYNUM];		 
};
extern struct keyStruct keyValue;
/******************************
功能描述：初始化按键相关AD
输入：void
输出：void
******************************/
void AD_Init(void);
/******************************
功能描述：获取按键AD值
输入：void
输出：uint
******************************/
uint AD_Get(void);
/******************************
功能描述：按键扫描
输入：void
输出：void
******************************/
void Key_Scan(void);
/******************************
功能描述：按下不同的按键做相应的动作
输入：void
输出：void
******************************/
void Key_Func();
#endif