#include	"Config.h"
#include	"GPIO.h"
#include	"NVIC.h"
#include	"Switch.h"
#include "Delay.h"
#include "UART.h"
#include "DS1302Clock.h"
#include "oled.h"
#include "bmp.h"

void	UART_config(void)
{
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����

    //����1
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE

    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44

}


void delay(u16 ms)
{
	while(ms--) delay_ms(1);
}

u8 count = 0;

//������
void main(void)
{
    Clock clock;
		
    char buffer[20];
		char buffer2[20];
		uint year, month, day, week, hour, minute, second;

    P0M1 = 0;
    P0M0 = 0;
    P1M1 = 0;
    P1M0 = 0;
    P2M1 = 0;
    P2M0 = 0;
    P3M1 = 0;
    P3M0 = 0;
    P4M1 = 0;
    P4M0 = 0;
    P5M1 = 0;
    P5M0 = 0;
		
		//׼˫��  OLED
    P0M0 = 0;
    P0M1 = 0;
			
    UART_config();
    Ds1302_Init(); //DS1302��ʼ��
    EA = 1;

    clock.year = 0x24;
    clock.month = 0x8;
    clock.day = 0x2;
    clock.week = 0x05;
    clock.hour = 0x17;
    clock.minute =0x42;
    clock.second = 0x50;
    //Ds1302_Write_Time(clock);
		//Ds1302_Write_Byte(ds1302_sec_add, 0X80);
		
		OLED_Init();			//��ʼ��OLED
    OLED_Clear();
		
    while(1)
    {
				
        DS1302_Read_Time(&clock);  //��ȡʱ��
				
        year = CENTURY * 100 + (clock.year / 16 * 10) + (clock.year % 16);
        month = (clock.month / 16 * 10) + (clock.month % 16);
        day = (clock.day / 16 * 10) + (clock.day % 16);
        hour = (clock.hour / 16 * 10) + (clock.hour % 16);
        minute = (clock.minute / 16 * 10) + (clock.minute % 16);
        second = (clock.second / 16 * 10) + (clock.second % 16);
			
				
        sprintf(buffer, "%04d-%02d-%02d ", year, month, day);
				sprintf(buffer2, "%02d:%02d:%02d ", hour, minute, second);
        printf("%s%s", buffer, buffer2);
				
				//OLED_Clear();
				OLED_ShowString(20, 0, buffer, 16);
				OLED_ShowString(30, 3, buffer2, 16);
				delay(1000);
			
				count++;
				if(count > 5)
				{
					OLED_Clear();
					OLED_DrawBMP(0, 0, 128, 8, BMP3);
					delay(2000);
					count = 0;
					OLED_Clear();
				}
				
				
    }
}
