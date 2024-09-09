#ifndef __DHT11_H__
#define __DHT11_H__

#include "Config.h"
#include "GPIO.h"
#include "Delay.h"

#define DHT11_IO P34
#define DHT11_GPIO_PIN GPIO_Pin_4
#define DHT11_GPIO  GPIO_P3

#define wait_level_change(level, min, max, discription) \
    cnt = 0;                                            \
    do                                                  \
    {                                                   \
        Delay1us();                                     \
        cnt++;                                          \
    } while (DHT11_IO == level && cnt < max);         \
                                                        \
    if (cnt < min || cnt > max)                         \
    {                                                   \
        printf("%s [%d]us\n", discription, (int)cnt);   \
        return -1;                                      \
    }

void DHT11_Init(void);
char Get_DHT11(u8 *humidity, float *temperature);
void Show_DHT11();

#endif