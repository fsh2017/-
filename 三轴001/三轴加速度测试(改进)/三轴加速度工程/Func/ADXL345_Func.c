/**********************************
****ADXL345相关数据处理.c文件******
**********************************/
#include "ADXL345_Func.h"
#include <math.h>
uchar standard_Collect_ADXL345_Num[3]={30,20,10};
uchar geY=0,geX=0,shiY=0,shiX=0,geZ=0,shiZ=0;//显示变量uchar 
int x0g[2],y0g[2],z0g[2],x1g,y1g,z1g;//校准时的基准值;
int offX=0,offY=0,offZ=0;//初始偏移值
double factorX=0,factorY=0,factorZ=0;//重力因子
int dataX=0,dataY=0,dataZ=0;	//处理后的x，y，z重力加速度寄存器值
uint sumY=0,sumX=0,sumZ=0;//x，y，z重力加速度寄存器值的累加和
double angleX=0,angleY=0,angleZ=0;//最后计算出的x，y，z轴角度值
int real_Collect_ADXL345_Num=0;//x，y，z轴加速度寄存器值得累加次数
int speed=0;
uchar ready=0,readyX=0,readyY=0,readyZ=0;
uchar collectFlag=0;
int oldZ = 0, newZ = 0, oldX = 0, newX = 0;
int a0 = 0, a1 = 0, a2 = 0, temp = 0;
int a0flag = 1, a1flag = 1, a2flag =1;
int stepDec,stepUni;
int stepNumber = 0;


void Get_X()
{   
	int dis_data;
    dis_data=((Buffer[1]<<8)+Buffer[0])-offX;  //合成数据   
	if(dis_data<0)
		dis_data=-dis_data;
    dataX=dis_data;			
}


void Get_Y()
{   
	int dis_data;  
    dis_data=((Buffer[3]<<8)+Buffer[2])-offY;  //合成数据   
	if(dis_data<0)
		dis_data=-dis_data;
	dataY=dis_data;
}


void Get_Z()
{     
	int dis_data;
    dis_data=((Buffer[5]<<8)+Buffer[4])-offZ;    //合成数据   
	if(dis_data<0)
		dis_data=-dis_data;
    dataZ=dis_data;
}

void Cal_XYZ()
{
	double temp_y,temp_x,temp_z;
	temp_x=((double)sumX)/standard_Collect_ADXL345_Num[speed]*factorX;
	temp_y=((double)sumY)/standard_Collect_ADXL345_Num[speed]*factorY;
	temp_z=((double)sumZ)/standard_Collect_ADXL345_Num[speed]*factorZ;
	angleX=(double)(acos((double)((temp_x/(sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z)))))*180/3.14159265); //X轴角度值
	angleY=(double)(acos((double)((temp_y/(sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z)))))*180/3.14159265);  //Y轴角度值
	angleZ=(double)(acos((double)((temp_z/(sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z)))))*180/3.14159265);  //y轴角度值	
}
void ACC_XYZ(int flag)
{  
	Get_X();
	Get_Y();
	Get_Z();
	sumX+=dataX;
	sumY+=dataY;
	sumZ+=dataZ;
	real_Collect_ADXL345_Num++;
    if(real_Collect_ADXL345_Num==standard_Collect_ADXL345_Num[speed])
	{
		if(flag==0)
		{
			sumX=sumX/standard_Collect_ADXL345_Num[speed]%256;
			sumY=sumY/standard_Collect_ADXL345_Num[speed]%256;
			sumZ=sumZ/standard_Collect_ADXL345_Num[speed]%256;
			shiX=sumX/16;
			geX=sumX%16;
			shiY=sumY/16;
			geY=sumY%16;
			shiZ=sumZ/16;
			geZ=sumZ%16;
			
			if(sumX <= 30){
				a0 = sumX;
				a0flag = 1;
			}
			if(sumX >=50){
				a1 = sumX;
				a1flag = 1;
			}
			if(sumX <=30 && a1flag == 1){
				a2 = sumX;
				a2flag = 1;	
			}
			
			if(a1 - a0 >= 25 && a1-a2 >=25 && a1flag == 1&& a0flag ==1 && a2flag ==1){
				stepNumber++;
				stepDec = stepNumber/10;
				stepUni = stepNumber%10;
				a0 = 0;
				a1 = 0;
				a2 = 0;
				a0flag = 0;
				a1flag = 0;
				a2flag = 0;
			}
			if(a1 -a0 >=25 && a0flag == 1 && a1flag ==1){
				stepNumber++;
				stepDec = stepNumber/10;
				stepUni = stepNumber%10;
				a0flag = 0;
			}	
		}
		
		if(flag==1)
		{
			int tempx,tempy,tempz;
			Cal_XYZ();
			tempx=90-(((int)(angleX*10))/10);
			tempy=90-(((int)(angleY*10))/10);
			tempz=90-(((int)(angleZ*10))/10);
			shiX=tempx/10;
			geX=tempx%10;
			shiY=tempy/10;
			geY=tempy%10;
			shiZ=tempz/10;
			geZ=tempz%10;
			
	
			if(tempx <= 30){
				a0 = tempx;
				a0flag = 1;
			}
			if(tempx >= 50){
				a1 = tempx;
				a1flag = 1;
			}
			if(tempx <=30 && a1flag == 1){
				a2 = tempx;
				a2flag = 1;
			}
	
			if(a1 - a0 >= 25 && a1-a2 >= 25 && a0flag == 1 && a1flag ==1 && a2flag == 1){
				stepNumber++;
				stepDec = stepNumber/10;
				stepUni = stepNumber%10;
				a0flag = 0;
				a1flag = 0;
				a2flag = 0;
			} 
			if(a1 -a0 >=25 && a0flag == 1 && a1flag ==1){
				stepNumber++;
				stepDec = stepNumber/10;
				stepUni = stepNumber%10;
				a0flag = 0;
			}
			if(a1-a2 >= 25 && a1flag ==1 && a2flag == 1){
				stepNumber++;
				stepDec = stepNumber/10;
				stepUni = stepNumber%10;
				a1flag = 0;
				a2flag = 0;		
		}
	}
	real_Collect_ADXL345_Num=0;
	sumY=0;
	sumX=0;
	sumZ=0;
	}
}