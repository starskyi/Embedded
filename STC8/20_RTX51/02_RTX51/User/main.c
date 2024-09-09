#include <STC8H.h>
#include "Config.h"
#include <RTX51TNY.h>
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"

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

void sys_init()
{
	GPIO_config();
	UART_config();

	LED1 = 1;

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
        // 超时计数
        // 一旦收到了一个字节数据，RX_TimeOut会初始化一个值（例如：5）
        if((COM1.RX_TimeOut > 0) && (--COM1.RX_TimeOut == 0))
        {            
            if(COM1.RX_Cnt > 0)
            {
                // 收到数据了，on_uart1_recv();
                os_send_signal(2);
            }
            // 处理完数据，将数据个数清零
            COM1.RX_Cnt = 0;
        }
    	// 注意这里delay代码的位置，属于while
        delay_ms(10);
    }
	
}

void task2() _task_ 2
{
	
	while(1)
	{
		os_wait1(K_SIG);
		printf("hello world\n");
		LED1 = !LED1;
	};
	
}
