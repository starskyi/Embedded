#include "NTC.h"

#define NTC_GPIO GPIO_P1
#define NTC_PIN GPIO_Pin_0
#define INIT_TEMP -40

#define ABS_VALUE(num) ((num) > 0 ? (num) : -(num))

u16 code temp_table[] = {
	18525, 17280, 16128, 15060, 14072, 13154, 12303, 11513, 10779, 10097, 9463, 8873, 8324, 7812, 7336, 6892,
	6477, 6091, 5730, 5393, 5078, 4783, 4508, 4250, 4008, 3782, 3571, 3372, 3186, 3011, 2847, 2693, 2548, 2412,
	2284, 2164, 2051, 1944, 1844, 1749, 1660, 1576, 1497, 1422, 1352, 1285, 1222, 1163, 1107, 1053, 1003, 956, 911,
	868, 828, 789, 753, 719, 686, 655, 626, 598, 572, 547, 523, 500, 478, 458, 438, 420, 402, 385, 369, 354, 340, 326,
	312, 300, 288, 276, 265, 255, 245, 235, 226, 218, 209, 201
};

u8 table_len = (u8)(sizeof(temp_table) / sizeof(temp_table[0]));

void	NTC_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

    GPIO_InitStructure.Pin  = NTC_PIN;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(NTC_GPIO,&GPIO_InitStructure);	//初始化
}


float adc_value;
u16 result_r;

int Get_Temperature()
{
	u8 i;
	u16 min_diff, curr_diff;
	u8 temp_index = 0;
	
	adc_value = Get_ADCResult(ADC_CH1) * 3.33 / 4095;
	result_r = (u16)(adc_value * 10 / (3.33 - adc_value) * 100);
	
	min_diff = (u16)ABS_VALUE(result_r - temp_table[0]);
	for(i = 1; i < table_len; i++)
	{
		curr_diff = (u16)ABS_VALUE(result_r - temp_table[i]);
		if(curr_diff < min_diff)
		{
			min_diff = curr_diff;
			temp_index = i;
		}
	}
	return (int)(INIT_TEMP + (int)temp_index);
	
}