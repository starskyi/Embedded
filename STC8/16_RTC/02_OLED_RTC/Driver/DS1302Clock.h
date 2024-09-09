#include	"Config.h"

#define uchar unsigned char
#define uint  unsigned int

#define CENTURY 20

#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84	//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90
#define ds1302_clkburst_add		0xbe

sbit DS1302_RST = P4^4;
sbit DS1302_IO = P4^2;
sbit DS1302_CLK = P4^1;

typedef struct{
	uchar year;
	uchar month;
	uchar day;
	uchar week;
	uchar hour;
	uchar minute;
	uchar second;
} Clock;

//typedef struct{
//	uint 

//}
static uchar time_buf[8] = {0x21,0x10,0x09,0x14,0x23,0x59,0x55,0x05};//初始时间

void Delay_1us(void);
void Ds1302_Init(void);

uchar DS1302_ReadByte(uchar addr);
void DS1302_Read_Time(Clock *clock);

void Ds1302_Write_Byte(uchar addr, uchar d);
void Ds1302_Write_Time(Clock clock);
