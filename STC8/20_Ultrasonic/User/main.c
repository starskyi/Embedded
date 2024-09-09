#include <STC8H.h>
#include "Config.h"
#include <RTX51TNY.h>
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"
#include "Button.h"
#include "NIXIE.h"
#include "ULTRASONIC.h"

#define LED1 P05

void GPIO_config()
{
	//针脚0
	GPIO_InitTypeDef gpio_initStructure;
	gpio_initStructure.Pin = GPIO_Pin_5;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P0, &gpio_initStructure);
	
}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

  	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

float distance = 0.0f;

void button_down_call(u8 index)
{

}

void button_up_call(u8 index)
{
	
	
	
	if(index == 1)
	{
		Get_Distance(&distance);
		
	}
	else if(index == 2)
	{
		
	}
	else if(index == 3)
	{
		
	}
	else
	{
		
	}
}

void sys_init()
{
	GPIO_config();
	UART_config();
	Button_Init();
	Nixie_Init();
	Ultrasonic_Init();
	

}

void task0() _task_ 0
{
	sys_init();
	
	os_create_task(1);
	os_create_task(2);
	
	os_delete_task(0);
	
}

void task1() _task_ 1
{
	
	 while(1) {
			buttonClick();
      os_wait2(K_TMO, 2);
    }
	
}

void task2() _task_ 2
{
	
	while(1)
	{
		Nixie_Display((uint)(distance * 10));
	};
	
}
