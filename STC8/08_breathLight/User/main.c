#include "Config.h"
#include "Timer.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"

void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1;				//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;			//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//初始化
		
}

/************************ 定时器配置 ****************************/
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;						//结构定义

	//定时器0做16位自动重装, 中断频率为100000HZ，中断函数从P6.7取反输出50KHZ方波信号.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);		//初值,
	
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	
	
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3


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
	UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
//	P_SW1 = 0X00;
}

int count = 0;

#define FREQ 100			//频率
#define PERIOD (1000/FREQ) //每个周期时间

float duty = 0.2f;

void Timer0_call()  //1ms执行一次  1/1000
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
	//全局使能
	EA = 1;
	
	P35 = 0; P36 = 1;P37 = 1; 
	
	while(1)
	{
//		if(COM1.RX_TimeOut > 0 && --COM1.RX_TimeOut == 0)		//超时计数
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