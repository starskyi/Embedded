#include "Config.h"
#include "GPIO.h"
#include "Delay.h"
#include "UART.h"
#include "switch.h"
#include "NVIC.h"

void delay_xs(int n)
{
	while(n--)
	{
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
	
}

void GPIO_config()
{
	//针脚0
	GPIO_InitTypeDef gpio_initStructure;
	gpio_initStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P0, &gpio_initStructure);
	
	
	//针脚1
	gpio_initStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P1, &gpio_initStructure);
	
	//针脚3
	gpio_initStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P3, &gpio_initStructure);
}

void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义

	//串口1
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	
	UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	//UART1_SW(UART1_SW_P36_P37);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	P_SW1 = 0X00;
	
	
	//串口2
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;
	COMx_InitStructure.UART_BaudRate  = 115200ul;			
	COMx_InitStructure.UART_RxEnable  = ENABLE;			
	COMx_InitStructure.BaudRateDouble = DISABLE;			
	
	UART_Configuration(UART2, &COMx_InitStructure);		
	NVIC_UART2_Init(ENABLE,Priority_1);	
	UART2_SW(UART2_SW_P10_P11);	
	
	
	//串口3
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer3;
	COMx_InitStructure.UART_BaudRate  = 115200ul;			
	COMx_InitStructure.UART_RxEnable  = ENABLE;			
	COMx_InitStructure.BaudRateDouble = DISABLE;			
	
	UART_Configuration(UART3, &COMx_InitStructure);		
	NVIC_UART3_Init(ENABLE,Priority_1);	
	UART3_SW(UART3_SW_P00_P01);	
	
	//串口4
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer4;
	COMx_InitStructure.UART_BaudRate  = 115200ul;			
	COMx_InitStructure.UART_RxEnable  = ENABLE;			
	COMx_InitStructure.BaudRateDouble = DISABLE;			
	
	UART_Configuration(UART4, &COMx_InitStructure);		
	NVIC_UART4_Init(ENABLE,Priority_1);	
	UART4_SW(UART4_SW_P02_P03);	
	
	
}


void on_uart1_recv()
{
	
	u8	i;
	
	for(i=0; i<COM1.RX_Cnt; i++)
	{
		TX1_write2buff(RX1_Buffer[i]);
		TX2_write2buff(RX1_Buffer[i]);
		TX3_write2buff(RX1_Buffer[i]);
	}
}

void on_uart2_recv()
{
	
	u8	i;
	printf("串口2:");
	for(i=0; i<COM2.RX_Cnt; i++)
	{
		TX1_write2buff(RX2_Buffer[i]);
	}		
}

void on_uart3_recv()
{
	u8	i;
	printf("串口3");
	for(i=0; i<COM3.RX_Cnt; i++)
	{
		TX1_write2buff(RX3_Buffer[i]);
	}		
}

void on_uart4_recv()
{
	u8	i;
	printf("串口4");
	for(i=0; i<COM4.RX_Cnt; i++)
	{
		TX4_write2buff(RX4_Buffer[i]);
	}		
}



void main(void)
{
	GPIO_config();
	UART_config();
	
	//全局中断使能
	EA = 1;
	delay_xs(2);

	printf("hello world");
	while(1)
	{
		delay_ms(250);
		if(COM1.RX_TimeOut > 0 && --COM1.RX_TimeOut == 0)		//超时计数
		{
			if(COM1.RX_Cnt > 0)
			{
				on_uart1_recv();
			}
			COM1.RX_Cnt = 0;
		}
		
		if(COM2.RX_TimeOut > 0 && --COM2.RX_TimeOut == 0)		//超时计数
		{
			if(COM2.RX_Cnt > 0)
			{
				on_uart2_recv();
			}
			COM2.RX_Cnt = 0;
		}
		
		if(COM3.RX_TimeOut > 0 && --COM3.RX_TimeOut == 0)		//超时计数
		{
			if(COM3.RX_Cnt > 0)
			{
				on_uart3_recv();
			}
			COM3.RX_Cnt = 0;
		}
		
		if(COM4.RX_TimeOut > 0 && --COM4.RX_TimeOut == 0)		//超时计数
		{
			if(COM4.RX_Cnt > 0)
			{
				on_uart4_recv();
			}
			COM4.RX_Cnt = 0;
		}
		
	}
}