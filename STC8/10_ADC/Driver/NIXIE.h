#ifndef __NIXIE_H__
#define __NIXIE_H__

#include	"GPIO.h"
#include	"NVIC.h"
#include	"Switch.h"
#include "Delay.h"

#define COM1 P41
#define COM2 P42
#define COM3 P44
#define COM4 P45

#define a1 P20
#define b1 P21
#define c1 P22
#define d1 P23
#define e1 P24
#define f1 P25
#define g1 P26
#define dp P27


#define uchar unsigned char 
#define uint unsigned int 
	
#define COM_GPIO GPIO_P4
#define COM_PIN (GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5)
#define DIG_GPIO GPIO_P2
#define DIG_PIN GPIO_Pin_All
#define DIG_RIG_Pin P2

void Nixie_Init();
void Nixie_Display(uint num);
#endif