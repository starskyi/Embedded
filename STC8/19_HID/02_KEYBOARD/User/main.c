#include "Config.h"
#include "GPIO.h"
#include "Delay.h"
#include "UART.h"
#include "Button.h"
#include "Switch.h"
#include "NVIC.h"

#include "usb.h"
#include "usb_req_class.h"

#define LED_NUM P05
#define LED_CAPS P06
#define LED_SCROLL P07

//void sys_init();
extern u8 status;

u8 keys[4] = {0x1A, 0x16, 0xE0, 0x06}; //W	S	L_CTRL	C
u8 ctr_key[8] = {0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7};

u8 btn_len = 4;
void	UART_config(void)
{
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE

    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

void button_down_call(u8 index)
{
    u8 i,j;
    u8 key[8] = {0};
    u8 cnt = 2;
    for(i = 2; i < btn_len; i++)    //��ť1,2�����⣬�ӵ�������ʼ
    {
        if(IS_KEY_DOWN(i))
        {
            if(keys[i] >= 0xE0 && keys[i] <= 0xE7)
            {
                for(j = 0; j < 8; j++)
                {
                    if(keys[i] == ctr_key[j])
                    {
                        key[0] |= (1 << j);
                        break;
                    }
                }
            }
						else
						{
							key[cnt++] = keys[i];
						}
            

        }
        if(cnt > 7) break;
    }


    usb_keyboard_send(key);
    P00 = 0;
}
void button_up_call(u8 index)
{
    u8 key[8] = {0};
    usb_keyboard_send(key);
    P00 = 1;
}

void keyboard_receive(u8 led)
{
		LED_NUM = !(led & 0x01);
    LED_CAPS = !(led & 0x02);
    LED_SCROLL = !(led & 0x04);
}

void main()
{

    EAXSFR();

    usb_init();
    //timer_init();
    //UART_config();
    Button_Init();
    P0M1 = 0;P0M0 = 0;
    EA = 1;
    while(1)
    {
        buttonClick();
        delay_ms(20);

    }
}
