#include "Buzzer.h"
#include "Timer.h"
#include "UART.h"
#include "Button.h"



extern u8 music_status;

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

void starsky_city()
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

u8 last_button1_status = 1;

void Timer0_call()
{
	button1Click();
}


void button_callback1()
{
	music_status = 0;
}

void butto2_callback1()
{
	music_status = 1;
	starsky_city();
	
}

void main(void)
{
    u8 i = 0;
		//printf("%d", music_status);
    EAXSFR();		/* 扩展寄存器访问使能 */
		Button_Init();
		Timer_config();
		UART_config();
//    Buzzer_Init(GPIO_P1, GPIO_Pin_0 | GPIO_Pin_1);
		
		Buzzer_Init(GPIO_P1, GPIO_Pin_6 | GPIO_Pin_7);
    EA = 1;
		starsky_city();
    while (1)
    {
				button2Click();
        //two_tiger();
				
				
    }
}