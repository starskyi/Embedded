#ifndef __BUZZER_H__
#define __BUZZER_H__

#include	"Config.h"
#include	"STC8H_PWM.h"
#include	"GPIO.h"
#include	"NVIC.h"
#include	"Switch.h"
#include "Delay.h"

#define	L1	1
#define	L2	2
#define	L3	3
#define	L4	4
#define	L5	5
#define	L6	6
#define	L7	7

#define N0 0

#define	N1	L1 + 7
#define	N2	L2 + 7
#define	N3	L3 + 7
#define	N4	L4 + 7
#define	N5	L5 + 7
#define	N6	L6 + 7
#define	N7	L7 + 7

#define	H1	N1 + 7
#define	H2	N2 + 7
#define	H3	N3 + 7
#define	H4	N4 + 7
#define	H5	N5 + 7
#define	H6	N6 + 7
#define	H7	N7 + 7


void delay(u16 ms);
void PWM_config(u16 hz_value);
void Buzzer_Init();
void Buzzer_Stop();
void Buzzer_Sing(u8 music[], u8 duration[], u16 hz[], u16 len);
void two_tiger();
void sky_city();
void Buzzer_loud();

#endif


