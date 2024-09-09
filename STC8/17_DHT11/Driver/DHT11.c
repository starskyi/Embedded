#include "DHT11.h"



void DHT11_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;        // 结构定义
    GPIO_InitStructure.Pin = DHT11_GPIO_PIN;        // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
    GPIO_InitStructure.Mode = GPIO_PullUp;      // 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(DHT11_GPIO, &GPIO_InitStructure); // 初始化
}

void Delay1us() //@24.000MHz
{
    NOP10();
}


char Get_DHT11(u8 *humidity, float *temperature)
{
    char symbol = 1;
    u8 cnt = 0;
    char i = 0, j = 0;
    u8 dat[5] = {0};
    // 起始信号 拉低拉高 低电平[18ms, 30ms]
    DHT11_IO = 0;
    delay_ms(20);
    DHT11_IO = 1;

    // 主机释放总线时间 13us [10, 35]
    do
    {
        Delay1us();
        cnt++;
    } while (DHT11_IO && cnt <= 35);

    if (cnt < 10 || cnt > 35)
    {
        printf("time out %d us\n", (int)cnt);
        return -1;
    }

    // 响应低电平时间: 83 [78, 88]
    wait_level_change(0, 78, 88, "response 0")

        // 响应高电平时间: 87 [80, 92]
       wait_level_change(1, 80, 92, "response 1")

        // 40bit数据， 信号0，1低电平时间[50, 58]  信号0高电平时间[23, 27] 信号1高电平时间[68, 74]
        for (i = 0; i < 5; i++)
    {
        for (j = 7; j >= 0; j--)
        {
            // 数据低电平时间
            wait_level_change(0, 49, 58, "data 0")

                // 数据高电平时间
                wait_level_change(1, 23, 74, "data 1")

                    dat[i] |= ((cnt > 50) << j);
        }
    }
    //printf("%d %d %d %d %d\n", (int)dat[0], (int)dat[1], (int)dat[2], (int)dat[3], (int)dat[4]);

    symbol = (dat[3] & 0x80) == 1 ? -1 : 1;
    *humidity = dat[0];
    *temperature = (float)((dat[2] + (dat[3] & 0X7F) * 0.1f) * symbol);

    if ((dat[0] + dat[1] + dat[2] + dat[3]) != dat[4])
    {
        return -1;
    }
    return 0;
}

void Show_DHT11()
{
    char cnt = 20;
    u8 humidity;
    char result;
    float temperature;
    result = Get_DHT11(&humidity, &temperature);

    while (result != 0 && cnt-- > 0)
    {
        delay_ms(50);
        result = Get_DHT11(&humidity, &temperature);
    }
    if (result != 0)
    {
        printf("fail to get humidity and temperature!");
    }
    else
    {
        printf("success to get: humidity: %d%%  temperature: %0.2fC\n", (int)humidity, temperature);
    }
}