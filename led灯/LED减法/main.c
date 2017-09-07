#include<reg52.h>
void delay(unsigned int c)
{
	unsigned char a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}

void main()
{
	unsigned char NUM =0xff;
	while(1)
	{
		P0=NUM;
		delay(50);
		NUM--;
	}
}
