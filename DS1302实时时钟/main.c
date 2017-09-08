#include<reg51.h>
#include"ds1302.h"
#include"lcd.h"

#define uchar unsigned char
#define uint unsigned int

sbit s1=P2^0;
sbit s2=P2^1;
sbit s3=P2^2;
sbit s4=P2^3;
sbit beep=P2^4;

bit flag1,flag_ri;
uchar count,s1num,flag,t0_num;
uchar day,month,week,amiao,afen,ashi;
uint miao,shi,fen,year;
uchar table[]=" 20  -  -       ";
uchar table1[]="      :  :  ";

void delay(uint x){
 	uchar y;
	for(x;x>0;x--)
		for(y=110;y>0;y--);
}

void di(){
 	uchar n;
	for(n=0;n<8;n++){
	 	beep=0;
		delay(10);
		beep=1;
		delay(10);
	}
}

void write_sfm(uchar add,char date){
 	char shi,ge;
	shi=date/10;
	ge=date%10;
	writecom(0x80+0x40+add);
	writedata('0'+shi);
	writedata('0'+ge);
}

void write_sfm_bcd(uchar add,char date){
 	char shi,ge;
	shi=date/16;
	ge=date&0x0f;
	writecom(0x80+0x40+add);
	writedata('0'+shi);
	writedata('0'+ge);
}

void write_nyr(uchar add,char date){
	char shi,ge;
	shi=date/10;
	ge=date%10;
	writecom(0x80+add);
	writedata('0'+shi);
	writedata('0'+ge); 	
}

void write_nyr_bcd(uchar add,char date){
	char shi,ge;
	shi=date/16;
	ge=date&0x0f;
	writecom(0x80+add);
	writedata('0'+shi);
	writedata('0'+ge); 	
}

void write_week(char we){
 	writecom(0x80+12);
	switch(we)
	{
	 	case 1: writedata('M');delay(5);
				writedata('O');delay(5);
				writedata('N');
				break;
		case 2: writedata('T');delay(5);
				writedata('U');delay(5);
				writedata('E');
				break;
		case 3: writedata('W');delay(5);
				writedata('E');delay(5);
				writedata('D');
				break;
		case 4: writedata('T');delay(5);
				writedata('H');delay(5);
				writedata('U');
				break;
		case 5: writedata('F');delay(5);
				writedata('R');delay(5);
				writedata('I');
				break;
		case 6: writedata('S');delay(5);
				writedata('A');delay(5);
				writedata('T');
				break;
		case 7: writedata('S');delay(5);
				writedata('U');delay(5);
				writedata('N');
				break;
	}
}

uchar shi_bcd(uchar num){
	return (((num/10)<<3)|(num%10)); 	
}
//void read_alarm(){
// 	amiao=read_ds(0x81);
//	afen=read_ds(0x83);
//	ashi=read_ds(0x85);
//}

void init(){
 	uchar num;
//	EA=1;
//	EX1=1;
//	IT1=1;
	flag1=0;
	t0_num=0;
	s1num=0;
	week=1;
	set_time();
	lcdinit();
	for(num=0;num<15;num++){
	 	writedata(table[num]);
		delay(1);
	}
	writecom(0x80+0x40);
	for(num=0;num<11;num++){
	 	writedata(table1[num]);
		delay(1);
	}
}

void keyscan(){
// 	if(flag_ri==1){
//	 	if((s1==0)||(s2==0)||(s3==0)||(s4==0)){
//		 	delay(5);
//			if((s1==0)||(s2==0)||(s3==0)||(s4==0)){
//			 	while(!(s1&&s2&&s3&&s4));di();
//				flag_ri=0;
//			}
//		}
//	}

	if(s1==0){
	 	delay(5);
		if(s1==0){
		 	s1num++;
//			if(flag1==1){
//			 	if(s1num==4)s1num=1;
//			}
			flag=1;
			while(!s1);di();
			switch(s1num)
			{
			 	case 1: writecom(0x80+0x40+10);
						writecom(0x0f);
						break;
				case 2: writecom(0x80+0x40+7);
						break;
				case 3: writecom(0x80+0x40+4);
						break;
				case 4: writecom(0x80+12);
						break;
				case 5: writecom(0x80+9);
						break;
				case 6: writecom(0x80+6);
						break;
				case 7: writecom(0x80+3);
						break;
				case 8: s1num=0;
						writecom(0x0c);
						flag=0;
						write_ds(0x8E,0x00);

						write_ds(0x80,shi_bcd(miao));
						write_ds(0x82,shi_bcd(fen));
						write_ds(0x84,shi_bcd(shi));
						write_ds(0x86,shi_bcd(day));
						write_ds(0x88,shi_bcd(month));
						write_ds(0x8a,shi_bcd(week));
						write_ds(0x8c,shi_bcd(year));

						write_ds(0x8E,0x80);
						break;
			}
		}
	}
	if(s1num!=0){
	 	if(s2==0){
		 	delay(5);
			if(s2==0){
			 	while(!s2);di();
				switch(s1num)
				{
				 	case 1: miao++;
							if(miao==60)miao=0;
							write_sfm(10,miao);
							writecom(0x80+0x40+10);
							break;
					case 2: fen++;
							if(fen==60)fen=0;
							write_sfm(7,fen);
							writecom(0x80+0x40+7);
							break;
					case 3: shi++;
							if(shi==24)shi=0;
							write_sfm(4,shi);
							writecom(0x80+0x40+4);
							break;
					case 4: week++;
							if(week==8)week=1;
							write_week(week);
							writecom(0x80+12);
							break;
					case 5: day++;
							if(day==32)day=1;
							write_nyr(9,day);
							writecom(0x80+9);
							break;
					case 6: month++;
							if(month==13)month=1;
							write_nyr(6,month);
							writecom(0x80+6);
							break;
					case 7: year++;
							if(year==100)year=0;
							write_nyr(3,year);
							writecom(0x80+3);
							break;
				}
			}
		}
		if(s3==0){
		 	delay(5);
			if(s3==0){
			 	while(!s3);di();
				switch(s1num)
				{
				 	case 1: miao--;
							if(miao==-1)miao=59;
							write_sfm(10,miao);
							writecom(0x80+0x40+10);
							break;
					case 2: fen--;
							if(fen==-1)fen=59;
							write_sfm(7,fen);
							writecom(0x80+0x40+7);
							break;
					case 3: shi--;
							if(shi==-1)shi=23;
							write_sfm(4,shi);
							writecom(0x80+0x40+4);
							break;
					case 4: week--;
							if(week==0)week=7;
							write_week(week);
							writecom(0x80+12);
							break;
					case 5: day--;
							if(day==0)day=31;
							write_nyr(9,day);
							writecom(0x80+9);
							break;
					case 6: month--;
							if(month==0)month=12;
							write_nyr(6,month);
							writecom(0x80+6);
							break;
					case 7: year--;
							if(year==-1)year=99;
							write_nyr(3,year);
							writecom(0x80+3);
							break;			
				}
			}
		}
	}
//	if(s4==0){
//	 	delay(5);
//		if(s4==0){
//		 	flag1=~flag1;
//			while(!s4);di();
//			if(flag1==0){
//			 	flag=0;
//				writecom(0x80+0x40);
//				writedata(' ');
//				writedata(' ');
//				writecom(0x0c);
//
//				write_ds(0x8E,0x00);
//
//				write_ds(0x80,miao);
//				write_ds(0x82,fen);
//				write_ds(0x84,shi);
//
//				write_ds(0x8E,0x80);
//			}
//			else{
//			 	read_alarm();
//				miao=amiao;
//				fen=afen;
//				shi=ashi;
//				writecom(0x80+0x40);
//				writedata('R');
//				writedata('i');
//				writecom(0x80+0x40+3);
//				write_sfm(4,shi);
//				write_sfm(7,fen);
//				write_sfm(10,shi);
//			}
//		}
//	}
}

void main(){
 	init();
	while(1){
	 	keyscan();
//		if(flag_ri==1){
//		 	di();
//			delay(100);
//			di();
//			delay(500);
//		}
		if(flag==0&&flag1==0){
		 	keyscan();
			miao=read_ds(0x81);
			fen=read_ds(0x83);
			shi=read_ds(0x85);
			day=read_ds(0x87);
			month=read_ds(0x89);
			week=read_ds(0x8b);
			year=read_ds(0x8d);

			write_sfm_bcd(10,miao);
			write_sfm_bcd(7,fen);
			write_sfm_bcd(4,shi);
			write_week(week);
			write_nyr_bcd(3,year);
			write_nyr_bcd(6,month);
			write_nyr_bcd(9,day);
		}
	}
}

//void exter() interrupt 2
//{
// 	uchar c;
//	flag_ri=1;
//	c=read_ds(0x0c);
//}