#include "Buzzer.h"


u8 music_status = 1;

void delay(u16 ms)
{
    while(ms--) delay_ms(1);
}


/***************  ���ڳ�ʼ������ *****************/


void	PWM_config(u16 hz_value)
{
    u16 PERIOD = (MAIN_Fosc / hz_value);

    PWMx_InitDefine		PWMx_InitStructure;

    PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty    = PERIOD * 0.95 ;	//PWMռ�ձ�ʱ��, 0~Period
    PWMx_InitStructure.PWM_EnoSelect   = ENO4P | ENO4N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM4, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

    PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

		PWM4_SW(PWM4_SW_P16_P17);
//    PWM1_SW(PWM1_SW_P10_P11);


    NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


void Buzzer_Init(u8 GPIO, u8 GPIO_Pin)
{
    GPIO_InitTypeDef	GPIO_InitStructure;         //�ṹ����
    GPIO_InitStructure.Pin  =  GPIO_Pin;           //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
    GPIO_InitStructure.Mode = GPIO_PullUp;          //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO,&GPIO_InitStructure);      //��ʼ��
}

void Buzzer_Stop()
{
    PWMx_InitDefine		PWMx_InitStructure;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);
}

void Buzzer_Sing(u8 music[], u8 duration[], u16 hz[], u16 len)
{
    u8 i;

    for(i = 0; i < len; i++)
    {
				if(!music_status)
				{
					return;
				}
        PWM_config(hz[music[i]-1]);
        delay(duration[i] * 120);
        Buzzer_Stop();
        delay(10);
				
    }

    delay(1000);

}