#ifndef __BUTTON_H__
#define __BUTON_H__

#include "GPIO.h"
#include "NVIC.h"
#include "Config.h"

#define S1 P30
#define S2 P31
#define S3 P32
#define S4 P33
#define UP 1
#define DOWN 0

#define BUTTON_GPIO GPIO_P3
#define BUTTON_PIN GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3

#define IS_KEY_UP(i) (status & (1 << i)) >= 1
#define IS_KEY_DOWN(i) (status & (1 << i)) == 0

#define SET_KEY_DOWN(i) status &= ~(1 << i)
#define SET_KEY_UP(i) status |= (1 << i)

void Button_Init();
void buttonClick();

#endif