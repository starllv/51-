#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit jia=P1^0;
sbit jian=P1^1;
sbit pwm=P0^1;

uchar count,jd;

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
			count=0;
		 	jd++;
			if(jd>=6)jd=5;
			while(!jia);
		}
	}
	if(jian==0){
	 	delay(10);
		if(jian==0){
			count=0;
			jd--;
			if(jd==0)jd=1;
			while(!jian);
		}
	}
}

void main(){
 	jd=4;
	count=0;
	time_init();
	while(1){
	 	key();
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