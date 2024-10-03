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
	
	GPIO_InitTypeDef gpio_initStructure;
	
	//���3
	gpio_initStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio_initStructure.Mode = GPIO_PullUp;
	
	GPIO_Inilize(GPIO_P3, &gpio_initStructure);
	
}

void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����

	//����1
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	//P_SW1 = 0X00;
	
	
}


void on_uart1_recv()
{
	
	u8	i;
	
	for(i=0; i<COM1.RX_Cnt; i++)
	{
		TX1_write2buff(RX1_Buffer[i]);
	}
}




void main(void)
{
	GPIO_config();
	UART_config();
	
	//ȫ���ж�ʹ��
	EA = 1;
	delay_xs(2);

	printf("hello world");

	while(1)
	{
		delay_ms(250);
		printf("hello world\n");
		if(COM1.RX_TimeOut > 0 && --COM1.RX_TimeOut == 0)		//��ʱ����
		{
			if(COM1.RX_Cnt > 0)
			{
				on_uart1_recv();
			}
			COM1.RX_Cnt = 0;
		}
		
	}
}