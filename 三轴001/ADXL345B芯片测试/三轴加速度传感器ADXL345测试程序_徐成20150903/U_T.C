/**************************
使用头文件如下：
**************************/
#include "STC15F2K60S2.H"

#define   uchar unsigned char
#define   uint unsigned int	
sbit	  SCL=P2^5;//P1^0;      //IIC时钟引脚定义
sbit 	  SDA=P2^6;//P1^1;      //IIC数据引脚定义
sbit	  SEL3=P2^3;

#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A
#define	ADXL345_Begin_Address   0x1D	
#define	ADXL345_End_Address     0x39

typedef unsigned char  BYTE;

BYTE BUF[8];                         //接收数据缓存区      	

void UartInit(void)		//1200bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0x00;		//设定定时初值
	T2H = 0xF7;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
}

/*******************************/
void delay(unsigned int k)	
{						
uint i,j;				
for(i=0;i<k;i++)
{			
for(j=0;j<121;j++)			
{;}}						
}

void Delay5us()
{
	char n =10;//560
    while (n--);
}
 
void ADXL345_Start()
{
    SDA = 1;                    //拉高数据线
	Delay5us(); 
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
	Delay5us(); 
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{
    SCL = 1;    			    //拉高时钟线
	Delay5us(); 
    SDA = 0;                    //拉低数据线               
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
	Delay5us(); 
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit ADXL345_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
// while(SDA)	;
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        Delay5us();             //延时
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE ADXL345_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(uchar REG_Address,uchar REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uchar Single_Read_ADXL345(uchar REG_Address)
{  uchar REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);                   //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
   Single_Write_ADXL345(0x31,0x0b);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式:测量模式   参考pdf24页
}

//******主程序********
void main()
{ 
  char  i;

    delay(500);	                   //上电延时		

	P0M1=0x00;
    P0M0=0xff;
	SEL3=0;
										

    UartInit();						//初始化串口
    Init_ADXL345();                 //初始化ADXL345
											
    if(Single_Read_ADXL345(0x00)==0xE5)	     			//检查ADXL345芯片是否可以访问：0——不能访问
	                                                    //                             1——可访问（待机模式）
	   {												//                             2——可访问（测量模式、正常情况下）
	    P0=0x06;	                                   	//读出的数据为0XE5,表示时序正确, 显示“1” 
        if(Single_Read_ADXL345(0x2D)==0x08) P0=0x5b;    //读出的数据为0x08 表示给345上电了，显示“2”
       }
 	else P0=0x3f;									    //显示“0” 

	TI=1;
    i=ADXL345_Begin_Address-2;

  while(1)                         //循环
  {    
   while(TI)
    {
 	  TI=0;
	  if(i==ADXL345_Begin_Address-2)    SBUF=0xA5;
	    else if(i==ADXL345_Begin_Address-1) SBUF=0x5A;
		        else   SBUF=Single_Read_ADXL345(i);			   //输出ADXL345内部寄存器值：从 ADXL345_Begin_Address 到 ADXL345_End_Address
	  if(++i>ADXL345_End_Address) i=ADXL345_Begin_Address-2;   //其中（0x33，0x32）为x轴加速度值
	}														   //其中（0x35，0x34）为y轴加速度值
  }															   //其中（0x37，0x36）为z轴加速度值
} 


