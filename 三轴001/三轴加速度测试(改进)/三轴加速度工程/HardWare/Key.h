/***********************
****����ɨ��.h�ļ�******
***********************/
#ifndef __Key_H_
#define __Key_H_
#include "STC15F2K60S2.H"
#include "Type_Redfine.h"
#define KEYNUM 8			//�����ϵİ�������
#define SENSITIVITY 50		   //
#define KEY_SCAN_FREQUENCY 2   //����ɨ��Ƶ��
#define PRESSNUM (0x80+(SENSITIVITY/3*2))
extern uchar keyFuncFlag,keyScanFlag,keyNum;	   //����ɨ����ر�־λ
/***����ɨ������ṹ��***/
struct  keyStruct{
	uint pressNum[KEYNUM];
	uint previousState[KEYNUM];
	uint presentState[KEYNUM];		 
};
extern struct keyStruct keyValue;
/******************************
������������ʼ���������AD
���룺void
�����void
******************************/
void AD_Init(void);
/******************************
������������ȡ����ADֵ
���룺void
�����uint
******************************/
uint AD_Get(void);
/******************************
��������������ɨ��
���룺void
�����void
******************************/
void Key_Scan(void);
/******************************
�������������²�ͬ�İ�������Ӧ�Ķ���
���룺void
�����void
******************************/
void Key_Func();
#endif