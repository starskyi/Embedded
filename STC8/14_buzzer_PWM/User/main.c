#include <STC8H.h>
#include "Config.h"
#include <RTX51TNY.h>
#include "UART.h"
#include "Switch.h"
#include "Delay.h"
#include "Button.h"
#include "Buzzer.h"



#define BUTTON_TASK 1
#define BUZZER_LOUD 2




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
	
}



void button_down_call(u8 index)
{
	if(index == 1)
	{
	
		
	}
	else if(index == 2)
	{
		P00 = 0;

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
		os_create_task(BUZZER_LOUD);
		
	}
	else if(index == 2)
	{
		P00 = 1;


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
	EAXSFR();
	UART_config();
	Button_Init();
	
}

void task0() _task_ 0
{
	sys_init();
	os_create_task(BUTTON_TASK);
	
	os_delete_task(0);
	
}

void task1() _task_ BUTTON_TASK
{
	
	 while(1) {
			buttonClick();
      os_wait2(K_TMO, 2);
    }
}

void task2() _task_ BUZZER_LOUD
{
	Buzzer_loud();
	os_wait2(K_TMO, 40); //200ms 40*5ms
	Buzzer_Stop();
	os_delete_task(BUZZER_LOUD);
}
