#include<reg51.h>
#include<intrins.h>

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

void write_ds(uchar add,uchar date);
uchar read_ds(uchar add);
void set_time();