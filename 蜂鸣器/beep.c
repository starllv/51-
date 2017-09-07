#include<reg51.h>

sbit beep = P2^7;

 void delay(unsigned int i)
 {
 	unsigned char j;
	for(i;i>0;i--)
		for(j=100;j>0;j--);
 }

 void di(){
 unsigned char i;
 	for(i=8;i>0;i--){
  	beep=0;
	delay(10);
	beep=1;
	delay(10);
	}
 }

void main()
 {
 	di();
	while(1);
 }