/******************************
****ADXL345读写操作.h文件******
******************************/
#ifndef __ADXL345_H_
#define __ADXL345_H_
#include "STC15F2K60S2.h"
#include "Type_Redfine.h"
#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
sbit	  SCL=P2^5;//P1^0;      //IIC时钟引脚定义
sbit 	  SDA=P2^6;//P1^1;      //IIC数据引脚定义
extern uint Buffer[8];//接收数据缓存区
/******************************
功能描述：IIC起始信号
输入：void
输出：void
******************************/
void ADXL345_Start();
/******************************
功能描述：IIC停止信号
输入：void
输出：void
******************************/
void ADXL345_Stop();
/******************************
功能描述：IIC发送应答信号
输入：sbit ack(0:ACK 1:NAK)
输出：void
******************************/
void ADXL345_SendACK(bit ack);
/******************************
功能描述：IIC接收应答信号
输入：void 
输出：sbit (0:ACK 1:NAK)
******************************/
bit ADXL345_RecvACK();
/******************************
功能描述：向IIC总线发送一个字节数据
输入：uchar dat(要发送的一字节数据) 
输出：void
******************************/
void ADXL345_SendByte(uchar dat);
/******************************
功能描述：从IIC总线接收一个字节数据
输入：void
输出：uchar (要发送的一字节数据) 
******************************/
uchar ADXL345_RecvByte();
/******************************
功能描述：往ADXL345某一寄存器写入一字节数据
输入：uchar REG_Address（寄存器地址）,uchar REG_data（要写入的数据）
输出：void
******************************/
void Single_Write_ADXL345(uchar REG_Address,uchar REG_data);
/******************************
功能描述：从ADXL345某一寄存器读取一字节数据
输入：uchar REG_Address（寄存器地址）
输出：uchar REG_data（读取到的数据）
******************************/
uchar Single_Read_ADXL345(uchar REG_Address);
/******************************
功能描述：初始化ADXL345
输入：void
输出：void
******************************/
void Init_ADXL345();
/******************************
功能描述：连续读出ADXL345内部寄存器数据到Buffer中，寄存器地址范围0x32~0x37
输入：void
输出：void
******************************/
void Multiple_Read_ADXL345(void);
#endif