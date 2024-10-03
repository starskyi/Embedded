#include "TRACK.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Switch.h"




void Track_Init()
{
	P0_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5)

}

void Get_status(u8 status[])
{
	status[0] = TRANCK_S1;
	status[1] = TRANCK_S2;
	status[2] = TRANCK_S3;
	status[3] = TRANCK_S4;

}

//获取转向
int get_direction()
{
		u8 track_status[4];
		static int last_position = 0;
		int sum = 0, count = 0, position;
		
		Get_status(track_status);
		
		if(TRANCK_S1)
		{
			sum -= 64;
			count++;
		}
		if(TRANCK_S2)
		{
			sum -= 32;
			count++;
		}
		if(TRANCK_S3)
		{
			sum += 32;
			count++;
		}
		if(TRANCK_S4)
		{
			sum += 64;
			count++;
		}
		
		if(count == 0)
		{
			return last_position;
		}
		
		position = sum / count;
		last_position = position;
		return position;
		
}