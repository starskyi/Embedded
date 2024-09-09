#include	"Config.h"

#define uchar unsigned char
#define uint  unsigned int

#define CENTURY 20

#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84	//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
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
static uchar time_buf[8] = {0x21,0x10,0x09,0x14,0x23,0x59,0x55,0x05};//��ʼʱ��

void Delay_1us(void);
void Ds1302_Init(void);

uchar DS1302_ReadByte(uchar addr);
void DS1302_Read_Time(Clock *clock);

void Ds1302_Write_Byte(uchar addr, uchar d);
void Ds1302_Write_Time(Clock clock);
