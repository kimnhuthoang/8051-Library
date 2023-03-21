#include <REGX52.H>
#include "1wire.h"
sbit Onewire_pin = P2^0;

void T0_delay_us(unsigned int t)		
{
	unsigned int value;
	value = (65535-t)+20;
	TH0 = value>>8;			
	TL0 = value&0x00ff;	
	TR0 = 1;						
	while(TF0 == 0);		
	TR0 = 0;						
	TF0 = 0;						
}

void Onewire_reset() //result = 0 => thanh cong; result = 1 =>that bai//
{
Again:
	Onewire_pin = 0;
	T0_delay_us(480);
	Onewire_pin = 1;
	T0_delay_us(70);
	if(Onewire_pin==1) goto Again;
	T0_delay_us(410);
}

void Onewire_write(unsigned char dat)
{
		unsigned char i;
    for (i=8; i>0; i--)
		{
        Onewire_pin = 0;
        Onewire_pin = dat&0x01;
        T0_delay_us(60);
        Onewire_pin = 1;
        dat>>=1;
    }
}

unsigned char Onewire_read()
{
    unsigned char i;
    unsigned char dat = 0;
    for (i=8;i>0;i--){
					Onewire_pin = 0;
          dat>>=1;
					Onewire_pin = 1;
					T0_delay_us(30);
          if(Onewire_pin){dat|=0x80;}
          T0_delay_us(30);
    }
    return(dat);
}