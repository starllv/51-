#include<reg52.h>
#include<intrins.h>

void delay(unsigned int c)
{
	unsigned char a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);	
}

void main()
{
	unsigned char LED;
	LED=0xfe;
	while(1)
	{
		P0=LED;
		delay(20);
		LED=_crol_(LED,1);
	}
}