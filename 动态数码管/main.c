#include<reg52.h>
void main()
{
	P1=0xfe;
	P0=0xbf;
	while(1);
}