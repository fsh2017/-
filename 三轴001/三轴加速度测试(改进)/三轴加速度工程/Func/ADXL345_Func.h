/**********************************
****ADXL345������ݴ���.h�ļ�******
**********************************/
#ifndef __ADXL345_Func_H_
#define __ADXL345_Func_H_
#include "ADXL345.h"
#define COLLECT_ADXL345_FREQUENCY 12		 //ADXL345���ݲɼ�Ƶ��
extern uchar standard_Collect_ADXL345_Num[3];//ADXL345���ݸ��²ɼ�����
extern uchar geY,geX,shiY,shiX,geZ,shiZ;//X,Y,Z����б�ǵĸߵ�λֵ 
extern int x0g[2],y0g[2],z0g[2],x1g,y1g,z1g,stepDec,stepUni;//У׼ʱ�Ļ�׼ֵ;
extern int offX,offY,offZ;//��ʼƫ��ֵ
extern double factorX,factorY,factorZ;//��������
extern int dataX,dataY,dataZ;	//������x��y��z�������ٶȼĴ���ֵ
extern uint sumY,sumX,sumZ;//x��y��z�������ٶȼĴ���ֵ���ۼӺ�
extern double angleX,angleY,angleZ;//���������x��y��z��Ƕ�ֵ
extern int real_Collect_ADXL345_Num;//x��y��z����ٶȼĴ���ֵ���ۼӴ���
extern int speed;  //���ݸ����ٶȣ���standard_Collect_ADXL345_Num[speed]ʹ��
extern uchar ready,readyX,readyY,readyZ; //��ʼ���ݲɼ���־λ��У׼��
extern uchar collectFlag; //���ݲɼ���־λ
/******************************
������������ȡx����ٶ�ƫ��ֵ
���룺void
�����void
******************************/
void Get_X();

/******************************
������������ȡy����ٶ�ƫ��ֵ
���룺void
�����void
******************************/
void Get_Y();

/******************************
������������ȡz����ٶ�ƫ��ֵ
���룺void
�����void
******************************/
void Get_Z();

/******************************
��������������X,Y,Z����б��
���룺void
�����void
******************************/
void Cal_XYZ();
/******************************
�����������ۼ�n��X,Y,Z����ٶ�ֵ��������ƽ��ֵ
���룺int flag
�����void
******************************/
void ACC_XYZ(int flag);
#endif