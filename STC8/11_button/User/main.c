#include	"Switch.h"
#include "Delay.h"
#include "UART.h"
#include "Button.h"


#define LED1 P07


void GPIO_config()
{
	
	P0_MODE_IO_PU(GPIO_Pin_7); //LED1
	
}



/***************  ���ڳ�ʼ������ *****************/
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
}


void callback()
{
	LED1 = !LED1;
}

void button_down_call(u8 index)
{
	printf("s%d: key down\n", (int)index);
}

void button_up_call(u8 index)
{
	printf("s%d: key up\n", (int)index);
	if(index == 2)
	{
		callback();
	}
	
}

void main(void)
{
	
	EAXSFR();		/* ��չ�Ĵ�������ʹ�� */

	GPIO_config();
	UART_config();
	Button_Init();
	EA = 1;
	P30 = 1;P31 = 1; P32 = 1; P33 = 1;
	while (1)
	{
		
		buttonClick();
		delay_ms(20);

	}
}