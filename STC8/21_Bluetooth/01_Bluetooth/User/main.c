#include <STC8H.h>
#include "Config.h"
#include <RTX51TNY.h>
#include "UART.h"
#include "Switch.h"
#include "Delay.h"
#include "Button.h"



#define BUTTON_TASK 1
#define UART1_TASK 2
#define UART2_TASK 3

void GPIO_config()
{
	//���0
	GPIO_InitTypeDef gpio_initStructure;
	
	gpio_initStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P1, &gpio_initStructure);
	
}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

  	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	
	
		COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

  	NVIC_UART2_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

    UART2_SW(UART2_SW_P10_P11);		
}



void button_down_call(u8 index)
{

}

void button_up_call(u8 index)
{
	
	if(index == 1)
	{
		printf("hello\n");
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
	EA = 1;
	GPIO_config();
	UART_config();
	Button_Init();
	
	
}

void task0() _task_ 0
{
	sys_init();
	//os_create_task(BUTTON_TASK);
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


void task3() _task_ UART2_TASK
{
	u8 i;
	while(1)
	{
		if((COM2.RX_TimeOut > 0) && (--COM2.RX_TimeOut == 0))
    {            
			if(COM2.RX_Cnt > 0)
      {
					for(i = 0; i < COM2.RX_Cnt; i++)
					{
						TX1_write2buff(RX2_Buffer[i]);
					}
          
      }
      COM2.RX_Cnt = 0;
    }
		os_wait2(K_TMO, 2);
	}
}




