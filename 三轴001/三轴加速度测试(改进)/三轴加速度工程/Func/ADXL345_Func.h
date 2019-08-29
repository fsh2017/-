/**********************************
****ADXL345相关数据处理.h文件******
**********************************/
#ifndef __ADXL345_Func_H_
#define __ADXL345_Func_H_
#include "ADXL345.h"
#define COLLECT_ADXL345_FREQUENCY 12		 //ADXL345数据采集频率
extern uchar standard_Collect_ADXL345_Num[3];//ADXL345数据更新采集次数
extern uchar geY,geX,shiY,shiX,geZ,shiZ;//X,Y,Z轴倾斜角的高地位值 
extern int x0g[2],y0g[2],z0g[2],x1g,y1g,z1g,stepDec,stepUni;//校准时的基准值;
extern int offX,offY,offZ;//初始偏移值
extern double factorX,factorY,factorZ;//重力因子
extern int dataX,dataY,dataZ;	//处理后的x，y，z重力加速度寄存器值
extern uint sumY,sumX,sumZ;//x，y，z重力加速度寄存器值的累加和
extern double angleX,angleY,angleZ;//最后计算出的x，y，z轴角度值
extern int real_Collect_ADXL345_Num;//x，y，z轴加速度寄存器值得累加次数
extern int speed;  //数据更新速度，与standard_Collect_ADXL345_Num[speed]使用
extern uchar ready,readyX,readyY,readyZ; //初始数据采集标志位（校准）
extern uchar collectFlag; //数据采集标志位
/******************************
功能描述：获取x轴加速度偏移值
输入：void
输出：void
******************************/
void Get_X();

/******************************
功能描述：获取y轴加速度偏移值
输入：void
输出：void
******************************/
void Get_Y();

/******************************
功能描述：获取z轴加速度偏移值
输入：void
输出：void
******************************/
void Get_Z();

/******************************
功能描述：计算X,Y,Z轴倾斜角
输入：void
输出：void
******************************/
void Cal_XYZ();
/******************************
功能描述：累加n次X,Y,Z轴加速度值，用于求平均值
输入：int flag
输出：void
******************************/
void ACC_XYZ(int flag);
#endif