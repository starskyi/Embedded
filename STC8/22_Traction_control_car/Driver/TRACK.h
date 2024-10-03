#ifndef __TRACK_H__ 
#define __TRACK_H__

#include "Config.h"

#define TRANCK_S1 P05

#define TRANCK_S2 P04
#define TRANCK_S3 P03
#define TRANCK_S4 P02

void Track_Init();

void Get_status(u8 status[]);
int get_direction();

#endif