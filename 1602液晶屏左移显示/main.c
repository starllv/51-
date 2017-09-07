#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="Hello everyone!";
uchar code table1[]="Welcome to here!";
#define LCD_DATAPINS P0
sbit LCD_E=P2^7;
sbit LCD_RW=P2^5;
sbit LCD_RS=P2^6;
uchar num;

void delay(uint z){
 	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_com(uchar com){
 	LCD_RS=0;
	LCD_RW=0;
	LCD_DATAPINS=com;
	delay(5);
	LCD_E=1;
	delay(5);
	LCD_E=0;
}

void write_date(uchar date){
 	LCD_RS=1;
	LCD_RW=0;
	LCD_DATAPINS=date;
	delay(5);
	LCD_E=1;
	delay(5);
	LCD_E=0;
}

void init(){
 	LCD_E=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

void main(){
 	init();
	write_com(0x80+0x10);
	for(num=0;num<15;num++){
	 	write_date(table[num]);
		delay(5);
	}
	write_com(0x80+0x50);
	for(num=0;num<16;num++){
	 	write_date(table1[num]);
		delay(5);
	}
	delay(1000);
	for(num=0;num<16;num++){
	 	write_com(0x18);
		delay(200);
	}
	while(1);
}