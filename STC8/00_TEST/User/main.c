#include <STC8H.H>

#define uchar unsigned char 
#define uint unsigned int 


void delay(uint i)	 //????
{
  uint j,k; 
  for(j=0;j<500;j++)
    for(k=0;k<i;k++);
}

void main(void)
{
	P0M0=0X00;P0M1=0X00;
	P1M0=0X00;P1M1=0X00;
	P2M0=0X00;P2M1=0X00;
	P3M0=0X00;P3M1=0X00;
	P4M0=0X00;P4M1=0X00;
	P5M0=0X00;P5M1=0X00;
	while(1)
	{
		P37 = 1;
		delay(1000);
	}

}
