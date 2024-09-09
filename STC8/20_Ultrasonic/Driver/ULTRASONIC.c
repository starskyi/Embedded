#include "ULTRASONIC.h"
#include "GPIO.h"


#define PIN_TRIG P11
#define PIN_ECHO P10


void Delay10us()		//@24.000MHz
{
	unsigned char data i;

	i = 78;
	while (--i);
}


void Ultra_GPIO_config()
{
	
	  GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

		//TRIG 推挽
    GPIO_InitStructure.Pin  = GPIO_Pin_1;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//初始化

		//ECHO 高阻
		GPIO_InitStructure.Pin  = GPIO_Pin_0;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_HighZ;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//初始化
		
}

void Ultrasonic_Init()
{
	Ultra_GPIO_config();
	
	PIN_TRIG = 0;
}


u8 Get_Distance(float *distance)
{
	u16 cnt_10us = 0;
	//1.使用TRIG触发测距，至少10us高电平
	PIN_TRIG = 1;
	Delay10us();
	Delay10us();
	PIN_TRIG = 0;

	//2.等待2.2ms左右，ECHO电平被拉高
	while(PIN_ECHO == 0 && cnt_10us < 230)
	{
		Delay10us();
		cnt_10us++;
	}
	
	if(cnt_10us >= 230)
	{
		printf("fail to get distance\n");
		return -1;
	}
	
	cnt_10us = 0;
	while(PIN_ECHO)
	{
		Delay10us();
		cnt_10us++;
	}
	
	*distance = (cnt_10us + 10) * 0.01 * 34 / 2;   //dis = time * seed(340m/s) / 2     cnt_10us + 10(有10 * 10us的误差)
	
	printf("distance(2cm - 400cm): %0.1f cm\n", *distance);
	return 0;
}