#include "MOTOR.h"
#include "GPIO.h"
#include "Switch.h"
#include "NVIC.h"
#include "STC8H_PWM.h"
#include <RTX51TNY.h>

#define PERIOD (MAIN_Fosc / 1000)

void Motor_GPIO_Config()
{
	P0_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
	P2_MODE_IO_PU(GPIO_Pin_All);
	P3_MODE_IO_PU(GPIO_Pin_All);
	P4_MODE_IO_PU(GPIO_Pin_5);
}

//void	MOtor_PWM_config(u8 percent)
//{
//	PWMx_InitDefine		PWMx_InitStructure;
//	
//	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty    = PERIOD * percent / 100;	//PWM占空比时间, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect   = ENO2P | ENO2N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM2, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//周期时间,   0~65535
//	PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
//	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
//	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
//	PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

//	PWM2_SW(PWM2_SW_P22_P23);			//PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
//	
//	PWMx_InitStructure.PWM_Duty    = PERIOD * percent / 100;
//	PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N;	
//	PWM_Configuration(PWM1, &PWMx_InitStructure);	
//	PWM_Configuration(PWMA, &PWMx_InitStructure);	
//	PWM1_SW(PWM1_SW_P20_P21);
//	

//	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);

//}

void	MOtor_PWM_config(u8 percent_left, u8 percent_right)
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	//PWM2
	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PERIOD * percent_left / 100;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO2P | ENO2N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB


	//PWM1
	PWMx_InitStructure.PWM_Duty    = PERIOD * percent_left / 100;
//	PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N;	
	PWMx_InitStructure.PWM_EnoSelect   = ENO1P;
	PWM_Configuration(PWM1, &PWMx_InitStructure);
	
	//PWM5
	PWMx_InitStructure.PWM_Duty    = PERIOD * percent_right / 100;
	PWMx_InitStructure.PWM_EnoSelect   = ENO5P;
	PWM_Configuration(PWM5, &PWMx_InitStructure);	
	
	
	//PWM6
	PWMx_InitStructure.PWM_Duty    = PERIOD * percent_right / 100;
	PWMx_InitStructure.PWM_EnoSelect   = ENO6P;
	PWM_Configuration(PWM6, &PWMx_InitStructure);	
	
		//PWMA
	PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
	
	//PWMB
	PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
	
	PWM1_SW(PWM1_SW_P20_P21);
	PWM2_SW(PWM2_SW_P22_P23);			//PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
	PWM5_SW(PWM5_SW_P00);
	PWM6_SW(PWM6_SW_P01);

	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
	NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}


void Motor_Init()
{
	Motor_GPIO_Config();
	
	MOtor_PWM_config(80, 80);
	
	LQ_AIN1 = 0;
	LQ_AIN2 = 0;
	RQ_BIN1 = 0;
	RQ_BIN2 = 0; 
	
	LH_AIN1 = 0;
	LH_AIN2 = 0;
	RH_BIN1 = 0;
	RH_BIN2 = 0;
	
	STBY_F = 1;
	STBY_B = 1;

	
}


void retreat()
{

	stop();
	
	LQ_AIN1 = 1;
	LQ_AIN2 = 0;
	RQ_BIN1 = 1;
	RQ_BIN2 = 0;
	
	LH_AIN1 = 1;
	LH_AIN2 = 0;
	RH_BIN1 = 1;
	RH_BIN2 = 0;
	
	
	STBY_F = 1;
	STBY_B = 1;
	os_wait2(K_TMO, 4);
	MOtor_PWM_config(80, 80);
	
}
	
void forward()
{
	stop();
	
	
	
	LQ_AIN1 = 0;
	LQ_AIN2 = 1;
	RQ_BIN1 = 0;
	RQ_BIN2 = 1;
	
	LH_AIN1 = 0;
	LH_AIN2 = 1;
	RH_BIN1 = 0;
	RH_BIN2 = 1;
	
	STBY_F = 1;
	STBY_B = 1;
	os_wait2(K_TMO, 4);
	MOtor_PWM_config(80, 80);

}

//void right(u8 angle_value)
//{
//	STBY_F = 1;
//	STBY_B = 1;
//	MOtor_PWM_config(50 + angle_value);
//	
//}

//void left(u8 angle_value)
//{
//	STBY_F = 1;
//	STBY_B = 1;
//	MOtor_PWM_config(50 - angle_value);
//}

void right(u8 angle_value)
{
	STBY_F = 1;
	STBY_B = 1;
	MOtor_PWM_config(angle_value, 10);
	
}

void left(u8 angle_value)
{
	STBY_F = 1;
	STBY_B = 1;
	MOtor_PWM_config(10, angle_value);
}


void turn_around_right()
{
	stop();

	
	
	LQ_AIN1 = 0;
	LQ_AIN2 = 1;
	LH_AIN1 = 0;
	LH_AIN2 = 1;
	
	RQ_BIN1 = 1;
	RQ_BIN2 = 0;
	RH_BIN1 = 1;
	RH_BIN2 = 0;
	STBY_F = 1;
	STBY_B = 1;
	os_wait2(K_TMO, 4);
	MOtor_PWM_config(100, 100);
}

void turn_around_left()
{
	stop();
	
	
	
	RQ_BIN1 = 0;
	RQ_BIN2 = 1;
	RH_BIN1 = 0;
	RH_BIN2 = 1;
	
	LQ_AIN1 = 1;
	LQ_AIN2 = 0;
	LH_AIN1 = 1;
	LH_AIN2 = 0;
	
	STBY_F = 1;
	STBY_B = 1;
	os_wait2(K_TMO, 4);
	MOtor_PWM_config(100, 100);

}

void stop()
{
	STBY_F = 0;
	STBY_B = 0;
	LQ_AIN1 = 0;
	LQ_AIN2 = 0;
	RQ_BIN1 = 0;
	RQ_BIN2 = 0; 
	
	LH_AIN1 = 0;
	LH_AIN2 = 0;
	RH_BIN1 = 0;
	RH_BIN2 = 0;
}
