#include "Button.h"

extern void button_down_call(u8 index);
extern void button_up_call(u8 index);

void Button_Init()
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//结构定义
	GPIO_InitStructure.Pin  = BUTTON_PIN;				//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;			//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(BUTTON_GPIO,&GPIO_InitStructure);	//初始化
}



void button_down(u8 index)
{
	//printf("button %d down!\n", (int)index);
	button_down_call(index);
}
void button_up(u8 index)
{
	//printf("button %d up!\n", (int)index);
	button_up_call(index);
}


u8 status = 0x0f;
void buttonClick()
{
	
	if(IS_KEY_UP(0) && S1 == 0)
	{
		SET_KEY_DOWN(0);
		//button_down(1);
		
	}
	else if(IS_KEY_DOWN(0) && S1 == 1)
	{
		SET_KEY_UP(0);
		//button_up(1);
		
	}
	
	if(IS_KEY_UP(1) && S2 == 0)
	{
		SET_KEY_DOWN(1);
		//button_down(2);
		
	}
	else if(IS_KEY_DOWN(1) && S2 == 1)
	{
		SET_KEY_UP(1);
		//button_up(2);
	}
	
	if(IS_KEY_UP(2) && S3 == 0)
	{
		SET_KEY_DOWN(2);
		button_down(3);
		
	}
	else if(IS_KEY_DOWN(2) && S3 == 1)
	{
		SET_KEY_UP(2);
		button_up(3);
	
	}
	
	if(IS_KEY_UP(3) && S4 == 0)
	{
		SET_KEY_DOWN(3);
		button_down(4);
		
	}
	else if(IS_KEY_DOWN(3) && S4 == 1)
	{
		SET_KEY_UP(3);
		button_up(4);
		
	}
	
}