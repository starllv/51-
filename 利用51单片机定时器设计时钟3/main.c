#include<reg51.h>
#include<i2c.h>

#define uint unsigned int
#define uchar unsigned char

sbit lcden=P2^7;
sbit rs=P2^6;
sbit s1=P2^3;
sbit s2=P2^4;
sbit s3=P2^5;
sbit beep=P3^0;

uchar count,s1num;
char miao,shi,fen;
uchar code table[]="  2017-08-22 TUE";

void delay(uint x){
 	uchar y;
	for(x;x>0;x--)
		for(y=110;y>0;y--); 
}

void di(){
 	uchar i;
	for(i=8;i>0;i--){
	 	beep=0;
		delay(10);
		beep=1;
		delay(10);
	}
}

void write_com(uchar com){
 	rs=0;
	lcden=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}

void write_data(uchar date){
 	rs=1;
	lcden=0;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}

void write_sfm(uchar add,uchar date){
 	uchar ge,shi;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+add);
	write_data(0x30+shi);
	write_data(0x30+ge);
}

void init(){
 	uchar num;
	lcden=0;
	shi=0;
	fen=0;
	miao=0;
	count=0;
	s1num=0;
	//init_24c02();
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
	for(num=0;num<15;num++){
	 	write_data(table[num]);
		delay(5);
	}
	write_com(0x80+0x40+6);
	write_data(':');
	delay(5);
	write_com(0x80+0x40+9);
	write_data(':');
	delay(5);
	miao=At24c02Read(1);
	fen=At24c02Read(2);
	shi=At24c02Read(3);
	write_sfm(10,miao);
	write_sfm(7,fen);
	write_sfm(4,shi);
	TMOD=0x01;
	TH0=15536/256;
	TL0=15536%256;
	EA=1;
	ET0=1;
	TR0=1;
}

void keyscan(){
 	if(s1==0){
	 	delay(5);
		if(s1==0){
		 	s1num++;
			while(!s1);
			di();
			if(s1num==1){
			 	TR0=0;
				write_com(0x80+0x40+10);
				write_com(0x0f);
			}
			if(s1num==2){
			 	write_com(0x80+0x40+7);
			}
			if(s1num==3){
			 	write_com(0x80+0x40+4);
			}
			if(s1num==4){
			 	s1num=0;
				write_com(0x0c);
				TR0=1;
			}
		}
	}
	if(s1num!=0){
	 	if(s2==0){
		 	delay(5);
			if(s2==0){
			 	while(!s2);
				di();
				if(s1num==1){
				 	miao++;
					if(miao>=60)miao=0;
					write_sfm(10,miao);
					write_com(0x80+0x40+10);
					At24c02Write(1,miao);	
				}
				if(s1num==2){
				 	fen++;
					if(fen>=60)fen=0;
					write_sfm(7,fen);
					write_com(0x80+0x40+7);
					At24c02Write(2,fen);
				}
				if(s1num==3){
				 	shi++;
					if(shi>=24)shi=0;
					write_sfm(4,shi);
					write_com(0x80+0x40+4);
					At24c02Write(3,shi);
				}
			}
		}
		if(s3==0){
		 	delay(5);
			if(s3==0){
			 	while(!s3);
				di();
				if(s1num==1){
				 	miao--;
					if(miao==-1)miao=59;
					write_sfm(10,miao);
					write_com(0x80+0x40+10);
					At24c02Write(1,miao);
				}
				if(s1num==2){
				 	fen--;
					if(fen==-1)miao=59;
					write_sfm(7,fen);
					write_com(0x80+0x40+7);
					At24c02Write(2,fen);
				}
				if(s1num==3){
				 	shi--;
					if(shi==-1)shi=23;
					write_sfm(4,shi);
					write_com(0x80+0x40+4);
					At24c02Write(3,shi);
				}
			}
		}
	}
}

void main(){
 	init();
	while(1){
		keyscan();
	}
}

void timer() interrupt 1
{
 	TH0=15536/256;
	TL0=15536%256;
	count++;
	if(count==20){
	 	count=0;
		miao++;
		if(miao==60){
		 	miao=0;
			fen++;
			if(fen==60){
			 	fen=0;
				shi++;
				if(shi==24)shi=0;
				write_sfm(4,shi);
				At24c02Write(3,shi);
			}
			write_sfm(7,fen);
			At24c02Write(2,fen);
		}
		write_sfm(10,miao);
		At24c02Write(1,miao);
	}	
}