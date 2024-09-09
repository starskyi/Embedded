#include "Delay.h"
#include "GPIO.h"
#include "Config.h"


#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03
#define LED5 P04
#define LED6 P05
#define LED7 P06
#define LED8 P07



void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_All;				//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;			//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化
}

void main()
{
	
	GPIO_config();
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	LED6 = 0;
	LED7 = 0;
	LED8 = 0;
	
	while(1)
	{
		int i;
		for(i = 1; i < 8; i++)
		{
			LED1 = (i == 0 ? 0: 1);
			LED2 = (i == 1 ? 0: 1);
			LED3 = (i == 2 ? 0: 1);
			LED4 = (i == 3 ? 0: 1);
			LED5 = (i == 4 ? 0: 1);
			LED6 = (i == 5 ? 0: 1);
			LED7 = (i == 6 ? 0: 1);
			LED8 = (i == 7 ? 0: 1);
			delay_ms(100);
		}
		
		for(i = 6; i >= 0; i--)
		{
			LED1 = (i == 0 ? 0: 1);
			LED2 = (i == 1 ? 0: 1);
			LED3 = (i == 2 ? 0: 1);
			LED4 = (i == 3 ? 0: 1);
			LED5 = (i == 4 ? 0: 1);
			LED6 = (i == 5 ? 0: 1);
			LED7 = (i == 6 ? 0: 1);
			LED8 = (i == 7 ? 0: 1);
			delay_ms(100);
		}
	
	}
}