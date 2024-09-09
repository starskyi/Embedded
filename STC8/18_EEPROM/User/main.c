#include "Config.h"
#include "Delay.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "EEPROM.h"
#include <string.h>

void UART_config(void)
{
    COMx_InitDefine COMx_InitStructure; // 结构定义

    // 串口1
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx; // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;  // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate = 115200ul;   // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable = ENABLE;     // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;   // 波特率加倍, ENABLE或DISABLE

    UART_Configuration(UART1, &COMx_InitStructure); // 初始化串口1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE, Priority_1);            // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);                     // UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

u8 xdata buf[100];
void main()
{
		u16 addr_sector = 0x0000;
		char *str = "hello 海阔天空 world! 123 ";
		u16 buf_len = strlen(str);
	
		UART_config();
    EA = 1;
	
//		EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number);
//	  EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number);
//		EEPROM_SectorErase(u16 EE_address);
	
//		EEPROM_SectorErase(addr_sector);
//	  EEPROM_write_n(addr_sector,str,buf_len);
		EEPROM_read_n(addr_sector,buf,buf_len);
		buf[buf_len] = '\0';
		printf("%s\n", buf);
    while (1)
    {
        
    }
}