#include<reg51.h>

#define uint unsigned int
#define uchar unsigned char

sfr WDT_CONTR=0xe1;
sbit led=P1^0;

void delay(uint x){
	uint i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--); 	
}

void main(){
	P1=0;
 	WDT_CONTR=0x35;
	delay(500);
	led=1;
	delay(700);
	led=0;
	while(1){
	 	delay(1000);
		WDT_CONTR=0x35;
	}
}