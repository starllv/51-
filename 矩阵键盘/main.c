#include<reg52.h>
unsigned char keyvalue;
unsigned char led[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay(unsigned char c);
void key();
void main()
{
	while(1)
	{
		 key();
		 P0=~led[keyvalue];
	}
}

void key()
{
	P1=0x0f;
	if(P1!=0x0f)
	{
		delay(1);
		if(P1!=0x0f)
		{
			switch(P1)
			{
				case (0x07):keyvalue=12;break;
				case (0x0b):keyvalue=8;break;
				case (0x0d):keyvalue=4;break;
				case (0x0e):keyvalue=0;break;
			}
			P1=0xf0;
			switch(P1)
			{
				case (0x70):keyvalue=keyvalue+3;break;
				case (0xb0):keyvalue=keyvalue+2;break;
				case (0xd0):keyvalue=keyvalue+1;break;
				case (0xe0):keyvalue=keyvalue;break;
			}
			while(P1!=0xf0);
		}
	}
}

void delay(unsigned char c)
{		
	unsigned char a,b;
	for(;c>0;c--);
		for(b=38;b>0;b--);
			for(a=130;a>0;a--);
}