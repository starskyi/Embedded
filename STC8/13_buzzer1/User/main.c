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
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_6;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//��ʼ��
	
	P0_MODE_IO_PU(GPIO_Pin_0);
}

/************************ ��ʱ������ ****************************/
void	Timer_config(u16 hz_value)
{
	TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����

	//��ʱ��0��16λ�Զ���װ, �ж�Ƶ��Ϊ100000HZ���жϺ�����P6.7ȡ�����50KHZ�����ź�.
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / hz_value * 2);		//��ֵ,
	
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	
	
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

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