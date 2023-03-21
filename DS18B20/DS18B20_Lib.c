#include <REGX52.H>
#include "DS18B20_Lib.h"

//void Delay_T0_Init()
//{
//	TMOD|=0x01;
//}
//void T0_delay_us(unsigned int t)		
//{
//	unsigned int value;
//	value = (65535-t)+20;
//	TH0 = value>>8;			
//	TL0 = value&0x00ff;	
//	TR0 = 1;						
//	while(TF0 == 0);		
//	TR0 = 0;						
//	TF0 = 0;						
//}

void DS18B20_reset() //result = 0 => thanh cong; result = 1 =>that bai//
{
	int i;
Again:
	DS18B20_Pin = 0;
//	T0_delay_us(480);
	for(i=0;i<60;i++); //delay 483us
	DS18B20_Pin = 1;
//	T0_delay_us(70);
	for(i=0;i<9;i++);	 //delay 75us
	if(DS18B20_Pin==1) goto Again;
//	T0_delay_us(410);
	for(i=0;i<51;i++); //delay 411us
}

void DS18B20_write(unsigned char dat)
{
		unsigned char i; int j;
    for(i=8;i>0;i--)
		{
			DS18B20_Pin = 0;
			DS18B20_Pin = ((dat&0x01)==0x01);
			for(j=0;j<8;j++);  //delay 67us
			DS18B20_Pin = 1;
			dat>>=1;
    }
}

unsigned char DS18B20_read()
{
    unsigned char i; int j;
    unsigned char dat = 0;
    for(i=8;i>0;i--)
		{
			DS18B20_Pin = 0;
			dat>>=1;
			DS18B20_Pin = 1;
//			T0_delay_us(20);
			for(j=0;j<2;j++); 							//delay 19us
			if(DS18B20_Pin){dat|=0x80;}
			for(j=0;j<2;j++); 							//delay 19us
//      T0_delay_us(20);
    }
    return(dat);
}