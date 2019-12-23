/*
 * Sine_wave.c
 *
 *  Created on: 2014年8月25日
 *      Author: Sam
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c1294ncpdt.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_epi.h"
#include "inc/hw_ints.h"
#include "driverlib/epi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"
#include "driverlib/fpu.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
//#include "TFTinit/picture.h"
//#include "TOUCHinit/TOUCH_TSC2046.h"
#include "EPIinit/EPIinit.h"

//
// Select floating-point math.
//
//#define MATH_TYPE FLOAT_MATH

#include "IQmath/IQmathLib.h"
#include "math.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"

// Provide a definition for M_PI, if it was not provided by math.h.
//
//*****************************************************************************


#ifndef M_PI
#define M_PI                    3.14159265358979323846F
#endif

#define MAX_CHAR_POSX 230
#define MAX_CHAR_POSY 390
// System clock rate in Hz.
//
//*****************************************************************************
uint32_t g_ui32SysClock;

//*****************************************************************************
//
// A counter for system clock ticks, used for tracking time.
//
//*****************************************************************************
static volatile unsigned long g_ulTickCount;

#define SERIES_LENGTH 240

//*****************************************************************************
//
// Creates a buffer for holding the values of the data series.  It must be
// large enough to hold the maximum number of data points in the series that
// will be shown on the strip chart.
//
//*****************************************************************************

typedef struct _Series
{
	uint32_t xAxis;
	int32_t data;
}tSeries;
static tSeries g_cSeries[240];


//*****************************************************************************
//
// The number of SysTick ticks per second.
//
//*****************************************************************************
#define TICKS_PER_SECOND 40
#define FSECONDS_PER_TICK (1.0F / (float)TICKS_PER_SECOND)


#ifndef TARGET_IS_SNOWFLAKE_RA0
#define TARGET_IS_SNOWFLAKE_RA0
#endif

#ifndef TARGET_IS_SNOWFLAKE_RA1
#define TARGET_IS_SNOWFLAKE_RA1
#endif

#ifndef TARGET_IS_SNOWFLAKE_RA3
#define TARGET_IS_SNOWFLAKE_RA3
#endif


#ifndef TARGET_IS_SNOWFLAKE_RB1
#define TARGET_IS_SNOWFLAKE_RB1
#endif


#define ROM_IntMasterDisable \
((bool (*)(void))ROM_INTERRUPTTABLE[2])

#define ROM_UARTCharGetNonBlocking                                            \
        ((int32_t (*)(uint32_t ui32Base))ROM_UARTTABLE[13])

//#define int32_t UARTCharGet(uint32_t ui32Base


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

#define ROM_UARTCharsAvail                                                    \
        ((bool (*)(uint32_t ui32Base))ROM_UARTTABLE[11])

#define ROM_UARTCharPutNonBlocking                                            \
        ((bool (*)(uint32_t ui32Base,                                         \
                   unsigned char ucData))ROM_UARTTABLE[15])

#define ROM_SysCtlPeripheralEnable                                            \
        ((void (*)(uint32_t ui32Peripheral))ROM_SYSCTLTABLE[6])

#define ROM_GPIOPinTypeGPIOOutput                                             \
        ((void (*)(uint32_t ui32Port,                                         \
                   uint8_t ui8Pins))ROM_GPIOTABLE[15])

#define ROM_SysCtlPeripheralEnable                                            \
        ((void (*)(uint32_t ui32Peripheral))ROM_SYSCTLTABLE[6])

#define ROM_GPIOPinTypeUART                                                   \
        ((void (*)(uint32_t ui32Port,                                         \
                   uint8_t ui8Pins))ROM_GPIOTABLE[21])

#define ROM_UARTConfigSetExpClk                                               \
        ((void (*)(uint32_t ui32Base,                                         \
                   uint32_t ui32UARTClk,                                      \
                   uint32_t ui32Baud,                                         \
                   uint32_t ui32Config))ROM_UARTTABLE[5])




int f=0;

void myhandermyhandler(void)
{
    if(ROM_UARTCharsAvail(UART6_BASE))
    {
        int32_t x;
        x = ROM_UARTCharGetNonBlocking(UART6_BASE);
        if (x==97){//aaaaa

        	    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1); //PF1输出高，点亮LED0
        	    SysCtlDelay(100*g_ui32SysClock/(100000*3));
        	    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0); //PF1输出低，关闭LED0
        	    f=1;
        }


        if (x==65){//AAAAA

                	    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1); //PF1输出高，点亮LED0
                	    SysCtlDelay(100*g_ui32SysClock/(100000*3));
                	    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0); //PF1输出低，关闭LED0
                	    f=2;
                }


        if(x==66)//BBBBBB
        	f=3;

        if(x==70)//FFFFF
               f=4;
        if(x==71)//GGGGG
                f=5;

        if(x==72)//HHHHH
                 f=6;




        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        SysCtlDelay(g_ui32SysClock/(100000*3));
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);

    }
}


void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    while(ui32Count--)
    {
        ROM_UARTCharPutNonBlocking(UART6_BASE, *pui8Buffer++);
    }
}



#define _NOP() _nop()
#define I2C0_MASTER_BASE 0x40020000
#define I2C0_SLAVE_BASE 0x40020000
#define I2C0_ADDR_TUBE_SEL	      0x30  //00110000
#define I2C0_ADDR_TUBE_SEG_LOW    0x32  //00110010
#define I2C0_ADDR_TUBE_SEG_HIGH  0x34   //00110100
#define PCA9557_REG_INPUT	 0x00
#define PCA9557_REG_OUTPUT	 0x01
#define PCA9557_REG_PolInver 0x02
#define PCA9557_REG_CONFIG	 0x03
#define NUM 0
unsigned char I2C_RECV_DATA[] ={0x00,0x00,0x00,0x00,0x00,0x00};

void I2C_Set_sda_high( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,GPIO_PIN_3);  //拉高PB3
    _NOP();
    _NOP();
    return;
}

/*******************************************
		拉低SDA 信号
********************************************/

void I2C_Set_sda_low ( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,0X00000000);  //拉低PB3
    _NOP();
    _NOP();
    return;
}

/*******************************************
		拉高SCL 信号
********************************************/

void I2C_Set_scl_high( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2,GPIO_PIN_2);  //拉高PB2
    _NOP();
    _NOP();
    return;
}

/*******************************************
		拉低SCL 信号
********************************************/

void I2C_Set_scl_low ( void )
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2,0X00000000);  //拉低PB2
    _NOP();
    _NOP();
    return;
}

/*******************************************
		IIC 信号结束信号函数
********************************************/

void I2C_STOP(void)
{
    int i;
    I2C_Set_sda_low();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_low();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high();
    for(i = NUM+1;i > 0;i--);
    return;
}


/*******************************************
		IIC 信号初始化
********************************************/

void I2C_Initial( void )
{
    I2C_Set_scl_low();
    I2C_STOP();
    return;
}


/*******************************************
		IIC 信号起始信号函数
********************************************/

void I2C_START(void)
{
    int i;

    I2C_Set_sda_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_low();
    for(i = NUM;i > 0;i--);
    I2C_Set_scl_low();
    return;
}

/*******************************************
		IIC 获取应答函数
********************************************/

int  I2C_GetACK(void)
{
    int j;
    _NOP();
    _NOP();
    I2C_Set_scl_low();
    for(j = NUM;j> 0;j--);
    I2C_Set_scl_high();
    for(j = NUM;j> 0;j--);
    I2C_Set_sda_low();
    for(j = NUM;j > 0;j--);
    I2C_Set_scl_low();
    return 1;
}

/*******************************************
		IIC 设置应答函数
********************************************/

void I2C_SetNAk(void)
{
    I2C_Set_scl_low();
    I2C_Set_sda_high();
    I2C_Set_scl_high();
    I2C_Set_scl_low();
    return;
}

/*******************************************
		IIC 发送字节函数
		参数 	1：要发送字节值
		return ：无返回
********************************************/

void I2C_TxByte(unsigned char nValue)
{
    int i;
    int j;
    for(i = 0;i < 8;i++)
    {
    	if(nValue & 0x80)
    	    I2C_Set_sda_high();
    	else
    	    I2C_Set_sda_low();
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_high();
    	nValue <<= 1;
    	for(j = NUM;j > 0;j--);
    	I2C_Set_scl_low();
    }

    return;
}

/*******************************************
		IIC 接收字节函数
		参数 		无
		return ：无返回
********************************************/
unsigned char  I2C_RxByte(void)
{
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);//配置PB3为输入口
    unsigned char nTemp=0 ;
    int i;

    I2C_Set_sda_high();

    _NOP();
    _NOP();
    _NOP();
    _NOP();
    for(i = 0;i < 8;i++)
    {
    	I2C_Set_scl_high(); //模拟SCL信号
    	if(GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_3) == 0x18) //依次判断PB3（SDA）输入
     	{
    	    nTemp |= (0x01 << (7-i));  //8位SDA数据哪一位为高就置1
    	}
    	I2C_Set_scl_low();
    	//Delay5us();
    }

    return nTemp;

}

/*******************************************
		IIC 发送数组函数
	参数  	1 num : 发送字节数
	    2 device_addr : iic目标地址
	    3 *data	：发送数组地址
	return ：无返回
********************************************/
void i2c_write(int num, unsigned char device_addr,unsigned char *data)
{
    int i = 0;
    int count = num;
    unsigned char *send_data = data;
    unsigned char write_addr = device_addr;

    I2C_Set_scl_high();
    for(i = NUM;i > 0;i--);
    I2C_Set_sda_high();
    for(i = NUM;i > 0;i--);

    for(i = 0;i < count;i++)
    {
      I2C_START();           //模拟I2C写数据的时序
      I2C_TxByte(write_addr);
      I2C_GetACK();
      I2C_TxByte(send_data[i]);
      I2C_GetACK();
      i++;
      I2C_TxByte(send_data[i]);
      I2C_GetACK();
      I2C_STOP();
    }

}

/*******************************************
		IIC 读取数组函数
	参数  	1 num : 发送字节数
	    2 device_addr : iic目标地址
	    3 *data	：接收数组地址
	return ：无返回
********************************************/
void i2c_read(int num, unsigned char device_addr,unsigned char *data)
{
  int i = 0;
  int count = num;
  unsigned char *send_data = data;
  unsigned char read_addr = device_addr;

  I2C_Set_scl_high();
  for(i = NUM;i > 0;i--);
  I2C_Set_sda_high();
  for(i = NUM;i > 0;i--);

  for(i = 0; i < count;i++)
  {
    I2C_START();               //模拟I2C读数据
    I2C_TxByte((read_addr - 1));
    I2C_GetACK();
    I2C_TxByte(send_data[2*i]);
    I2C_GetACK();

    I2C_START();
    I2C_TxByte(read_addr);
    I2C_GetACK();

    I2C_RECV_DATA[i] = I2C_RxByte();
    data[2*i+1]=I2C_RECV_DATA[i];
    I2C_SetNAk();
    I2C_STOP();
  }

}

//*********************************************************************

//*********************************************************************
//******配置I2C0模块的IO引脚，**********************************************
void I2C0GPIOBEnable(void)
{	// Enable GPIO portB containing the I2C pins (PB2&PB3)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3);

}

//******配置PCA9557芯片中连接米字管的各引脚为输出***********************************
void I2C0DeviceInit(void)
{
	unsigned char dataBuf[2] = {PCA9557_REG_CONFIG, 0x00};
	i2c_write(2,I2C0_ADDR_TUBE_SEL,dataBuf);
	i2c_write(2,I2C0_ADDR_TUBE_SEG_LOW,dataBuf);
	i2c_write(2,I2C0_ADDR_TUBE_SEG_HIGH,dataBuf);

}

//*******设置米字管的管选信号**************************************************
void I2C0TubeSelSet(char data)
{   //选择1、2、3、4、5哪个米字管亮
	unsigned char dataBuf[2] = {PCA9557_REG_OUTPUT, data};  //PCA9557_REG_OUTPUT==0x01
	i2c_write(2,I2C0_ADDR_TUBE_SEL,dataBuf);
}
//*******点亮米字管的相应码段**************************************************
void I2C0TubeLowSet(char data)
{  //点亮7-14管脚对应的码段
	unsigned char dataBuf[2] = {PCA9557_REG_OUTPUT, data}; //PCA9557_REG_OUTPUT==0x01
	i2c_write(2,I2C0_ADDR_TUBE_SEG_LOW,dataBuf);
}
void I2C0TubeHighSet(char data)
{  //点亮15-18管脚对应的码段
	unsigned char dataBuf[2] = {PCA9557_REG_OUTPUT, data};
	i2c_write(2,I2C0_ADDR_TUBE_SEG_HIGH,dataBuf);
}

//********预设码段值，方便查找************************************************
static const char tubeCodeTable[10][2]=
		{ //  SegmLow, SegHigh
			{	0x10,	0x3E	},		// 	    	0
			{	0x00,	0x18	},		// 	        1
			{	0x70,	0x2C	},		//      	2
            {	0x70,	0x26	},		//       	3
            {	0x60,	0x32	},		//      	4
            {	0x70,	0x16	},		//     		5
            {	0x70,	0x1E	},		//     		6
            {	0x00,	0x26	},		//     		7
            {	0x70,	0x3E	},		//     		8
            {	0x70,	0x36	},	    //     		9
//            {	0x60,	0x3E	},	    //     		a
		};



//*****************************************************************************
//
// This is the handler for this SysTick interrupt.  It simply increments a
// counter that is used for timing.
//
//********* ********************************************************************
void
SysTickIntHandler(void)
{
    //
    // Update our tick counter.
    //
    g_ulTickCount++;
    if(g_ulTickCount>=320)
    	g_ulTickCount = 0;

}


//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}


void TFTLCD_DrawCircle(int x,int y ,int r){
	int num=800;
	float i;
	_iq24 angle,xi,yi,fr,sin_angle,cos_angle;
	fr=_IQ24(r);
	for(i=0;i<num;i++){
		angle=_IQ24(i/((float)(num/2)))*(float)M_PI;
		sin_angle=_IQ24sin(angle);
		cos_angle=_IQ24cos(angle);
		xi=_IQ24mpy(cos_angle,fr);
		yi=_IQ24mpy(sin_angle,fr);
		TFTLCD_DrawPoint(x+_IQ24int(xi),y+_IQ24int(yi),WHITE);
	}
}


uint32_t loadvalue;

struct Cnote{
	int frequency;
	float time;
};


#define T 1.6 //400ms 四音符
#define B 0.8 //200ms 八音符
#define L 0.4

#define ST 0.5 //400ms 四音符

struct Cnote  friend[]={
{5,T},{1,B},{1,L},{1,B},{3,B},{2,B},{1,L},{2,B},{3,B},
{1,B},{1,L},{3,B},{5,B},{6,T},{6,B},
{5,B},{3,L},{3,B},{1,B},{2,B},{1,L},{2,B},{3,B},
{1,B},{6,L},{6,B},{5,B},{1,T},  //27

{6,B},{5,B},{3,L},{3,B},{1,B},
{2,B},{1,L},{2,B},{6,B},{5,B},{3,L},{3,B},{5,B},
{6,T},{1,B},{5,B},{3,L},{3,B},{1,B},
{2,B},{1,L},{2,B},{3,B},
{1,B},{6,L},{6,B},{5,B},{1,T}  //24

};


struct Cnote  music1[]={{956,T},{852,T},{758,T},{956,T},{956,T},{852,T},{758,T},{956,T},{758,T},{710,T},{638,2*T},{758,T}};


int a[7]={0,523,587,659,698,784,880,988};

int ff[7]={0,698,784,880,988,523,587,659};

struct Cnote  star[]={

		{1,ST},{1,ST},{5,ST},{5,ST},{6,ST},{6,ST},{5,2*ST},
		{4,ST},{4,ST},{3,ST},{3,ST},{2,ST},{2,ST},{1,2*ST},
		{5,ST},{5,ST},{4,ST},{4,ST},{3,ST},{3,ST},{2,2*ST},
		{1,ST},{1,ST},{5,ST},{5,ST},{6,ST},{6,ST},{5,2*ST},
		{4,ST},{4,ST},{3,ST},{3,ST},{2,ST},{2,ST},{1,2*ST}

};





void Sound(struct Cnote *note){
	if(note->frequency!=0){
		//loadvalue = g_ui32SysClock*a[(note->frequency)]/12000;
		//loadvalue = (1/(2*a[(note->frequency)]))*g_ui32SysClock/3000000;
	    uint32_t  temp= 2*ff[(note->frequency)];
		//uint32_t  temp= 2*(note->frequency);


		loadvalue =	(g_ui32SysClock/3)/temp;
		TimerLoadSet(TIMER0_BASE,TIMER_B,10);
		TimerEnable(TIMER0_BASE,TIMER_B);
	}

	SysCtlDelay((g_ui32SysClock/3)*(note->time));
	TimerDisable(TIMER0_BASE,TIMER_B);
	TimerIntClear(TIMER0_BASE,TIMER_TIMB_TIMEOUT);
	SysCtlDelay((5*g_ui32SysClock/16000000));
}

void starSound(struct Cnote *note){
	if(note->frequency!=0){
		//loadvalue = g_ui32SysClock*a[(note->frequency)]/12000;
		//loadvalue = (1/(2*a[(note->frequency)]))*g_ui32SysClock/3000000;
	    uint32_t  temp= 2*a[(note->frequency)];
		//uint32_t  temp= 2*(note->frequency);


		loadvalue =	(g_ui32SysClock/3)/temp;
		TimerLoadSet(TIMER0_BASE,TIMER_B,10);
		TimerEnable(TIMER0_BASE,TIMER_B);
	}

	SysCtlDelay((g_ui32SysClock/3)*(note->time));
	TimerDisable(TIMER0_BASE,TIMER_B);
	TimerIntClear(TIMER0_BASE,TIMER_TIMB_TIMEOUT);
	SysCtlDelay((5*g_ui32SysClock/16000000));
}



void GPIOInitial(void)    //GPIO端口初始化
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);  //使能GPIOD引脚
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOD);//
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1); //设置输出引脚为pin_1

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);  //使能GPIOP引脚
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOP);//
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_2);  //设置输出引脚为pin_2


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);    //使能GPIOL引脚
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOL);//
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);  //设置输出引脚为pin_1,pin_2,pin_3


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);    //使能GPIOL引脚
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOM);//
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);  //设置输出引脚为pin_1,pin_2,pin_3

}
void GPIOIntInitial(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOD);//
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_0);
    GPIOIntTypeSet(GPIO_PORTD_BASE,GPIO_PIN_0,GPIO_LOW_LEVEL);
    GPIOIntEnable(GPIO_PORTD_BASE,GPIO_INT_PIN_0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPION);//
    GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_2);
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_2,GPIO_LOW_LEVEL);
    GPIOIntEnable(GPIO_PORTN_BASE,GPIO_INT_PIN_2);
}

void TimerIntInitial(void)     //定时器初始化
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);   //定时器使能

	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR  | TIMER_CFG_B_PERIODIC);

	//TimerLoadSet(TIMER0_BASE, TIMER_B, g_ui32SysClock/1000 );

	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

void
Timer0BIntHandler(void)    //定时器中断
{
	unsigned long Status;
	TimerDisable(TIMER0_BASE, TIMER_B);
	Status=TimerIntStatus(TIMER0_BASE,true);   //如果检测到定时器中断


	if(Status==TIMER_TIMB_TIMEOUT)
	{
		if(GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_5)!=0x20)
		GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0x20);
			//GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1 , 0xff);
		else
			GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0xdf);
	}



	TimerIntClear(TIMER0_BASE, Status);
	TimerLoadSet(TIMER0_BASE, TIMER_B, loadvalue);
	//TimerLoadSet(TIMER0_BASE, TIMER_B, 1136*g_ui32SysClock/3000000);
	TimerEnable(TIMER0_BASE, TIMER_B);

}
void main()
 {
/*
	      g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
	                                             SYSCTL_OSC_MAIN |
	                                             SYSCTL_USE_PLL |
	                                             SYSCTL_CFG_VCO_480), 120000000);*/
	g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
	                                         SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
	                                         SYSCTL_CFG_VCO_480), 16000000);
    GPIOInitial();
    GPIOIntInitial();
    TimerIntInitial();
    IntPrioritySet(INT_TIMER0B, 0x20);
    IntEnable(INT_TIMER0B); //使能中断
    IntMasterEnable();  //允许处理器响应中断
    TimerEnable(TIMER0_BASE, TIMER_B);//使能定时器

    /*

     struct Cnote *p=star;
     for(;p<star+28;p++)
        	starSound(p);
     p=friend;
     for(;p<friend+51;p++)
            starSound(p);
            */
        TimerDisable(TIMER0_BASE, TIMER_B);
        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0xdf);
	    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
	    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
	    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
	    GPIOPinConfigure(GPIO_PP0_U6RX);
	    GPIOPinConfigure(GPIO_PP1_U6TX);
	    ROM_GPIOPinTypeUART(GPIO_PORTP_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//使能GPIOF
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);//使能GPIOL
	   	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);//配置PF1、PF2、PF3为输出
	   	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);//配置PL0、PL1、PL2、PL3、PL4为输出
	    ROM_UARTConfigSetExpClk(UART6_BASE, g_ui32SysClock, 115200,
	                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
	                             UART_CONFIG_PAR_NONE));
	    SYSCTL_RCGCGPIO_R |= (SYSCTL_RCGCGPIO_R13 | SYSCTL_RCGCGPIO_R12 | SYSCTL_RCGCGPIO_R11 |SYSCTL_RCGCGPIO_R10| SYSCTL_RCGCGPIO_R7 |SYSCTL_RCGCGPIO_R3 |SYSCTL_RCGCGPIO_R5  );
	    GPIO_PORTM_DIR_R = 0x28;
	    GPIO_PORTM_DEN_R = 0x28;
	    UARTSend((uint8_t *)"\033[2JEnter text: ", 16);

         uint16_t ui32Loop = 0,ulItemCount=0,FinishCalculateFlag=0,ulLastTickCount=0;
		 float fElapsedTime;
		_iq24 fRadians,fSine;
		 FPUEnable();
		 FPULazyStackingEnable();
		 SysTickPeriodSet(g_ui32SysClock / TICKS_PER_SECOND);
		 IntMasterEnable();
		 SysTickIntEnable();
         SysTickEnable();
		 EPIGPIOinit();
		 TFT_400x240_OTM4001Ainit(g_ui32SysClock);//初始化TFT_OTM4001
		     // Open BackLight.
		 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
		 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);

		 TFTLCD_ShowString(50,10,"This is God Huan",GREEN,BLACK);
		 TFTLCD_ShowString(60,40,"hello,bitch!",GREEN,BLACK);
		 TFTLCD_DrawHorizontalLine(0,240,63,GREEN);//水平线
		 TFTLCD_DrawHorizontalLine(0,240,128,GREEN);
		 TFTLCD_DrawHorizontalLine(0,240,193,GREEN);
		 TFTLCD_DrawVerticalLine(64,193,0,GREEN);//竖直线
		 TFTLCD_DrawVerticalLine(64,193,239,GREEN);
		 TFTLCD_ShowString(12,46,"1",WHITE,BLACK);
		 TFTLCD_ShowString(2,195,"-1",WHITE,BLACK);
		 LCD_Show_Font(90,275,0);
		 LCD_Show_Font(114,275,1);
		 LCD_Show_Font(138,275,2);

		 I2C0GPIOBEnable();//配置I2C0模块的IO引脚
		 I2C0DeviceInit();//配置PCA9557芯片中连接米字管的各引脚为输出


while(1){

myhandermyhandler();

if(f == 1){
	        		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1); //PF1输出高，点亮LED0
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0); //PF1输出低，关闭LED0

	        		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2); //PF2输出高，点亮LED1
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0); //PF2输出低，点亮LED1

	        		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3);
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0);

	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_0,GPIO_PIN_0);
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_0,0);

	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_1,GPIO_PIN_1);
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_1,0);

	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_2,GPIO_PIN_2);
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_2,0);

	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_3,GPIO_PIN_3);
	        		SysCtlDelay(100*(16000000/3000));         //延时n*1ms
	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_3,0);

	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_4,GPIO_PIN_4);
	        		SysCtlDelay(100*(16000000/3000));
	        		GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_4,0);
	        		f=0;
}

if(f==2){
        //
        // Wait for the next timer tick.
        //
	    	     char x;
	    	     int xpos,ypos;
	    	     xpos=50;ypos=70;
	    	     TFTLCD_CLEAR(BLACK);


	    	    // x = UARTCharGet(UART6_BASE);
	    	     //TFTLCD_ShowChar(50, 70, x ,GREEN,BLACK);
	    	     while(ROM_UARTCharsAvail(UART6_BASE))
	    	         {
	    	             x = ROM_UARTCharGetNonBlocking(UART6_BASE);

	    	             if(xpos>MAX_CHAR_POSX){xpos=0;ypos+=16;}
	    	             if(ypos>MAX_CHAR_POSY){ypos=xpos=0;TFTLCD_CLEAR(BLACK);}
	    	             TFTLCD_ShowChar(xpos, ypos, x ,GREEN,BLACK);
	    	             xpos+=16;

	    	         }

	    }//if (f==2)





/*

	    while(f){
        while(ulLastTickCount == g_ulTickCount)
        {
        }
        ulLastTickCount = g_ulTickCount;
        //
        // Preparing to add a new data point to the strip chart ...
        // If the number count of items in the strip chart has reached the
        // maximum value, then the data points need to "slide down" in the
        // buffer so new data can be added at the end.
        //
        if(ulItemCount == SERIES_LENGTH)
        {
            FinishCalculateFlag = 1;
        }

        //
        // Otherwise, the series data buffer is less than full so just
        // increment the count of data points.
        //
        else
        {
            //
            // Increment the number of items that have been added to the strip
            // chart series data buffer.
            //
        	g_cSeries[ulItemCount].xAxis = ++ulItemCount;
        }
        //
        // Compute the elapsed time in decimal seconds, in floating point
        // format.
        //
        fElapsedTime = (float)g_ulTickCount * FSECONDS_PER_TICK;
        // Convert the time to r
        //
//      fRadians = fElapsedTime * (float)M_PI;
        fRadians = _IQ24(fElapsedTime * (float)M_PI);     //_IQ24 converts a floating-point constant or variable into an IQ number.

        //
        // Adjust the period of the wave.  This will give us a wave period
        // of 4 seconds, or 0.25 Hz.  This number was chosen arbitrarily to
        // provide a nice looking wave on the display.
        //
//        fRadians /= 2.0F;
          fRadians = _IQdiv2(fRadians);        //_IQdiv2 divides fRadians by two.
//        fRadians = _IQdiv4(fRadians);        //Divides fRadians by four.
        //
        // Compute the sine.  Multiply by 0.5 to reduce the amplitude.
        //
        fSine = _IQ24sin(fRadians);         //Computes the sine of the input value.
        //
        // Finally, save the sine value into the last location in the series
        // data point buffer.  Convert the sine amplitude to display pixels.
        // (Amplitude 1 = 64 pixels)
        //
//        g_cSeries[ulItemCount - 1] = fSine*64;
       //g_cSeries[ulItemCount - 1].data = _IQ24mpyI32int(fSine,64); //_IQ24mpyI32int multiplies an IQ number fSine by an integer32, returning the integer portion of the result.

        //c = _IQ24(60*_IQ24asin(fSine));
        //a=a*100;
       // float a=_IQ24asin(fSine);
        //_iq24 c=_IQ24(a);
        if (ulLastTickCount<80)
            g_cSeries[ulItemCount - 1].data = 1.5*ulLastTickCount-60;
        else if (ulLastTickCount>=80 && ulLastTickCount<160)
        	g_cSeries[ulItemCount - 1].data = -1.5*ulLastTickCount+180;
        else if (ulLastTickCount>160 && ulLastTickCount<240)
        	g_cSeries[ulItemCount - 1].data = 1.5*(ulLastTickCount-160)-60;
        else
        	g_cSeries[ulItemCount - 1].data = -1.5*(ulLastTickCount-160)+180;

        if(!FinishCalculateFlag)
        {
        	// If we haven't calculate the sine value, continue to calculate.
        	TFTLCD_DrawPoint(g_cSeries[ulItemCount - 1].xAxis,g_cSeries[ulItemCount - 1].data+128,BLUE);
        }
        else
		{
        	// We need to update sine value per Systick period.
			for(ui32Loop=2;ui32Loop<SERIES_LENGTH;ui32Loop++)
			{
				// Clear the former data.
				TFTLCD_DrawPoint(g_cSeries[ui32Loop-1].xAxis,g_cSeries[ui32Loop-1].data+128,0);
				g_cSeries[ui32Loop-1].data = g_cSeries[ui32Loop].data;
				// Update data.
				TFTLCD_DrawPoint(g_cSeries[ui32Loop-1].xAxis,g_cSeries[ui32Loop-1].data+128,BLUE);
			}
			// Rewrite display information, you can comment the follow programs
			// and see what will change.
//			TFTLCD_ShowString(12,46,"1",WHITE,BLACK);
//			TFTLCD_ShowString(2,195,"-1",WHITE,BLACK);
//			TFTLCD_DrawHorizontalLine(0,240,63,GREEN);
			TFTLCD_DrawHorizontalLine(0,240,128,GREEN);
//			TFTLCD_DrawHorizontalLine(0,240,193,GREEN);
			TFTLCD_DrawVerticalLine(64,192,0,GREEN);
			TFTLCD_DrawVerticalLine(64,192,239,GREEN);
			TFTLCD_DrawCircle(130,280,60);//画圆
		}
             f=0;
	    	}//while(1)
*/


if (f==3){

	while(f==3)
	{
        I2C0TubeSelSet(~0x10); //~0x10==11101111 选中5
		I2C0TubeLowSet(0x10);
		I2C0TubeHighSet(0x34);
		SysCtlDelay(9000);  //延时n*3个指令时间

		I2C0TubeSelSet(0xFF);
	    I2C0TubeLowSet(0x00);
	    I2C0TubeHighSet(0x00);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xDF);//选中DIG1
		I2C0TubeLowSet(0x44);
	    I2C0TubeHighSet(0x22);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xFF);
		I2C0TubeLowSet(0x00);
		I2C0TubeHighSet(0x00);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xFD);//选中DIG2
		I2C0TubeLowSet(0x30);
	    I2C0TubeHighSet(0x1C);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xFF);
		I2C0TubeLowSet(0x00);
		I2C0TubeHighSet(0x00);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xFB);//选中DIG3
		I2C0TubeLowSet(0x10);
	    I2C0TubeHighSet(0x1C);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xFF);
		I2C0TubeLowSet(0x00);
		I2C0TubeHighSet(0x00);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xF7);//选中DIG4
		I2C0TubeLowSet(0x04);
	    I2C0TubeHighSet(0x1C);
		SysCtlDelay(9000);

		I2C0TubeSelSet(0xFF);
		I2C0TubeLowSet(0x00);
		I2C0TubeHighSet(0x00);
		SysCtlDelay(9000);

		myhandermyhandler();
	}
}


if (f==4){
	    TFTLCD_ShowString(50,70,"Little Star",GREEN,BLACK);
		struct Cnote *p=star;
		for(;p<star+28;p++){
			 starSound(p);
		     myhandermyhandler();
		     if(f==6){
			       TimerDisable(TIMER0_BASE, TIMER_B);
			       p=star+28;
			       GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0xdf);
		             }
		 }
		 GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0xdf);
}

if (f==5){
	 TFTLCD_ShowString(50,70,"Friendship",GREEN,BLACK);
	 struct Cnote *p=friend;
	 for(;p<friend+51;p++){
		 Sound(p);
	     myhandermyhandler();
	     if(f==6){
		       TimerDisable(TIMER0_BASE, TIMER_B);
		       p=friend+51;
		       GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0xdf);
	             }
	 }



	 GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5,0xdf);
}



f=0;}//while(1)


}

