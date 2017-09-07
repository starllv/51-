//P0是位选端，P1是段选端，P2连着独立键盘
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code weima[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar code duanma[]={0x3f,0x06,0x5b,0x4f,0x66,
				0x6d,0x7d,0x07,0x7f,0x6f};
uchar displaynum[]={0,0,0,0,0,0,0,0};
sbit k1=P2^0;
sbit k2=P2^1;
sbit k3=P2^2;
sbit k4=P2^3;
sbit k5=P2^4;
sbit k6=P2^5;
sbit k7=P2^6;
sbit k8=P2^7;

void delayms(uint xms){
 	uint i;
	for(xms;xms>0;xms--)
		for(i=100;i>0;i--);
}

uchar key(){
	uchar a=0;
 	if(k1==0){
	 	delayms(10);
		if(k1==0){
			while(!k1){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '1';
		}
	}
	if(k2==0){
	 	delayms(10);
		if(k2==0){
			P0=0x00;
			P1=0x3f;
			while(!k2){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '2';
		}
	}
	if(k3==0){
	 	delayms(10);
		if(k3==0){
			P0=0x00;
			P1=0x3f;
			while(!k3){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '3';
		}
	}
	if(k4==0){
	 	delayms(10);
		if(k4==0){
			P0=0x00;
			P1=0x3f;
			while(!k4){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '4';
		}
	}
	if(k5==0){
	 	delayms(10);
		if(k5==0){
			P0=0x00;
			P1=0x3f;
			while(!k5){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '5';
		}
	}
	if(k6==0){
	 	delayms(10);
		if(k6==0){
			P0=0x00;
			P1=0x3f;
			while(!k6){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '6';
		}
	}
	if(k7==0){
	 	delayms(10);
		if(k7==0){
			P0=0x00;
			P1=0x3f;
			while(!k7){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '7';
		}
	}
	if(k8==0){
	 	delayms(10);
		if(k8==0){
			P0=0x00;
			P1=0x3f;
			while(!k8){
			 	P0=weima[a];
				P1=duanma[displaynum[a]];
				a++;
				if(a>7)a=0;
				delayms(1);
			}
			return '8';
		}
	}
}

void display(){
 	uchar num;
	for(num=0;num<8;num++){
	 	P0=weima[num];
		P1=duanma[displaynum[num]];
		delayms(1);
	}	
}

void main(){
	uchar KEY;
 	while(1){
	 	KEY=key();
		switch(KEY)
		{
		 	case '1': displaynum[0]+=1;
					if(displaynum[0]==10)displaynum[0]=0;
					break;
			case '2':displaynum[1]+=1;
					if(displaynum[1]==10)displaynum[1]=0;
					break;
			case '3':displaynum[2]+=1;
					if(displaynum[2]==10)displaynum[2]=0;
					break;
			case '4':displaynum[3]+=1;
					if(displaynum[3]==10)displaynum[3]=0;
					break;
			case '5':displaynum[4]+=1;
					if(displaynum[4]==10)displaynum[4]=0;
					break;
			case '6':displaynum[5]+=1;
					if(displaynum[5]==10)displaynum[5]=0;
					break;
			case '7':displaynum[6]+=1;
					if(displaynum[6]==10)displaynum[6]=0;
					break;
			case '8':displaynum[7]+=1;
					if(displaynum[7]==10)displaynum[7]=0;
					break;
		}
		display();
	}
}
