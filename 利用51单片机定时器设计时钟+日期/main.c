#include<reg52.h>
#include"24c02.h"

#define uint unsigned int
#define uchar unsigned char

sbit lcden=P2^7;
sbit rs=P2^6;
sbit rw=P2^5;
sbit s1=P2^3;
sbit s2=P2^4;
sbit s3=P2^2;
sbit beep=P1^0;

uint counter=15536;
uchar count,s1num;
char miao,shi,fen,nian,yue,ri,xingqi;
uchar code table[7][3]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

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
	rw=0;
 	rs=0;
	lcden=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}

void write_data(uchar date){
	rw=0;
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

void write_nyr(uchar add,uchar date){
 	uchar ge,shi;
	shi=date/10;
	ge=date%10;
	write_com(0x80+add);
	write_data(0x30+shi);
	write_data(0x30+ge);
}

void write_week(uchar week){
	uchar num;
 	write_com(0x80+13);
	for(num=0;num<3;num++){
		write_data(table[week][num]);
	}
}

void init(){
	lcden=0;
	shi=0;
	fen=0;
	miao=0;
	count=0;
	s1num=0;
	init_24c02();
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80+2);
	write_data('2');
	write_data('0');
	write_com(0x80+6);
	write_data('-');
	write_com(0x80+9);
	write_data('-');
	write_com(0x80+0x40+6);
	write_data(':');
	delay(5);
	write_com(0x80+0x40+9);
	write_data(':');
	delay(5);
	nian=read_add(4);
	yue=read_add(5);
	ri=read_add(6);
	xingqi=read_add(7);
	miao=read_add(1);
	fen=read_add(2);
	shi=read_add(3);
	write_nyr(4,nian);
	write_nyr(7,yue);
	write_nyr(10,ri);
	write_week(xingqi);
	write_sfm(10,miao);
	write_sfm(7,fen);
	write_sfm(4,shi);
	TMOD=0x01;
	TH0=counter/256;
	TL0=counter%256;
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
				write_com(0x80+10);
			}
			if(s1num==5){
			 	write_com(0x80+7);
			}
			if(s1num==6){
			 	write_com(0x80+4);
			}
			if(s1num==7){
			 	write_com(0x80+13);
			}
			if(s1num==8){
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
					write_add(1,miao);	
				}
				if(s1num==2){
				 	fen++;
					if(fen>=60)fen=0;
					write_sfm(7,fen);
					write_com(0x80+0x40+7);
					write_add(2,fen);
				}
				if(s1num==3){
				 	shi++;
					if(shi>=24)shi=0;
					write_sfm(4,shi);
					write_com(0x80+0x40+4);
					write_add(3,shi);
				}
				if(s1num==4){
				 	ri++;
					if(ri==32)ri=1;
					write_nyr(10,ri);
					write_com(0x80+10);
					write_add(6,ri);
				}
				if(s1num==5){
				 	yue++;
					if(yue>=13)yue=1;
					write_nyr(7,yue);
					write_com(0x80+7);
					write_add(5,yue);
				}
				if(s1num==6){
				 	nian++;
					if(nian>=100)nian=0;
					write_nyr(4,nian);
					write_com(0x80+4);
					write_add(4,nian);
				}
				if(s1num==7){
				 	xingqi++;
					if(xingqi>=7)xingqi=0;
					write_week(xingqi);
					write_add(7,xingqi);
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
					write_add(1,miao);
				}
				if(s1num==2){
				 	fen--;
					if(fen==-1)fen=59;
					write_sfm(7,fen);
					write_com(0x80+0x40+7);
					write_add(2,fen);
				}
				if(s1num==3){
				 	shi--;
					if(shi==-1)shi=23;
					write_sfm(4,shi);
					write_com(0x80+0x40+4);
					write_add(3,shi);
				}
				if(s1num==4){
				 	ri--;
					if(ri==0)ri=31;
					write_nyr(10,ri);
					write_com(0x80+10);
					write_add(6,ri);
				}
				if(s1num==5){
				 	yue--;
					if(yue==0)yue=12;
					write_nyr(7,yue);
					write_com(0x80+7);
					write_add(5,yue);
				}
				if(s1num==6){
				 	nian--;
					if(nian==-1)nian=99;
					write_nyr(4,nian);
					write_com(0x80+4);
					write_add(4,nian);
				}
				if(s1num==7){
				 	xingqi--;
					if(xingqi==-1)xingqi=6;
					write_week(xingqi);
					write_add(7,xingqi);
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
 	TH0=counter/256;
	TL0=counter%256;
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
				if(shi==24){
					shi=0;
					ri++;
					xingqi++;
					if(xingqi>=7)xingqi=0;
					switch(yue){
					 case 1:if(ri>=32){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 2:if(ri>=29){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 3:if(ri>=32){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 4:if(ri>=31){
					 	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue); 	
					 };break;
					 case 5:if(ri>=32){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 6:if(ri>=31){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 7:if(ri>=32){
					 	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 8:if(ri>=32){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 9:if(ri>=31){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 10:if(ri>=32){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 11:if(ri>=31){
					  	ri=1;
						yue++;
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 case 12:if(ri>=32){
					  	ri=1;
						yue=1;
						nian++;
						if(nian>=99)nian=0;
						write_nyr(4,nian);
						write_add(4,nian);
						write_nyr(7,yue);
						write_add(5,yue);
					 };break;
					 default:break;
					 }
					write_nyr(10,ri);
					write_add(6,ri);
					write_week(xingqi);
					write_add(7,xingqi);
				}
				write_sfm(4,shi);
				write_add(3,shi);
			}
			write_sfm(7,fen);
			write_add(2,fen);
		}
		write_sfm(10,miao);
		write_add(1,miao);
	}	
}