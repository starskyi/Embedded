/*******************************************************************************  
* 文件名称：LED流水灯
* 实验目的：了解基本IO口的配置及操作 
* 硬件说明：STC8H8K64U @11.0592MHz   LED灯
* 日期版本：2022-05-28
*	程序作者：大科工作室
* 淘宝店铺：shop117015787.taobao.com 
* 特别提醒：本程序仅适用于板载LED控制；
						如果使用的是其他模块，请根据自行调整程序；
*******************************************************************************/

#include <STC8H.H>
#include <intrins.H>

unsigned char temp;

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main(void)
{
	P0M0=0X00;P0M1=0X00;
	P1M0=0X00;P1M1=0X00;
	P2M0=0X00;P2M1=0X00;
	P3M0=0X00;P3M1=0X00;
	P4M0=0X00;P4M1=0X00;
	while(1)
	{
		P0=0X7F;			//设置初值 ffff fff0
//		for(temp=0;temp<8;temp++)
//		{
//			P0=_crol_(P0,1);			//左移函数，每间隔500ms左移一位
//			Delay500ms();
//		}
	}
}