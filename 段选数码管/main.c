#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
//uchar code weima[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
uchar code weima[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar code duanma[]={0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};

void delay(uint time){
	uint i;
	for(time;time>0;time--)
		for(i=110;i>0;i--); 	
}

void main(){
 	uchar num;
	while(1){
	 	if(num>7)num=0;
		P0=weima[num];
		P1=duanma[num];
		delay(1);
		num++;
	}
}