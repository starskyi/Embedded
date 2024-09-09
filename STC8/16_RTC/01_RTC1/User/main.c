#include	"Config.h"
#include	"GPIO.h"
#include	"NVIC.h"
#include	"Switch.h"
#include "Delay.h"
#include "UART.h"
#include "DS1302Clock.h"

#define uchar unsigned char
#define uint  unsigned int



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






//������
void main(void)
{
    Clock clock;
		
    char buffer[20];
		uint year, month, day, week, hour, minute, second;
    char ch = 0x17;
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
			P2M1 = 0;P2M0 = 0;
    UART_config();
    Ds1302_Init(); //DS1302��ʼ��
    EA = 1;

    clock.year = 0x24;
    clock.month = 0x12;
    clock.day = 0x31;
    clock.week = 0x05;
    clock.hour = 0x23;
    clock.minute =0x59;
    clock.second = 0x50;
    //Ds1302_Write_Time(clock);
		Ds1302_Write_Byte(ds1302_sec_add, 0X80);
    while(1)
    {

        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
        delay_ms(250);


        DS1302_Read_Time(&clock);  //��ȡʱ��

        year = CENTURY * 100 + (clock.year / 16 * 10) + (clock.year % 16);
        month = (clock.month / 16 * 10) + (clock.month % 16);
        day = (clock.day / 16 * 10) + (clock.day % 16);
        hour = (clock.hour / 16 * 10) + (clock.hour % 16);
        minute = (clock.minute / 16 * 10) + (clock.minute % 16);
        second = (clock.second / 16 * 10) + (clock.second % 16);


        sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d\r\n", year, month, day, hour, minute, second);
        printf("%s", buffer);


    }
}
