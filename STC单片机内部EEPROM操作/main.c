#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define RdCommand 0x01
#define PrgCommand 0x02
#define EraseCommand 0x03
#define Error 1
#define Ok 0
#define WaitTime 0x01

sfr ISP_DATA=0xe2;
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;

sbit LS138A=P2^2;
sbit LS138B=P2^3;
sbit LS138C=P2^4;

uchar code Disp_Tab[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar LedOut[8]={0,0,0,0,0,0,0,0};
uchar num;

void delayms(uint xms){
 	uint i,j;
	for(i=xms;i>0;i--)
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

		delayms(1);
	 }
}

void ISP_IAP_enable(){
 	EA=0;
	ISP_CONTR=ISP_CONTR&0x18;
	ISP_CONTR=ISP_CONTR|WaitTime;
	ISP_CONTR=ISP_CONTR|0x80;
}

void ISP_IAP_disable(){
 	ISP_CONTR=ISP_CONTR&0x7f;
	ISP_TRIG=0x00;
	EA=1;
}

void ISPgoon(){
 	ISP_IAP_enable();
	ISP_TRIG=0x46;
	ISP_TRIG=0xb9;
	_nop_();
}

unsigned char byte_read(unsigned int byte_addr){
 	ISP_ADDRH=(unsigned char)(byte_addr>>8);
	ISP_ADDRL=(unsigned char)(byte_addr&0x00ff);
	ISP_CMD=ISP_CMD&0xf8;
	ISP_CMD=ISP_CMD|RdCommand;
	ISPgoon();
	ISP_IAP_disable();
	return (ISP_DATA);
}

void SectorErase(unsigned int sector_addr){
 	uint iSectorAddr;
	iSectorAddr=(sector_addr&0xfe00);
	ISP_ADDRH=(unsigned char)(iSectorAddr>>8);
	ISP_ADDRL=0x00;
	ISP_CMD=ISP_CMD&0xf8;
	ISP_CMD=ISP_CMD|EraseCommand;
	ISPgoon();
	ISP_IAP_disable();
}

void byte_write(unsigned int byte_addr,unsigned char original_data){
 	ISP_ADDRH=(unsigned char)(byte_addr>>8);
	ISP_ADDRL=(unsigned char)(byte_addr&0x00ff);
	ISP_CMD=ISP_CMD&0xf8;
	ISP_CMD=ISP_CMD|PrgCommand;
	ISP_DATA=original_data;
	ISPgoon();
	ISP_IAP_disable();
}

void main(){
 	uchar num1;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	num1=byte_read(0x2000);
	if(num1>=60)num1=0;
	while(1){
	 	if(num>20){
		 	num=0;
			num1++;
			SectorErase(0x2000);
			byte_write(0x2000,num1);
			if(num1==60)num1=0;
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