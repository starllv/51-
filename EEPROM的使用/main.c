#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

bit write=0;
sbit scl = P2^1;
sbit sda = P2^0;
uchar sec,tcnt;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
unsigned char code GPIO_DIG_CODE[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar displaydate[2];

void delay(){
	;;
}

void delay1ms(uint z){
 	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void start(){
	sda=1;
	delay(); 	
	scl=1;
	delay();
	sda=0;
	delay();
}

void stop(){
 	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}

void respons(){
 	uchar i;
	scl=1;
	delay();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay();
}

void init(){
 	sda=1;
	delay();
	scl=1;
	delay();
}

void write_byte(uchar date){
 	uchar i,temp;
	temp=date;
	for(i=0;i<8;i++){
	 	temp=temp<<1;
		scl=0;
		delay();
		sda=CY;
		delay();
		scl=1;
		delay();
	}
	scl=0;
	delay();
	sda=1;
	delay();
}

uchar read_byte(){
 	uchar i,k;
	scl=0;
	delay();
	sda=1;
	delay();
	for(i=0;i<8;i++){
	 	scl=1;
		delay();
		k=(k<<1)|sda;
		scl=0;
		delay();
	}
	return k;
}

void write_add(uchar address,uchar date){
 	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	write_byte(date);
	respons();
	stop();
}

uchar read_add(uchar address){
 	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	stop();
	return date;
}

void display(uchar shi,uchar ge){
	P0=0;
	LSA=0;LSB=1;LSC=1;
	P0=GPIO_DIG_CODE[shi];
	P0=0;
	LSA=1;LSB=1;LSC=1;
	P0=GPIO_DIG_CODE[ge];
}

void main(){
 	init();
	sec=read_add(2);
	if(sec>100)sec=0;
	TMOD=0x01;
	ET0=1;
	EA=1;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=1;
	while(1){
		display(displaydate[0],displaydate[1]);
		if(write==1){
		 	write=0;
			write_add(2,sec);
		}
	}
}

void t0() interrupt 1{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tcnt++;
	if(tcnt==20){
	 	tcnt=0;
		sec++;
		write=1;
		if(sec==100)sec=0;
		displaydate[0]=sec/10;
		displaydate[1]=sec%10;
	} 							
}