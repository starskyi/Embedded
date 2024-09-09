#include "DS1302Clock.h"


void Delay_1us(void)
{
	NOP1();
}
void Ds1302_Init(void)
{
	DS1302_RST=0;			//RST脚置低
  DS1302_CLK=0;			//SCK脚置低
}

uchar DS1302_ReadByte(uchar addr)
{
    uchar dat = 0;
    uchar i;

		DS1302_RST = 0;
		NOP1();
    DS1302_CLK = 0;
		NOP1();
		DS1302_RST = 1;
    addr = addr | 0x01;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = addr & 0x01;
				NOP1();
        DS1302_CLK = 1;
        Delay_1us();
        DS1302_CLK = 0;
        addr >>= 1;
    }

    //DS1302_IO = 1; // 设置IO为输入

//		DS1302_CLK = 0;
//		NOP1();
//    DS1302_CLK = 0;
    for (i = 0; i < 8; i++)
    {
        dat >>= 1;
        if (DS1302_IO)
        {
            dat |= 0x80;
        }
        else
        {
            dat &= 0x7F;
        }
        DS1302_CLK = 1;
        Delay_1us();
        DS1302_CLK = 0;
    }
		DS1302_RST = 0;
    return dat;
}


void DS1302_Read_Time(Clock *clock)
{
	
		
    clock->year = DS1302_ReadByte(ds1302_year_add);		//年
//		DS1302_CLK = 0;
//		DS1302_CLK = 1;
		//DS1302_ReadByte(ds1302_year_add);
	
		
    clock->month = DS1302_ReadByte(ds1302_month_add);		//月
		//DS1302_ReadByte(ds1302_month_add);
	
		
    clock->day = DS1302_ReadByte(ds1302_date_add);		//日
		//DS1302_ReadByte(ds1302_date_add);
	
		
		clock->hour = DS1302_ReadByte(ds1302_hr_add);		//时
		//DS1302_ReadByte(ds1302_hr_add);
	
		
    clock->minute = DS1302_ReadByte(ds1302_min_add);		//分
		//DS1302_ReadByte(ds1302_min_add);
		
		
    clock->second = (DS1302_ReadByte(ds1302_sec_add))&0x7f;  //秒，屏蔽秒的第7位，避免超出59
		//DS1302_ReadByte(ds1302_sec_add);
		
		
    clock->week = DS1302_ReadByte(ds1302_day_add);		//周
		//DS1302_ReadByte(ds1302_day_add);
		
	
	   //BCD码转换
	  
		
}

void Ds1302_Write_Byte(uchar addr, uchar d)
{
    uchar i;
    DS1302_RST=1;					//启动DS1302总线

    //写入目标地址：addr
    addr = addr & 0xFE;   //最低位置零，寄存器0位为0时写，为1时读
    for (i = 0; i < 8; i ++) {
        if (addr & 0x01) {
            DS1302_IO=1;
        }
        else {
            DS1302_IO=0;
        }
        DS1302_CLK=1;      //产生时钟
        Delay_1us();
        DS1302_CLK=0;
        addr = addr >> 1;
    }
    //写入数据：d
    for (i = 0; i < 8; i ++) {
        if (d & 0x01) {
            DS1302_IO=1;
        }
        else {
            DS1302_IO=0;
        }
        DS1302_CLK=1;    //产生时钟
        Delay_1us();
        DS1302_CLK=0;
        d = d >> 1;
    }
    DS1302_RST=0;		//停止DS1302总线
}

void Ds1302_Write_Time(Clock clock)
{
		Ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护
    Ds1302_Write_Byte(ds1302_sec_add,0x80);				//暂停时钟
    //ds1302_write_byte(ds1302_charger_add,0xa9);	    //涓流充电
    Ds1302_Write_Byte(ds1302_year_add,clock.year);		//年
    Ds1302_Write_Byte(ds1302_month_add,clock.month);	//月
    Ds1302_Write_Byte(ds1302_date_add, clock.day);		//日
    Ds1302_Write_Byte(ds1302_hr_add,clock.hour);		//时
    Ds1302_Write_Byte(ds1302_min_add,clock.minute);		//分
    Ds1302_Write_Byte(ds1302_sec_add,clock.second);		//秒
    Ds1302_Write_Byte(ds1302_day_add,clock.week);		//周
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护
}