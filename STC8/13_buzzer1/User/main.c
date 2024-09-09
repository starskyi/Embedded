#include "Config.h"
#include "Timer.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Delay.h"

#define BUZZER_PIN P16


u16 hz[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};
u16 hz_len = (sizeof(hz) / sizeof(hz[0]));

void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_6;				//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;			//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//初始化
	
	P0_MODE_IO_PU(GPIO_Pin_0);
}

/************************ 定时器配置 ****************************/
void	Timer_config(u16 hz_value)
{
	TIM_InitTypeDef		TIM_InitStructure;						//结构定义

	//定时器0做16位自动重装, 中断频率为100000HZ，中断函数从P6.7取反输出50KHZ方波信号.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / hz_value * 2);		//初值,
	
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	
	
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

}

void Timer0_call()
{
	
	BUZZER_PIN = ~BUZZER_PIN;
	
}



void main()
{
	u8 i = 0;
	GPIO_config();

	EA = 1;
	
	while(1){
		Timer_config(hz[i]);
		if(++i >= hz_len) i = 0;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		
	}
}