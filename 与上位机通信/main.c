#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar flag,a,i;
uchar code table[4]="µÃµ½";

void init(){
 	TMOD=0x20;
	PCON=0x80;
	TH1=0xf4;
	TL1=0xf4;
	TR1=1;
//	SM0=0;
//	SM1=1;
//	REN=1;
	SCON=0x50;
	EA=1;
	ES=1;
}

void main(){
 	init();
	while(1){
	 	if(flag==1){
		 	ES=0;
			for(i=0;i<4;i++){
			 	SBUF=table[i];
				while(!TI);
				TI=0;
			}
			SBUF=a;
			while(!TI);
			TI=0;
			SBUF=0x0a;
			while(!TI);
			TI=0;
			ES=1;
			flag=0;
		}
	}
}

void ser() interrupt 4
{
 	RI=0;
	a=SBUF;
	flag=1;
}