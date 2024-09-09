#include "Button.h"

extern void button_callback1();
extern void butto2_callback1();

void Button_Init()
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//结构定义
	GPIO_InitStructure.Pin  = BUTTON_PIN;				//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;			//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(BUTTON_GPIO,&GPIO_InitStructure);	//初始化
}


void button1_down_call()
{
	printf("s1: key down\n");
}

void button1_up_call()
{
	printf("s1: key up\n");
	button_callback1();
}

void button2_down_call()
{
	printf("s2: key down\n");
}

void button2_up_call()
{
	printf("s2: key up\n");
	butto2_callback1();
}

void button3_down_call()
{
	printf("s3: key down\n");
	
}

void button3_up_call()
{
	printf("s3: key up\n");
}
void button4_down_call()
{
	printf("s4: key down\n");
}
void button4_up_call()
{
	printf("s4: key up\n");
}



u8 status = 0x0f;


void button1Click()
{
	if(IS_KEY_UP(0) && S1 == 0)
	{
		SET_KEY_DOWN(0);
		button1_down_call();
		
	}
	else if(IS_KEY_DOWN(0) && S1 == 1)
	{
		SET_KEY_UP(0);
		button1_up_call();
		
	}
}

void button2Click()
{
	if(IS_KEY_UP(1) && S2 == 0)
	{
		SET_KEY_DOWN(1);
		button2_down_call();
		
	}
	else if(IS_KEY_DOWN(1) && S2 == 1)
	{
		SET_KEY_UP(1);
		button2_up_call();
	}
}

void button3Click()
{
	if(IS_KEY_UP(2) && S3 == 0)
	{
		SET_KEY_DOWN(2);
		button3_down_call();
		
	}
	else if(IS_KEY_DOWN(2) && S3 == 1)
	{
		SET_KEY_UP(2);
		button3_up_call();
	
	}
}

void button4Click()
{
		
	if(IS_KEY_UP(3) && S4 == 0)
	{
		SET_KEY_DOWN(3);
		button4_down_call();
		
	}
	else if(IS_KEY_DOWN(3) && S4 == 1)
	{
		SET_KEY_UP(3);
		button4_up_call();
		
	}
}
