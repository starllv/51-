#include"ds1302.h"

void write_ds(uchar add,uchar date){
 	uchar n;
	RST=0;
	_nop_();

	SCLK=0;
	_nop_();
	RST=1;
	_nop_();

	for(n=0;n<8;n++){
	 	DSIO=add&0x01;
		add>>=1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	for(n=0;n<8;n++){
		DSIO=date&0x01;
		date>>=1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();	 	
	}

	RST=0;
	_nop_();
}

uchar read_ds(uchar add){
 	uchar n,dat,dat1;
	RST=0;
	_nop_();

	SCLK=0;
	_nop_();
	RST=1;
	_nop_();

	for(n=0;n<8;n++){
	 	DSIO=add&0x01;
		add>>=1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	_nop_();
	for(n=0;n<8;n++){
	 	dat1=DSIO;
		dat=(dat>>1)|(dat1<<7);
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}

	RST=0;
	_nop_();
	SCLK=1;
	_nop_();
	DSIO=0;
	_nop_();
	DSIO=1;
	_nop_();
	return dat;
}

void set_time(){
 	write_ds(0x8e,0x00);
	write_ds(0x80,0);
	write_ds(0x82,0x30);
	write_ds(0x84,0x13);
	write_ds(0x86,0x07);
	write_ds(0x88,0x09);
	write_ds(0x8a,0x04);
	write_ds(0x8c,0x17);
}

