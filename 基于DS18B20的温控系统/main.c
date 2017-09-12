#include<reg51.h>
#include<stdio.h>
#include"temp.h"

#define uchar unsigned char
#define uint unsigned int

sbit lsa=P2^2;
sbit lsb=P2^3;
sbit lsc=P2^4;

uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	//不带小数点
//					0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};	//带小数点
//float f_temp;
uchar displaydata[8];

void display(){
	uchar i;
	for(i=0;i<8;i++){
	 	switch(i)
		{
		 	case 0:
				lsa=0;lsb=0;lsc=0;break;
			case 1:
				lsa=1;lsb=0;lsc=0;break;
			case 2:
				lsa=0;lsb=1;lsc=0;break;
			case 3:
				lsa=1;lsb=1;lsc=0;break;
			case 4:
				lsa=0;lsb=0;lsc=1;break;
			case 5:
				lsa=1;lsb=0;lsc=1;break;
			case 6:
				lsa=0;lsb=1;lsc=1;break;
			case 7:
				lsa=1;lsb=1;lsc=1;break;
		}
		P0=displaydata[i];
		delay1ms(1);
		P0=0;
	} 	
}

void dis_temp(uint temp){
 	displaydata[0]=table[temp/100];
	displaydata[1]=table[temp%100/10]|0x80;
	displaydata[2]=table[temp%10];
	display();	
}

void init_com(){
 	TMOD=0x20;
	PCON=0x00;
	SCON=0x50;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
}

void comm(char *parr){
 	do{
		SBUF=*parr++;
		while(!TI);
		TI=0;
	}while(*parr);
}

void main(){
	uchar buff[4];
 	init_com();
	while(1){
	 	dis_temp(readtemp());
		delay1ms(5);
		sprintf(buff,"%f",((readtemp()-0.5)/10+0.05));
		dis_temp(readtemp());
		delay1ms(5);
		comm(buff);
		dis_temp(readtemp());
		delay1ms(5);
	}
}