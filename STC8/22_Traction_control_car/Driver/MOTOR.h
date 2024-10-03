#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Config.h"

#define LQ_AIN2 P45
#define LQ_AIN1 P27
#define STBY_F P26
#define RQ_BIN1 P25
#define RQ_BIN2 P24 


#define LH_AIN2 P36
#define LH_AIN1 P35
#define STBY_B P34
#define RH_BIN1 P33
#define RH_BIN2 P32


void Motor_Init();

void forward();
void retreat();
void left(u8 angle_value);
void right(u8 angle_value);
void stop();
void turn_around_right();
void turn_around_left();


#endif