 #include"lcd.h"

 void lcd_delay1ms(uint c){
  	uchar a,b;
	for(c;c>0;c--)
		for(b=199;b>0;b--)
			for(a=1;a>0;a--);
 }

 void  writecom(uchar com){
  	E=0;
	RS=0;
	RW=0;
	DATAPINS=com;
	lcd_delay1ms(1);
	E=1;
	lcd_delay1ms(5);
	E=0;
 }

 void writedata(uchar dat){
  	E=0;
	RS=1;
	RW=0;
	DATAPINS=dat;
	lcd_delay1ms(1);
	E=1;
	lcd_delay1ms(5);
	E=0;
 }

 void lcdinit(){
  	writecom(0x38);
	writecom(0x0c);
	writecom(0x06);
	writecom(0x01);
	writecom(0x80);
 }