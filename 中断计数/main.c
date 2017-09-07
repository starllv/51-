#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit LS138A=P2^2;  
sbit LS138B=P2^3;
sbit LS138C=P2^4;
sbit In=P3^0;

uchar code Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
uchar LedOut[8];
uchar num;
uint count;

void delay(uint i){
	uchar j;
 	for(i;i>0;i--)
		for(j=100;j>0;j--);
}

void main(){
	uchar i;
	In=0;
 	TMOD=0x16;
	TH0=0xff;
	TL0=0xff;
	TH1=65075/256;	//定时500微秒
	TL1=65075%256;
	ET0=1;
	ET1=1;
	EA=1;
	TR0=1;
	TR1=1;
	while(1){
//		P0=~Disp_Tab[num%10];

	 	LedOut[0]=0;
     	LedOut[1]=0;	  //0x7f小数点
     	LedOut[2]=0;
     	LedOut[3]=0;

	 	LedOut[4]=0;
     	LedOut[5]=0;
     	LedOut[6]=Disp_Tab[num/10];
     	LedOut[7]=Disp_Tab[num%10];;


	 	for( i=0; i<8; i++) 
	 	{	 
			
	  		switch(i)					  
	     	{	    
				case 0:LS138A=0; LS138B=0; LS138C=0; break;         
	        	case 1:LS138A=1; LS138B=0; LS138C=0; break;             	
	        	case 2:LS138A=0; LS138B=1; LS138C=0; break; 
	        	case 3:LS138A=1; LS138B=1; LS138C=0; break; 
				case 4:LS138A=0; LS138B=0; LS138C=1; break;
				case 5:LS138A=1; LS138B=0; LS138C=1; break;
				case 6:LS138A=0; LS138B=1; LS138C=1; break;
				case 7:LS138A=1; LS138B=1; LS138C=1; break;
			
	     	}
			P0 = LedOut[i];
			delay(5);
	 	}
	}
}

void t0() interrupt 1
{
	num++;
	if(num>=100)num=0;
}

void t1() interrupt 3
{
 	count++;
	if(count>=5){
		count=0;
	 	In=~In;
	}
}