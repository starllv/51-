#include<reg51.h>

sbit LED=P0^6;

void delay(unsigned int i)
{
	unsigned char j;
	for(i;i>0;i--)
		for(j=100;j>0;j--);
}

main()
{
	P0=0x00;
	while(1)
	{
		LED=1;
		delay(1000);
		LED=0;
		delay(1000);
	}
}