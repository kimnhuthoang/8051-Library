
#include <REGX52.H>
#include <intrins.h>
#include "dht11_22.h"

static void delay_30us()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}

static void delay_ms(unsigned int t)      
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<123;j++);
		_nop_();_nop_();
	}
}

char DHT_ReadData()			/* Receive data */
{
	char i,b=0;	
	for (i=0;i<8;i++)
	{
		while(DHT_pin==0);		/* wait wait host signal logic 0 = 50us */
		delay_30us();         /* wait 30us,if DHT11_pin=0:bit=0 else bit=1*/
		if(DHT_pin==1)			
		b = (b<<1)|(0x01);	
		else								
		b = (b<<1);
		while(DHT_pin==1);
	}
	return b;
}

void DHT_init()				 /* Microcontroller send request */
{
	DHT_pin = 0;				 /* set to low pin */
	delay_ms(20);				 /* wait for 20ms */
	DHT_pin = 1;				 /* set to high pin */
	
	while(DHT_pin==1);   /* Wait response from DHT11 */
	while(DHT_pin==0);   /*logic 0 = 80us; logic 1 = 80us*/
	while(DHT_pin==1);
}