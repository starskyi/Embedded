#include <STC8H.h>
#include "Config.h"
#include <RTX51TNY.h>
#include "UART.h"
#include "Switch.h"
#include "Delay.h"
#include "Button.h"
#include "TRACK.h"
#include "MOTOR.h"
#include "Buzzer.h"



#define BUTTON_TASK 1
#define UART1_TASK 2
#define UART2_TASK 3
#define TRACK_TASK 4
#define BUZZER 5

u8 track_status[4];

void GPIO_config()
{
	//针脚0
	GPIO_InitTypeDef gpio_initStructure;
	
	gpio_initStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P0, &gpio_initStructure);
	
	
	P1_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
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
	
	
		COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

  	NVIC_UART2_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

    UART2_SW(UART2_SW_P10_P11);		
}


void trumpet()
{
	os_create_task(BUZZER);
}

void start_tracking()
{
	os_create_task(TRACK_TASK);
}

void stop_tracking()
{
	os_delete_task(TRACK_TASK);
	stop();
}

u8 button1_flag = 0;
u8 button2_flag = 0;

void button_down_call(u8 index)
{
	if(index == 1)
	{
		button1_flag = !button1_flag;
		printf("%d\n", button1_flag);
		if(button1_flag)
		{
			//开启巡线
			printf("start\n");
			start_tracking();
		}
		else
		{
			//关闭巡线
			printf("stop\n");
			stop_tracking();
		}
		
			
		
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



void button_up_call(u8 index)
{
	u8 i;
	
	if(index == 1)
	{

		Get_status(track_status);
		for(i = 0; i < 4; i++)
		{
			printf("%d ", (int)track_status[i]);
		}
		printf("\n");
		printf("%d\n", get_direction());
		
	}
	else if(index == 2)
	{
		button2_flag = !button2_flag;
		if(button1_flag)
		{
			//前进
			forward();
		}
		else
		{
			//后退
			retreat();
		}

	}
	else if(index == 3)
	{
		printf("button3\n");
		left(100);
	}
	else
	{
		printf("button4\n");
		right(100);
	}
}



void response_action(char cmd)
{
	switch(cmd)
	{
		case 0xA1: {forward(); break;}
		case 0xA2: {retreat(); break;}
		case 0xA3: {left(100); break;}
		case 0xA4: {right(100); break;}
		case 0xA5: {stop(); break;}
		case 0xA6: {start_tracking(); break;}
		case 0xA7: {stop_tracking(); break;}
		case 0xA8: {trumpet(); break;}
		case 0xA9: {turn_around_left(); break;}
		default: break;
		
	}
}



void sys_init()
{
	EA = 1;
	EAXSFR();
	GPIO_config();
	UART_config();
	Button_Init();
	Buzzer_Init();
	Track_Init();
	Motor_Init();
	
}

void task0() _task_ 0
{
	sys_init();
	os_create_task(BUTTON_TASK);
	os_create_task(UART1_TASK);
	os_create_task(UART2_TASK);

	
	os_delete_task(0);
	
}

void task1() _task_ BUTTON_TASK
{
	
	 while(1) {
			buttonClick();
      os_wait2(K_TMO, 2);
    }
}

//通过串口给蓝牙发送消息
void task2() _task_ UART1_TASK
{
	u8 i;
	
	while(1)
	{
		if((COM1.RX_TimeOut > 0) && (--COM1.RX_TimeOut == 0))
    {            
			if(COM1.RX_Cnt > 0)
      {
					for(i = 0; i < COM1.RX_Cnt; i++)
					{
						TX2_write2buff(RX1_Buffer[i]);
					}
      }
      COM1.RX_Cnt = 0;
    }
    os_wait2(K_TMO, 2);
	}
}


//蓝牙模块接收消息处理
void task3() _task_ UART2_TASK
{
	u8 i;
	while(1)
	{
		if((COM2.RX_TimeOut > 0) && (--COM2.RX_TimeOut == 0))
    {            
			if(COM2.RX_Cnt > 0)
      {
					//收到消息，处理逻辑
					for(i = 0; i < COM2.RX_Cnt; i++)
					{
						TX1_write2buff(RX2_Buffer[i]);
						
					}
					
					response_action(RX2_Buffer[0]);
      }
      COM2.RX_Cnt = 0;
    }
		os_wait2(K_TMO, 2);
	}
}


void task4() _task_ TRACK_TASK
{
	int direction;
	
	forward();
	while (1)
	{
		
		direction = get_direction();
		
		if(direction < 0)
		{
			left(100);
		}
		else if(direction > 0)
		{
			right(100);
		}
		else
		{
			forward();
		}
		
		os_wait2(K_TMO, 2);  //10ms  2*5ms
		
	}
	
}

void task5() _task_ BUZZER
{
	Buzzer_loud();
	os_wait2(K_TMO, 40);  //200ms  40*5ms
	Buzzer_Stop();
	os_delete_task(BUZZER);
}


