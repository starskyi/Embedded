#ifndef __NTC_H__
#define __NTC_H__

#include "ADC.H"
#include	"GPIO.h"
#include	"Switch.h"
#include	"NVIC.h"


void	NTC_Init(void);
int Get_Temperature();

#endif