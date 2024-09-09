#include "Config.h"
#include "Timer.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"

void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//��ʼ��
		
}

/************************ ��ʱ������ ****************************/
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����

	//��ʱ��0��16λ�Զ���װ, �ж�Ƶ��Ϊ100000HZ���жϺ�����P6.7ȡ�����50KHZ�����ź�.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);		//��ֵ,
	
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	
	
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3


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
//	P_SW1 = 0X00;
}

int count = 0;

#define FREQ 100			//Ƶ��
#define PERIOD (1000/FREQ) //ÿ������ʱ��

float duty = 0.2f;

void Timer0_call()  //1msִ��һ��  1/1000
{
	
	if(count <= (duty * PERIOD))
	{
		P35 = 0; P36 = 1;P37 = 1; 
	}
	else
	{
		P35 = 1; P36 = 1;P37 = 1; 
	}
	if(count++ == PERIOD) count = 0;
}

void on_uart1_recv()
{
	u8	i;
	
	u8 dat = RX1_Buffer[0];
	TX1_write2buff(RX1_Buffer[0]);
	printf("\n%u", dat);
	if(dat == 0)
	{
		duty += 0.1;
		if(duty > 1.0) duty = 1.0f;
	}
	if(dat == 1)
	{
		duty -= 0.1;
		if(dat < 0.0) duty = 0.0f;
	}
	
	
}

float direction = 0.01;

void breathLight()
{
	if(duty >= 1.0) direction = -0.02;
	if(duty <= 0.0) direction = 0.02;
	duty += direction;
}

void main()
{
	GPIO_config();
	Timer_config();
	UART_config();
	//ȫ��ʹ��
	EA = 1;
	
	P35 = 0; P36 = 1;P37 = 1; 
	
	while(1)
	{
//		if(COM1.RX_TimeOut > 0 && --COM1.RX_TimeOut == 0)		//��ʱ����
//		{
//			if(COM1.RX_Cnt > 0)
//			{
//				on_uart1_recv();
//			}
//			COM1.RX_Cnt = 0;
//		}
		
		breathLight();
		delay_ms(10);
	}
}