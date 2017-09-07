#include<reg52.h>
void delay(unsigned int c);
unsigned char LED;
void main()
{
	unsigned char i;
	LED=0x01;
	while(1)
	{
		for(i=0;i<7;i++)
		{
			P0=LED;
			delay(50);
			LED=LED<<1;
		}
		for(i=0;i<7;i++)
		{
			P0=LED;
			delay(50);
			LED=LED>>1;
		}
	}
}

void delay(unsigned int c)
{
	unsigned char a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}