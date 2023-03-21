/*Thu vien doc analog tu ic ADC0808*/
/*Kim Nhut Hoang - 10DHDT1 - DHCNTP TPHCM <HUFI>*/

#include <REGX52.H>
#include "ADC0808.h"

void ADC0808_setup()
{
	ADC0808_START = 0;
	ADC0808_ALE = 0;
	ADC0808_OE = 0;
}

/**************Show Temp***********************
//Neu gia tri dien ap tham chieu khac 2.55V thi su dung ham nay//
unsigned char Temp(unsigned char adc) 
{
	 return ((VREF*adc)/2.56f); //Tinh nhiet do 
} */
unsigned char ADC0808_Read(unsigned char channel)
{
	unsigned char kq;
 	ADC0808_A = channel & 0x01;
	ADC0808_B = channel & 0x02;
	ADC0808_C = channel & 0x04;
	
	ADC0808_ALE = 1;
	ADC0808_START = 1;
	ADC0808_ALE = 0;
	ADC0808_START = 0;
	
	while(ADC0808_EOC);
	while(!ADC0808_EOC);
	
	ADC0808_OE = 1;
	kq = ADC0808_DATA;
	ADC0808_OE = 0;
	
	return kq;
}
