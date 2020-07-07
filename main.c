#include<reg51.h>
#include<lcd.h>
#include<stdio.h>

//LCD Module Connections
sbit RS = P0^0;                                                                   
sbit EN = P0^1;                            
sbit D0 = P2^0;
sbit D1 = P2^1;
sbit D2 = P2^2;
sbit D3 = P2^3;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;

//PIR connection
sbit PIR=P1^0;

//delay function for 1ms
void delay()    //delay by timer function
{
	TMOD=0x01;    //select timer 0 mode 1
	TH0=0xFC;     //load FC67 for 1000 Count
	TL0=0x67;
	TCON=0x10;    //start timer 0
	
	while(!(TCON & 0x20));
	{
		TCON &=~0x10;    //stop timer 0
		TCON &=~0x20;    //clear overflow flag
	}
}

//timer delay function for x ms
void timer_delay(int ms)
{
	int i;
	for(i=0;i<ms;i++)
		delay();
}



void main()
{
	int i,hum=80;
	float temp=28.6;
	unsigned char humidity[20],temperature[20];
	                                  
  //sprintf(humidity,"HUMIDITY:%d",hum);
	//sprintf(temperature,"TEMP.:%0.2f",temp);
	
	Lcd8_init();   //Init lcd
	
	while(1)
  { 
		Lcd8_Clear();
		
		if(PIR==1)
		{
			Lcd8_Set_Cursor(1,1);
			Lcd8_Write_String("Motion detected");
			timer_delay(5000);
		}
		else if(PIR==0)
		{
			Lcd8_Set_Cursor(1,1);
			Lcd8_Write_String("Motion Not");
			Lcd8_Set_Cursor(2,1);
			Lcd8_Write_String("Detected");
			timer_delay(5000);
    }
	}
}