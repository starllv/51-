#include<reg52.h>
#define GPIO_KEY P1
#define GPIO_LED P0

void delay(unsigned int c);
unsigned char Key_Scan();

void main()
{
	unsigned char ledValue,keyNum;
	ledValue=0x00;
	while(1)
	{
		keyNum=Key_Scan();
		switch(keyNum)
		{
			case(0xfe):
				ledValue=0x01;
				break;
			case(0xfd):
				ledValue=0x02;
				break;
			case(0xfb):
				ledValue=0x04;
				break;
			case(0xf7):
				ledValue=0x08;
				break;
			case(0xef):
				ledValue=0x10;
				break;
			case(0xdf):
				ledValue=0x20;
				break;
			case(0xbf):
				ledValue=0x40;
				break;
			case(0x7f):
				ledValue=0x80;
				break;
			default:
				break;	
		}
		GPIO_LED=ledValue;
	}
}

unsigned char Key_Scan()
{
	unsigned char keyValue=0;
	if(GPIO_KEY != 0xff)
	{
		delay(1);
		if(GPIO_KEY != 0xff)
		{
			keyValue=GPIO_KEY;
			while(GPIO_KEY!=0xff);
		}
	}
	return keyValue;
}

void delay(unsigned int c)
{
	unsigned char a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}