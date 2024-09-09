#include	"config.h"
#include	"STC8H_PWM.h"
#include	"GPIO.h"
#include	"NVIC.h"
#include	"Switch.h"
#include "Delay.h"

PWMx_Duty PWMA_Duty;
u16 value = 0;
void GPIO_config()
{
	GPIO_InitTypeDef	GPIO_InitStructure;         //结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 ;           //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;          //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);      //初始化
	

	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;           //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;          //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);      //初始化

}


/***************  串口初始化函数 *****************/
#define PERIOD (MAIN_Fosc / 1000)
void	PWM_config()
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = value;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM1, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

	PWM1_SW(PWM1_SW_P10_P11);			//PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
	

	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


u8 duty_percent = 20;
int direction = 2;

void breathLight()
{
	duty_percent += direction;
	if(duty_percent >= 100) 
	{
		duty_percent = 100;
		direction = -2;
	}
	if(duty_percent <= 0)
	{
		duty_percent = 0;
		direction = 2;
	}
	
//	PWMA_Duty.PWM1_Duty = PERIOD * duty_percent / 100;
//	UpdatePwm(PWM1, &PWMA_Duty);
	value = PERIOD * duty_percent / 100;
	PWM_config();
	
}
int count = 0;
void rgb_light()
{
	count += 1;
	if(count == 100) count = 0;
	if(count % 30 == 0)
	{
		P00 = 0;P01 = 1;P02 = 1;
	}
	else if(count % 30 == 10)
	{
		P00 = 1;P01 = 0;P02 = 1;
	}else if(count % 30 == 20)
	{
		P00 = 1;P01 = 1;P02 = 0;
	}
}

void main(void)
{
	
	EAXSFR();		/* 扩展寄存器访问使能 */
	PWMA_Duty.PWM1_Duty = PERIOD * duty_percent / 100;
	
	GPIO_config();
	PWM_config();
	EA = 1;
	P10 = 1;		//打开LED电源
	P00 = 0;P01 = 0;P02 = 0; //RGB灯
	
	//UpdatePwm(PWM1, &PWMA_Duty);
	while (1)
	{
	
		delay_ms(10);
		
		breathLight();
		//rgb_light();
		
	}
}