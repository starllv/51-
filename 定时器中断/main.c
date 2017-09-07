#include<reg52.h>
sbit led=P1^0;
unsigned char num;
void main()
{
 	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1);
}

void T0_time() interrupt 1
{
 	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
	if(num==10)
	{
	 	num=0;
		led=~led;
	}
}