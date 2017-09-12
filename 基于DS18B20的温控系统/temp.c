#include"temp.h"

void delay1ms(uint x){
 	uint y;
	for(;x>0;x--)
		for(y=110;y>0;y--);
}

uchar dsreset(){
	uchar i;
	ds=0;
	i=103;
	while(i--);
	ds=1;
	while(ds){
	 	delay1ms(1);
		i++;
		if(i>5)return 0;
	} 	
	return 1;
}

void tempwritebyte(uchar dat){
	uchar i,j;
	for(j=0;j<8;j++){
	 	ds=0;
		i++;
		ds=dat&0x01;
		i=6;
		while(i--);
		ds=1;
		dat>>=1;
	}
}

uchar tempreadbyte(){
 	uchar dat,bi,i,j;
	for(j=8;j>0;j--){
	 	ds=0;
		i++;
		ds=1;
		i++;i++;
		bi=ds;
		dat=(dat>>1)|(bi<<7);
		i=4;
		while(i--);
	}
	return dat;
}

void tempchange(){
 	dsreset();
	delay1ms(1);
	tempwritebyte(0xcc);
	tempwritebyte(0x44);
}

uint readtemp(){
 	int temp=0;
	uchar tmh,tml;
	tempchange();
	dsreset();
	delay1ms(1);
	tempwritebyte(0xcc);
	tempwritebyte(0xbe);
	tml=tempreadbyte();
	tmh=tempreadbyte();
	temp=tmh;
	temp<<=8;
	temp|=tml;
//	f_temp=temp*0.0625+0.05;
	temp=temp*0.0625*10+0.5;
	return temp;
}