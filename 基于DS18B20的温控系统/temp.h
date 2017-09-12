#ifndef uchar 
#define uchar unsigned char
#endif

#include<reg51.h>

#ifndef uint
#define uint unsigned int
#endif

sbit ds=P3^7;

//float f_temp;

void delay1ms(uint x);
uchar dsreset();
void tempwritebyte(uchar dat);
uchar tempreadbyte();
void tempchange();
uint readtemp();