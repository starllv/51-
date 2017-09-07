#include<reg51.h>
void delay(unsigned int i)
{
	unsigned char j;
	for(i;i>0;i--)
	    for(j=100;j>0;j--);

}
void main(void)
{
	unsigned int led[9]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	int i;
    while(1)
	{
		P0 = 0x00;
		delay(1000);
		P0 = 0x00;
		delay(1000);
		for(i=0;i<9;i++)
		{
			P0=led[i];
			delay(1000);
		}

	}
}