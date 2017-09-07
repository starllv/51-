#include<reg51.h>

#define uint unsigned int
#define uchar unsigned char

sbit LS138A=P2^2;
sbit LS138B=P2^3;
sbit LS138C=P2^4;

uchar code Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
uchar LedOut[8]={0,0,0,0,0,0,0,0},num;

void delay(uint x){
 	uint i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}

void display(){
	uchar i;
	for( i=0; i<8; i++) 
	 {	 
	 	P0 = Disp_Tab[LedOut[i]];
			
	  	switch(i)					  
	     {	    
			case 0:LS138A=0; LS138B=0; LS138C=0; break;         
	        case 1:LS138A=1; LS138B=0; LS138C=0; break;             	
	        case 2:LS138A=0; LS138B=1; LS138C=0; break; 
	        case 3:LS138A=1; LS138B=1; LS138C=0; break; 
			case 4:LS138A=0; LS138B=0; LS138C=1; break;
			case 5:LS138A=1; LS138B=0; LS138C=1; break;
			case 6:LS138A=0; LS138B=1; LS138C=1; break;
			case 7:LS138A=1; LS138B=1; LS138C=1; break;
			
	     }

		delay(1);
	 }
}

void main(){
 	uchar num1;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	EX0=1;
	EX1=1;
	TR0=1;
	while(1){
	 	if(num>=20){
		 	num=0;
			num1++;
			if(num1==6){
			 	ET0=0;
				PCON=0x02;
			}
			LedOut[6]=num1/10;
			LedOut[7]=num1%10;
		}
		display();
	}
}

void timer() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
}

void ex_int0() interrupt 0
{
 	PCON=0;
	ET0=1;
}

void ex_int1() interrupt 2
{
 	PCON=0;
	ET0=1;
}