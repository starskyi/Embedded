#include "DS1302Clock.h"


void Delay_1us(void)
{
	NOP1();
}
void Ds1302_Init(void)
{
	DS1302_RST=0;			//RST���õ�
  DS1302_CLK=0;			//SCK���õ�
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

    //DS1302_IO = 1; // ����IOΪ����

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
	
		
    clock->year = DS1302_ReadByte(ds1302_year_add);		//��
//		DS1302_CLK = 0;
//		DS1302_CLK = 1;
		//DS1302_ReadByte(ds1302_year_add);
	
		
    clock->month = DS1302_ReadByte(ds1302_month_add);		//��
		//DS1302_ReadByte(ds1302_month_add);
	
		
    clock->day = DS1302_ReadByte(ds1302_date_add);		//��
		//DS1302_ReadByte(ds1302_date_add);
	
		
		clock->hour = DS1302_ReadByte(ds1302_hr_add);		//ʱ
		//DS1302_ReadByte(ds1302_hr_add);
	
		
    clock->minute = DS1302_ReadByte(ds1302_min_add);		//��
		//DS1302_ReadByte(ds1302_min_add);
		
		
    clock->second = (DS1302_ReadByte(ds1302_sec_add))&0x7f;  //�룬������ĵ�7λ�����ⳬ��59
		//DS1302_ReadByte(ds1302_sec_add);
		
		
    clock->week = DS1302_ReadByte(ds1302_day_add);		//��
		//DS1302_ReadByte(ds1302_day_add);
		
	
	   //BCD��ת��
	  
		
}

void Ds1302_Write_Byte(uchar addr, uchar d)
{
    uchar i;
    DS1302_RST=1;					//����DS1302����

    //д��Ŀ���ַ��addr
    addr = addr & 0xFE;   //���λ���㣬�Ĵ���0λΪ0ʱд��Ϊ1ʱ��
    for (i = 0; i < 8; i ++) {
        if (addr & 0x01) {
            DS1302_IO=1;
        }
        else {
            DS1302_IO=0;
        }
        DS1302_CLK=1;      //����ʱ��
        Delay_1us();
        DS1302_CLK=0;
        addr = addr >> 1;
    }
    //д�����ݣ�d
    for (i = 0; i < 8; i ++) {
        if (d & 0x01) {
            DS1302_IO=1;
        }
        else {
            DS1302_IO=0;
        }
        DS1302_CLK=1;    //����ʱ��
        Delay_1us();
        DS1302_CLK=0;
        d = d >> 1;
    }
    DS1302_RST=0;		//ֹͣDS1302����
}

void Ds1302_Write_Time(Clock clock)
{
		Ds1302_Write_Byte(ds1302_control_add,0x00);			//�ر�д����
    Ds1302_Write_Byte(ds1302_sec_add,0x80);				//��ͣʱ��
    //ds1302_write_byte(ds1302_charger_add,0xa9);	    //������
    Ds1302_Write_Byte(ds1302_year_add,clock.year);		//��
    Ds1302_Write_Byte(ds1302_month_add,clock.month);	//��
    Ds1302_Write_Byte(ds1302_date_add, clock.day);		//��
    Ds1302_Write_Byte(ds1302_hr_add,clock.hour);		//ʱ
    Ds1302_Write_Byte(ds1302_min_add,clock.minute);		//��
    Ds1302_Write_Byte(ds1302_sec_add,clock.second);		//��
    Ds1302_Write_Byte(ds1302_day_add,clock.week);		//��
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����
}