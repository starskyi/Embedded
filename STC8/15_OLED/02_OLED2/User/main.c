#include "Config.h"
#include "oled.h"
#include "bmp.h"


int main(void)
{   u8 t;

    //准双向
    P0M0 &= ~0x03;
    P0M1 &= ~0x03;

    //开漏
    //P0M0 |= 0x03; P0M1 |= 0x03;

    OLED_Init();			//初始化OLED
    OLED_Clear();

    while(1)
    {
      OLED_Clear();
//      OLED_ShowChar(0, 0, 'C', 16);
//      delay_ms(3000);
//      OLED_ShowNum(32, 0, 2024, 4, 16);
//			delay_ms(3000);
      OLED_ShowString(0, 0, "hello world!", 16);
			delay_ms(3000);
			OLED_Clear();
			OLED_ShowCHinese(0, 3, 0);
			OLED_ShowCHinese(16, 3, 1);
			OLED_ShowCHinese(32, 3, 2);
			OLED_ShowCHinese(48, 3, 3);
			delay_ms(3000);
      OLED_DrawBMP(0, 0, 128, 8, BMP3);
			delay_ms(3000);
    }

}
