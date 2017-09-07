#include<reg51.h>
#include<stdio.h>
#include<intrins.h>

unsigned char a,flag,flag_uart;

void init(){
 	TMOD=0x20;
	PCON=0x80;
	TH1=0xf4;
	TL1=0xf4;
	TR1=1;
	SCON=0x50;
	EA=1;
	ES=1;
}

void main(){
 	init();
	TI=1;
	puts("�����ַ�c�������");
	puts("�����ַ�e���Ӣ��");
	puts("���������ַ����������룡\n");
	while(!TI);
	TI=0;
	while(1){
		if(flag_uart==1){
			flag_uart=0;
		 	ES=0;
			TI=1;
			switch(flag){
			 	case 0:puts("hello world!");
					break;
				case 1:printf("���!\n");
					break;
				case 2:break;
				case 3:puts("please input again!\n");
					break;
			}
			while(!TI);
			TI=0;
			ES=1;
		}	 	
	}
}

void ser() interrupt 4{
 	RI=0;
	a=SBUF;
	flag_uart=1;
	if(a=='e')
		flag=0;
	else if(a=='c')
			flag=1;
		else if(a=='\0')
				flag=2;
			else
				flag=3;
}