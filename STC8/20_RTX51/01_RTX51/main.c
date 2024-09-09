#include <STC8H.h>
#include "Config.h"
#include <RTX51TNY.h>

void Delay500ms()		//@24.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 61;
	j = 225;
	k = 62;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void sys_init()
{
	P0M1 = 0;P0M0 = 0;
	P00 = 0;
	P07 = 1;
}

void task0() _task_ 0
{
	sys_init();
	os_create_task(1);
	os_create_task(2);
	
	os_delete_task(0);
	
}

void task1() _task_ 1
{
	
	while(1)
	{
		os_wait2(K_TMO, 100);  //1: 5ms  (24M)
		P00 = !P00;
	};
	
}

void task2() _task_ 2
{
	
	while(1)
	{
		os_wait2(K_TMO, 100);
		P07 = !P07;
	};
	
}
