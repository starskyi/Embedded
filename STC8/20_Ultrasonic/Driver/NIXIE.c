#include "NIXIE.h"

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//�������ֱ���  0.1.2.3.4....9

void	Nixie_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����

    GPIO_InitStructure.Pin  =COM_PIN;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(COM_GPIO,&GPIO_InitStructure);	//��ʼ��
	
		GPIO_InitStructure.Pin  =DIG_PIN;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(DIG_GPIO,&GPIO_InitStructure);	//��ʼ��
}

void Nixie_Display(uint num) //��ʾ����
{
  
	 uchar num1 = num / 1000;
	 uchar num2 = num % 1000 / 100;
	 uchar num3 = num % 100 / 10;
	 uchar num4 = num % 10;

   DIG_RIG_Pin = table[num1];
   COM1 = 0;
   delay_ms(5);
   COM1 = 1;

   DIG_RIG_Pin = table[num2];
   COM2 = 0;
   delay_ms(5);
   COM2 = 1;

   DIG_RIG_Pin = table[num3];
	 dp = 0;
   COM3 = 0;
   delay_ms(5);
   COM3 = 1;

   DIG_RIG_Pin = table[num4];
   COM4 = 0;
   delay_ms(5);
   COM4 = 1;
}
