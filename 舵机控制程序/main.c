#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit jia=P1^6;
sbit jian=P1^7;
sbit pwm=P3^0;

uchar count,jd;
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void delay(uint x){
 	uchar y;
	for(x;x>0;x--)
		for(y=125;y>0;y--);
}

void time_init(){
 	TMOD=0x01;
	IE=0x82;
	TH0=0xfe;
	TL0=0x33;
	TR0=1;
}

void key(){
 	if(jia==0){
	 	delay(10);
		if(jia==0){
			while(!jia);
			count=0;
		 	jd++;
			if(jd>=6)jd=5;
		}
	}
	if(jian==0){
	 	delay(10);
		if(jian==0){
			while(!jian);
			count=0;
			jd--;
			if(jd==0)jd=1;
		}
	}
}

void main(){
 	jd=1;
	count=0;
	time_init();
	while(1){
	 	key();
		P0=table[jd];
	}
}

void time() interrupt 1
{
 	TH0=0xfe;
	TL0=0x33;
	if(count<jd){
		pwm=1;
	}
	else{
		pwm=0;
	}
	count += 1;
	count=count%40;
}