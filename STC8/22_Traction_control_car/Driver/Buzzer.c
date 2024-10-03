#include "Buzzer.h"


u8 music_status = 1;

void delay(u16 ms)
{
    while(ms--) delay_ms(1);
}


/***************  串口初始化函数 *****************/

void Buzzer_GPIO_Config()
{
	P1_MODE_IO_PU(GPIO_Pin_6);
}

void	PWM_config(u16 hz_value)
{
    u16 PERIOD = (MAIN_Fosc / hz_value);

    PWMx_InitDefine		PWMx_InitStructure;

    PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty    = PERIOD * 0.5 ;	//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect   = ENO4P | ENO4N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM4, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

    PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

		PWM4_SW(PWM4_SW_P16_P17);
//    PWM1_SW(PWM1_SW_P10_P11);


    NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


void Buzzer_Init()
{
		EAXSFR();		/* 扩展寄存器访问使能 */
		Buzzer_GPIO_Config();
}

void Buzzer_Stop()
{
    PWMx_InitDefine		PWMx_InitStructure;
		PWMx_InitStructure.PWM_EnoSelect   = ENO4P | ENO4N;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);
}

void Buzzer_loud()
{
	PWM_config(1000);
}

void Buzzer_Sing(u8 music[], u8 duration[], u16 hz[], u16 len)
{
    u8 i;

    for(i = 0; i < len; i++)
    {
        PWM_config(hz[music[i]-1]);
        delay(duration[i] * 120);
        Buzzer_Stop();
        delay(10);
				
    }

    delay(1000);

}

void two_tiger()
{
    //谱子
    u8 code music[] = {
        1,2, 3, 1,					1, 2, 3, 1,					3, 4, 5,		3, 4, 5,
        5, 6, 5, 4, 3, 1, 	5, 6, 5, 4, 3, 1,		1, 5, 1,		1, 5, 1
    };

    //节拍
    u8 code durations[] = {
        4, 4, 4, 4,					4, 4, 4, 4,					4, 4, 8,		4, 4, 8,
        3, 1, 3, 1, 4, 4,		3, 1, 3, 1, 4, 4,		4, 4, 8,		4, 4, 8
    };

    //音律
    //	 		C`	   D`     E`   F`	  G`		A`	  	B`    C``
    u16 hz[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};

    u16 len = (sizeof(music) / sizeof(music[0]));

    Buzzer_Sing(music, durations, hz, len);
}

void sky_city()
{
    u16  code FREQS[] = {
        523 * 1, 587 * 1, 659 * 1, 698 * 1, 784 * 1, 880 * 1, 988 * 1,
        523 * 2, 587 * 2, 659 * 2, 698 * 2, 784 * 2, 880 * 2, 988 * 2,
        523 * 4, 587 * 4, 659 * 4, 698 * 4, 784 * 4, 880 * 4, 988 * 4,
        523 * 8, 587 * 8, 659 * 8, 698 * 8, 784 * 8, 880 * 8, 988 * 8,
    };

    u8  code notes[] = {
        N6, N7, 			 H1, N7, H1, H3, 	  N7, N3, N3, 			N6, N5, N6, H1, 		 N5, N0, N3, N3,		N4, N3, N4, H1,
        N3, N0, H1, H1, H1,  N7, N4, N4, N7,	  N7, N0, N6, N7, 		H1, N7, H1, H3,			 N7, N0, N3, N3,		N6, N5, N6, H1,
        N5, N0, N3, 		 N4, H1, N7, N7, H1,  H2, H2, H3, H1, N0,   H1, N7, N6, N6, N7, N5,	 N6, N0, H1, H2,		H3, H2, H3, H5,
        H2, N0, N5,	N5,		 H1, N7, H1, H3,	  H3, N0, N0,			N6, N7, H1, N7, H2, H2,  H1, N5, N5, N0,		H4, H3, H2, H1,
        H3, 		 		 H3, N0, H3,		  H6, H5, H5,			H3, H2, H1, N0, H1, 	 H2, H1, H2, H2, H5, 	H3, N0, H3,
        H6,	H5,				 H3, H2, H1, N0, H1,  H2, H1, H2, H2, N7,   N6, N0,
    };

    u8  code durations[] = {
        2, 2, 				6, 2, 4, 4, 		  12, 2, 2, 			6, 2, 4, 4, 			8, 4, 2, 2,				6, 2, 2, 6,
        8, 2, 2, 2, 2, 	    6, 2, 4, 4,			  8, 4, 2, 2, 			6, 2, 4, 4,				8, 4, 2, 2,				6, 2, 4, 4,
        12, 2, 2, 			4, 2, 2, 4, 4,		  2, 2, 2, 4, 4, 		4, 2, 2, 2, 4, 4,		8, 4, 2, 2,				6, 2, 4, 4,
        8, 4, 2, 2,			2, 2, 4, 4,			  8, 4, 4,				2, 2, 4, 4, 2, 2, 		6, 2, 4, 4,				4, 4, 4, 4,
        16, 				8, 4,	4,			  8, 4, 4,				2, 2, 4, 2, 2, 			4, 2, 2, 2, 4, 		    8, 4, 4,
        8, 8,				2, 2, 8, 2, 2, 		  4, 2, 2, 2, 4, 		8, 4,
    };
		
		u16 len = sizeof(notes) /sizeof(notes[0]);
		
		Buzzer_Sing(notes, durations, FREQS, len);
}