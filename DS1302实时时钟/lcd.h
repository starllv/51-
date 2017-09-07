#include<reg51.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int 
#endif

#define DATAPINS P0
sbit E=P2^7;
sbit RW=P2^5;
sbit RS=P2^6;

void lcd_delay1ms(uint c);
void writecom(uchar com);
void writedata(uchar dat);
void lcdinit();
