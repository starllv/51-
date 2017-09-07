#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar code duanma[]={0xc0,0xf9,0xa4,0xb0,
					0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,
					0xc6,0xa1,0x86,0x8e};
					
void delay(uint time){
 	uint i;
	for(time;time>0;time--)
		for(i=110;i>0;i--);
} 

void keyscan(){
 	uchar temp,key;
	P3=0x7f;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f){
	 	delay(10);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f){
			temp=P3;
		 	switch(temp){
			 	case 0x77:key=15;
						break;
				case 0x7b:key=11;
						break;
				case 0x7d:key=7;
						break;
				case 0x7e:key=3;
						break;
			}
			while(temp!=0x0f){
			 	temp=P3;
				temp=temp&0x0f;
				P0=duanma[key];
			}
			P0=0xff;
		}
	}
	P3=0xbf;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f){
	 	delay(10);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f){
		 	temp=P3;
			switch(temp){
			 	case 0xb7:key=14;
						break;
				case 0xbb:key=10;
						break;
				case 0xbd:key=6;
						break;
				case 0xbe:key=2;
						break;
			}
			while(temp!=0x0f){
			 	temp=P3;
				temp=temp&0x0f;
				P0=duanma[key];
			}
			P0=0xff;
		}
	}
	P3=0xdf;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f){
	 	delay(10);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f){
		 	temp=P3;
			switch(temp){
			 	case 0xd7:key=13;
						break;
				case 0xdb:key=9;
						break;
				case 0xdd:key=5;
						break;
				case 0xde:key=1;
						break;
			}
			while(temp!=0x0f){
			 	temp=P3;
				temp=temp&0x0f;
				P0=duanma[key];
			}
			P0=0xff;
		}
	}
	P3=0xef;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f){
	 	delay(10);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f){
		 	temp=P3;
			switch(temp){
			 	case 0xe7:key=12;
						break;
				case 0xeb:key=8;
						break;
				case 0xed:key=4;
						break;
				case 0xee:key=0;
						break;
			}
			while(temp!=0x0f){
			 	temp=P3;
				temp=temp&0x0f;
				P0=duanma[key];
			}
			P0=0xff;
		}
	}
}

void main(){
 	P0=0xff;
	while(1){
	 	keyscan();
	}
}