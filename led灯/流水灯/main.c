#include<reg51.h>
#include<intrins.h>
void delay(unsigned int c)
{
	unsigned char a,b;
	for(;c>0;c--)
	  for(b=38;b>0;b--)
	    for(a=130;a>0;a--);
}
main()
{
	unsigned char LED;
	LED=0x01;
	while(1)
	{
		P0=LED;
		delay(50);
		LED=_crol_(LED,1);
	//	if(LED==0x00)
	//	{
	//	 LED=0x01;
	//	}
	}
}